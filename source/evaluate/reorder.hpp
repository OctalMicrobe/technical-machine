// Reorder moves for efficient evaluation
// Copyright (C) 2015 David Stone
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

#pragma once

#include "../block.hpp"
#include "../move/max_moves_per_pokemon.hpp"
#include "../move/moves.hpp"

#include <containers/static_vector/static_vector.hpp>

namespace technicalmachine {

struct MoveScores;

StaticVectorMoves reorder(LegalSelections const & input, MoveScores const & move_scores, bool ai);

}	// namespace technicalmachine
