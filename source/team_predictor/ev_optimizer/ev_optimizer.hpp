// Optimize EVs and nature to remove waste
// Copyright (C) 2018 David Stone
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

#include "../../stat/ev.hpp"
#include "../../stat/nature.hpp"
#include "../../stat/stat_names.hpp"

#include <containers/array/array.hpp>

#include <random>

namespace technicalmachine {
struct Pokemon;

struct Combined {
	Nature nature;
	EV hp;
	EV attack;
	EV defense;
	EV special_attack;
	EV special_defense;
	EV speed;
};

constexpr auto regular_stats() {
	return containers::array{StatNames::ATK, StatNames::DEF, StatNames::SPA, StatNames::SPD, StatNames::SPE};
}

void optimize_evs(Pokemon & pokemon, std::mt19937 & random_engine);
void minimize_evs(Pokemon & pokemon);
void pad_random_evs(Pokemon & pokemon, std::mt19937 & random_engine);

}	// namespace technicalmachine
