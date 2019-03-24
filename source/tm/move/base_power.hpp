// Base power calculation
// Copyright (C) 2019 David Stone
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

#include <bounded/integer.hpp>
#include <bounded/optional.hpp>

namespace technicalmachine {
enum class Generation;
enum class Moves : std::uint16_t;

// variable power returns non-0. Fixed damage is the uninitialized state.
auto base_power(Generation generation, Moves move) -> bounded::optional<bounded::integer<0, 250>>;

// Fling gives 0, Rollout gives 480
using VariableAdjustedBasePower = bounded::integer<0, 480>;

}	// namespace technicalmachine
