// Test stat calculations
// Copyright (C) 2016 David Stone
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

#include <tm/test/stat.hpp>

#include <tm/test/incorrect_calculation.hpp>

#include <tm/team.hpp>
#include <tm/weather.hpp>

#include <tm/pokemon/max_pokemon_per_team.hpp>
#include <tm/pokemon/species.hpp>

#include <tm/stat/calculate.hpp>
#include <tm/stat/stat.hpp>

#include <iostream>
#include <string>

namespace technicalmachine {
namespace {
using namespace bounded::literal;

constexpr auto critical_hit = false;

void attack_tests () {
	std::cout << "\tRunning Attack tests.\n";
	constexpr auto max_attack = 7368_bi;
	Team attacker(max_pokemon_per_team);

	Level const level(100_bi);
	attacker.add_pokemon(Species::Shuckle, level, Gender::male);
	Pokemon & pokemon = attacker.pokemon();

	set_stat_ev(pokemon, StatNames::DEF, EV(EV::max));
	get_nature(pokemon) = Nature::Impish;
	attacker.pokemon().activate_power_trick();
	get_ability(pokemon) = Ability::Pure_Power;
	boost(stage(attacker.pokemon()), StatNames::ATK, 6_bi);

	get_item(pokemon) = Item::Choice_Band;
	
	check_equal(calculate_attack(attacker.pokemon(), Weather{}, critical_hit), max_attack);
}

void special_attack_tests () {
	std::cout << "\tRunning Special Attack tests.\n";
	constexpr auto max_special_attack = 4536_bi;
	Weather weather;
	weather.activate_sun(Weather::Duration::permanent);
	Team attacker(max_pokemon_per_team);

	Level const level(100_bi);
	attacker.add_pokemon(Species::Deoxys_Attack, level, Gender::genderless);
	Pokemon & pokemon = attacker.pokemon();

	set_stat_ev(pokemon, StatNames::SPA, EV(EV::max));
	get_nature(pokemon) = Nature::Modest;
	boost(stage(attacker.pokemon()), StatNames::SPA, 6_bi);

	get_ability(pokemon) = Ability::Solar_Power;

	get_item(pokemon) = Item::Choice_Specs;
	
	check_equal(calculate_special_attack(attacker.pokemon(), weather, critical_hit), max_special_attack);
}

void max_defense_test() {
	std::cout << "\t\tRunning max Defense test.\n";
	constexpr auto max_defense = 3684_bi;

	Team defender(max_pokemon_per_team);
	Weather weather;

	Level const level(100_bi);
	defender.add_pokemon(Species::Shuckle, level, Gender::male);
	Pokemon & pokemon = defender.pokemon();
	set_stat_ev(pokemon, StatNames::DEF, EV(EV::max));
	get_nature(pokemon) = Nature::Bold;

	boost(stage(defender.pokemon()), StatNames::DEF, 6_bi);

	get_ability(pokemon) = Ability::Marvel_Scale;
	apply(Statuses::burn, pokemon, weather);

	check_equal(calculate_defense(defender.pokemon(), weather), max_defense);
}

void min_defense_test() {
	std::cout << "\t\tRunning min Defense test.\n";
	constexpr auto min_defense = 1_bi;

	Team defender(max_pokemon_per_team);

	Level const level(1_bi);
	defender.add_pokemon(Species::Combee, level, Gender::male);
	auto pokemon = defender.pokemon();
	set_stat_ev(pokemon, StatNames::DEF, EV(0_bi));
	get_nature(pokemon) = Nature::Hasty;

	for (auto const n [[maybe_unused]] : containers::integer_range(3_bi)) {
		boost(stage(pokemon), StatNames::DEF, -2_bi);
	}

	check_equal(calculate_defense(defender.pokemon(), Weather{}), min_defense);
}

void defense_tests () {
	std::cout << "\tRunning Defense tests.\n";
	max_defense_test();
	min_defense_test();
}

void special_defense_tests () {
	std::cout << "\tRunning Special Defense tests.\n";
	constexpr auto max_special_defense = 3684_bi;

	Team defender(max_pokemon_per_team);
	Weather weather;
	weather.activate_sand(Weather::Duration::permanent);

	Level const level(100_bi);
	defender.add_pokemon(Species::Shuckle, level, Gender::male);
	Pokemon & pokemon = defender.pokemon();
	set_stat_ev(pokemon, StatNames::SPD, EV(EV::max));
	get_nature(pokemon) = Nature::Calm;

	boost(stage(defender.pokemon()), StatNames::SPD, 6_bi);

	check_equal(calculate_special_defense(defender.pokemon(), weather), max_special_defense);
}

void speed_tests () {
	std::cout << "\tRunning Speed tests.\n";
	constexpr auto max_speed = 12096_bi;
	Weather weather;
	weather.activate_rain(Weather::Duration::permanent);

	Team team(max_pokemon_per_team);

	Level const level(100_bi);
	team.add_pokemon(Species::Deoxys_Speed, level, Gender::genderless);
	Pokemon & pokemon = team.pokemon();
	set_stat_ev(pokemon, StatNames::SPE, EV(EV::max));
	get_nature(pokemon) = Nature::Timid;

	boost(stage(team.pokemon()), StatNames::SPE, 6_bi);

	get_ability(pokemon) = Ability::Swift_Swim;

	get_item(pokemon) = Item::Choice_Scarf;
	
	team.screens.activate_tailwind();
	
	check_equal(calculate_speed(team, weather), max_speed);
}

}	// namespace

void stat_tests () {
	std::cout << "Running stat tests.\n";
	attack_tests ();
	special_attack_tests ();
	defense_tests ();
	special_defense_tests ();
	speed_tests ();
	std::cout << "Stat tests passed.\n\n";
}

}	// namespace technicalmachine