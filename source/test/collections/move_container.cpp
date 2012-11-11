// Test container for moves
// Copyright (C) 2012 David Stone
//
// This file is part of Technical Machine.
//
// Technical Machine is free software: you can redistribute it and / or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "move_container.hpp"

#include <functional>
#include <iostream>

#include "create_regular_moves.hpp"
#include "create_shared_moves.hpp"
#include "invalid_collection.hpp"

#include "../../move/move.hpp"
#include "../../move/moves_forward.hpp"
#include "../../move/container.hpp"
#include "../../move/shared.hpp"

namespace technicalmachine {
namespace {
class Comparator : public std::unary_function<void, Move> {
	public:
		Comparator(std::vector<Moves> const & m):
			moves(m),
			n(0) {
		}
		void operator()(Move const & move) {
			if (moves[n] != move.name)
				throw InvalidCollection("MoveContainer has the wrong moves.");
			++n;
		}
		std::vector<Moves> moves;
		unsigned n;
};

}	// unnamed namespace

void move_container_tests() {
	std::cout << "\tRunning MoveContainer tests.\n";
	constexpr unsigned team_size = 4;
	constexpr unsigned shared_moves_size = team_size + 1;
	SharedMoves shared(team_size);
	MoveContainer c(shared);
	if (c.size() != shared_moves_size)
		throw InvalidCollection("MoveContainer has the wrong number of shared moves.");
	auto const moves = create_regular_moves();
	for (unsigned n = 0; n != moves.size(); ++n) {
		c.emplace_back(moves[n]);
		if (c.size() != shared_moves_size + n + 1 or c.size() != c.number_of_regular_moves() + shared_moves_size)
			throw InvalidCollection("MoveContainer has the wrong number of moves.");
	}
	c.for_each_regular_move(Comparator(moves));
	c.for_each_shared(Comparator(create_shared_moves(team_size)));
}

}	// namespace technicalmachine
