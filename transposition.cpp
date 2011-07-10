// Determine when transpositions occur
// Copyright 2011 David Stone
//
// This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License
// as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <cstdint>
#include <iostream>
#include "evaluate.h"
#include "expectiminimax.h"
#include "move.h"
#include "pokemon.h"
#include "team.h"
#include "transposition.h"
#include "weather.h"

namespace technicalmachine {

class Hash {
public:
	uint64_t ai;
	uint64_t foe;
	uint64_t weather;
	int64_t score;
	int depth;
	Hash ();
	Hash (uint64_t ai_hash, uint64_t foe_hash, uint64_t weather_hash, int depth_current);
	bool operator== (Hash const &other) const;
	bool operator!= (Hash const &other) const;
};

Hash::Hash ():
	depth (0) {
}

Hash::Hash (uint64_t ai_hash, uint64_t foe_hash, uint64_t weather_hash, int depth_current):
	ai (ai_hash),
	foe (foe_hash),
	weather (weather_hash),
	depth (depth_current) {
}

bool Hash::operator== (Hash const &other) const {
	return ai == other.ai and foe == other.foe and weather == other.weather;
}

bool Hash::operator!= (Hash const &other) const {
	return !(*this == other);
}

int64_t transposition (Team &ai, Team &foe, Weather const &weather, int const &depth, score_variables const &sv) {
	int64_t score;
	if (depth == 0)
		score = evaluate (ai, foe, weather, sv);
	else {
		// First, I hash both teams and the weather. These are the long-form hashes that are each the size of a uint64_t, and should be unique within a game. I then take those hashes and divide them modulo their relevant dimension (used to determine the size of the transposition table). These short-form hashes are used as the array index. The shortened hash combinations are used to look up the full hashes, score, and depth.
		Hash hash (ai.hash(), foe.hash(), weather.hash(), depth);
		static unsigned const ai_dimension = 256;
		static unsigned const foe_dimension = 256;
		static unsigned const weather_dimension = 32;
		static Hash table [ai_dimension][foe_dimension][weather_dimension] = {};
		Hash * const transpose = &table [hash.ai % ai_dimension] [hash.foe % foe_dimension] [hash.weather % weather_dimension];
		// If I can find the current state in my transposition table at a depth of at least the current depth, set the score to the stored score.
		if (transpose->depth >= hash.depth and *transpose == hash)
			score = transpose->score;
		else {
			moves_list phony = END_MOVE;
			// If I can't find it, set the score to the evaluation of the state at depth - 1.
			hash.score = select_move_branch (ai, foe, weather, depth, sv, phony);
		
			// Since I didn't find any stored value at the same hash as the current state, or the value I found was for a shallower depth, add the new value to my table.
			*transpose = hash;
			score = hash.score;
		}
	}
	return score;
}

}
