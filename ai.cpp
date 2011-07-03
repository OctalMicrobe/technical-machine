// AI to win a 1v1 battle
// Copyright 2011 David Stone
//
// This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License
// as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include <iostream>
#include <boost/lexical_cast.hpp>
#include "analyze_logs.h"
#include "expectiminimax.h"
#include "item.h"
#include "load_stats.h"
#include "move.h"
#include "pokemon.h"
#include "status.h"
#include "team.h"
#include "teampredictor.h"
#include "type.h"
#include "weather.h"

int main (int argc, char* argv[]) {
	using namespace technicalmachine;
	unsigned const foe_size = 6;
	int depth;
	if (argc == 1)
		depth = -1;
	else
		depth = boost::lexical_cast <int> (argv[1]);

	Map const map;
	int detailed [END_SPECIES][7] = {{ 0 }};
	detailed_stats (map, detailed);
	Team ai (true, map, foe_size);
	Team foe (false, map, ai.size);
	Weather weather;
	score_variables sv;
	
	analyze_turn (ai, foe, weather, map);		// Turn 0, sending out initial Pokemon
	
	bool won = false;
	while (!won) {
		Team predicted = foe;
		std::cout << "======================\nPredicting...\n";
		predict_team (detailed, predicted, ai.size);
		std::string out;
		predicted.output (out);
		std::cout << out;

		long score;
		moves_list best_move = expectiminimax (ai, predicted, weather, depth, sv, score);

		won = analyze_turn (ai, foe, weather, map);
	}
	return 0;
}
