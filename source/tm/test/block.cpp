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

#include <tm/test/block.hpp>

#include <tm/string_conversions/move.hpp>
#include <tm/block.hpp>
#include <tm/team.hpp>
#include <tm/weather.hpp>

#include <iostream>

namespace technicalmachine {
namespace {

void test_two_moves_with_one_out_of_pp() {
	auto user = Team(1_bi, true);
	auto & pokemon = user.add_pokemon(Species::Pikachu, Level(100_bi), Gender::female);
	auto empty_pp = [](Move & move) {
		while (!move.pp().is_empty()) {
			move.decrement_pp(Ability::Static);
		}
	};
	auto & thunder = all_moves(pokemon).emplace_back(Moves::Thunder, 0_bi);
	empty_pp(thunder);
	all_moves(pokemon).emplace_back(Moves::Thunderbolt, 0_bi);

	auto other = Team(1_bi, false);
	other.add_pokemon(Species::Pikachu, Level(100_bi), Gender::female);
	
	auto const selections = legal_selections(user, other.pokemon(), Weather{});
	if (size(selections) != 1_bi) {
		throw std::runtime_error("Incorrect number of selections with one of two moves out of PP. Expected 1, got " + to_string(size(selections)));
	}
	if (front(selections) != Moves::Thunderbolt) {
		throw std::runtime_error("Incorrect legal selection with one of two moves out of PP. Expected Thunderbolt, got " + std::string(to_string(front(selections))));
	}
}

void test_two_moves_with_both_out_of_pp() {
	auto user = Team(1_bi, true);
	auto & pokemon = user.add_pokemon(Species::Pikachu, Level(100_bi), Gender::female);
	auto empty_pp = [](Move & move) {
		while (!move.pp().is_empty()) {
			move.decrement_pp(Ability::Static);
		}
	};
	auto & thunder = all_moves(pokemon).emplace_back(Moves::Thunder, 0_bi);
	empty_pp(thunder);
	auto & thunderbolt = all_moves(pokemon).emplace_back(Moves::Thunderbolt, 0_bi);
	empty_pp(thunderbolt);

	auto other = Team(1_bi, false);
	other.add_pokemon(Species::Pikachu, Level(100_bi), Gender::female);
	
	auto const selections = legal_selections(user, other.pokemon(), Weather{});
	if (size(selections) != 1_bi) {
		throw std::runtime_error("Incorrect number of selections with two of two moves out of PP. Expected 1, got " + to_string(size(selections)));
	}
	if (front(selections) != Moves::Struggle) {
		throw std::runtime_error("Incorrect legal selection with two of two moves out of PP. Expected Struggle, got " + std::string(to_string(front(selections))));
	}
}

}	// namespace

void block_tests() {
	std::cout << "Running block tests.\n";
	test_two_moves_with_one_out_of_pp();
	test_two_moves_with_both_out_of_pp();
}

}	// namespace technicalmachine