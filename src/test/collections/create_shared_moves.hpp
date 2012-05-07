// Basis for some move tests
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

#ifndef TEST_CREATE_SHARED_MOVES_HPP_
#define TEST_CREATE_SHARED_MOVES_HPP_

#include <vector>
#include "../../move.hpp"

namespace technicalmachine {

inline std::vector<Move> create_shared_moves(unsigned const team_size) {
	std::vector<Move> shared ({ Move(Move::STRUGGLE, 0) });
	if (team_size != 1) {
		for (unsigned n = 0; n != team_size; ++n)
			shared.push_back(Move(Move::from_replacement(n), 0));
	}
	return shared;
}

}	// namespace technicalmachine
#endif	// TEST_CREATE_SHARED_MOVES_HPP_
