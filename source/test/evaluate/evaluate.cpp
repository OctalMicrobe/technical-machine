// Test damage-related functions
// Copyright (C) 2014 David Stone
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

#include "evaluate.hpp"

#include "../../evaluate/evaluate.hpp"
#include "../../team.hpp"
#include "../../weather.hpp"

#include "../../pokemon/species.hpp"

#include <bounded_integer/bounded_integer.hpp>

#include <cassert>
#include <iostream>

namespace technicalmachine {
namespace {
using namespace bounded::literal;

void assert_lower_score(Evaluate const & evaluate, Team const & lesser, Team const & greater) {
	assert(evaluate(lesser, greater, Weather{}) < 0_bi);
}

}	// namespace

void evaluate_tests() {
	std::cout << "Running evaluate tests.\n";

	auto const species = Species::Blissey;
	Level const level(100_bi);
	auto const gender = Gender::FEMALE;
	auto const item = Item::Leftovers;
	auto const ability = Ability::Natural_Cure;
	auto const nature = Nature::Bold;

	Team team1(1_bi);
	team1.add_pokemon(species, level, gender, item, ability, nature);
	Team team2(1_bi);
	team2.add_pokemon(species, level, gender, item, ability, nature);
	get_hp(team1.pokemon()) -= 50_bi;
	Evaluate const evaluate;
	assert_lower_score(evaluate, team1, team2);

	std::cout << "Evaluate tests passed.\n\n";
}

}	// namespace technicalmachine