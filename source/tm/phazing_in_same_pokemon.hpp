// Exception class if phazing attempts to bring in the currently active Pokemon
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

#include <tm/pokemon/collection.hpp>

#include <stdexcept>

namespace technicalmachine {

struct PhazingInSamePokemon : std::logic_error {
	explicit PhazingInSamePokemon(containers::index_type<PokemonCollection> index);
};

}	// namespace technicalmachine
