// Test stat calculations
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

#include "stat.hpp"

#include <iostream>
#include <string>

#include "incorrect_calculation.hpp"

#include "../team.hpp"
#include "../weather.hpp"

#include "../pokemon/species.hpp"

#include "../stat/stat.hpp"

namespace technicalmachine {
namespace {

constexpr unsigned team_size = 6;

void attack_tests () {
	std::cout << "\tRunning Attack tests.\n";
	constexpr unsigned max_attack = 7368;
	Team attacker;

	constexpr unsigned level = 100;
	Gender const gender(Gender::MALE);
	attacker.add_pokemon(Species::SHUCKLE, level, gender);
	Pokemon & pokemon = attacker.pokemon();

	pokemon.def.ev = 252 / 4;
	pokemon.nature.name = Nature::IMPISH;
	attacker.activate_power_trick();
	pokemon.ability.name = Ability::PURE_POWER;
	attacker.stat_boost(Stat::ATK, 6);

	pokemon.item.name = Item::CHOICE_BAND;
	
	calculate_attack(attacker, Weather ());
	if (attacker.pokemon().atk.stat != max_attack)
		throw IncorrectCalculation (attacker.pokemon().atk.stat, max_attack);
}

void special_attack_tests () {
	std::cout << "\tRunning Special Attack tests.\n";
	constexpr unsigned max_special_attack = 4536;
	Weather weather;
	weather.set_sun (Weather::Duration::permanent);
	Team attacker;

	constexpr unsigned level = 100;
	Gender const gender(Gender::GENDERLESS);
	attacker.add_pokemon(Species::DEOXYS_A, 100, gender);
	Pokemon & pokemon = attacker.pokemon();

	pokemon.spa.ev = 252 / 4;
	pokemon.nature.name = Nature::MODEST;
	attacker.stat_boost(Stat::SPA, 6);

	pokemon.ability.name = Ability::SOLAR_POWER;

	pokemon.item.name = Item::CHOICE_SPECS;
	
	calculate_special_attack(attacker, weather);
	if (attacker.pokemon().spa.stat != max_special_attack)
		throw IncorrectCalculation (attacker.pokemon().spa.stat, max_special_attack);
}

void defense_tests () {
	std::cout << "\tRunning Defense tests.\n";
	constexpr unsigned max_defense = 3684;

	Team defender;

	constexpr unsigned level = 100;
	Gender const gender(Gender::MALE);
	defender.add_pokemon(Species::SHUCKLE, 100, gender);
	Pokemon & pokemon = defender.pokemon();
	pokemon.def.ev = 252 / 4;
	pokemon.nature.name = Nature::BOLD;

	defender.stat_boost(Stat::DEF, 6);

	pokemon.ability.name = Ability::MARVEL_SCALE;
	Status::apply<Status::BURN>(pokemon, Weather());

	calculate_defense(defender);

	if (pokemon.def.stat != max_defense)
		throw IncorrectCalculation (pokemon.def.stat, max_defense);
}

void special_defense_tests () {
	std::cout << "\tRunning Special Defense tests.\n";
	constexpr unsigned max_special_defense = 3684;

	Team defender;
	Weather weather;
	weather.set_sand (Weather::Duration::permanent);

	constexpr unsigned level = 100;
	Gender const gender(Gender::MALE);
	defender.add_pokemon(Species::SHUCKLE, level, gender);
	Pokemon & pokemon = defender.pokemon();
	pokemon.spd.ev = 252 / 4;
	pokemon.nature.name = Nature::CALM;

	defender.stat_boost(Stat::SPD, 6);

	calculate_special_defense(defender, weather);

	if (pokemon.spd.stat != max_special_defense)
		throw IncorrectCalculation (pokemon.spd.stat, max_special_defense);
}

void speed_tests () {
	std::cout << "\tRunning Speed tests.\n";
	constexpr unsigned max_speed = 12096;
	Weather weather;
	weather.set_rain (Weather::Duration::permanent);

	Team team;

	constexpr unsigned level = 100;
	Gender const gender(Gender::GENDERLESS);
	team.add_pokemon(Species::DEOXYS_S, level, gender);
	Pokemon & pokemon = team.pokemon();
	pokemon.spe.ev = 252 / 4;
	pokemon.nature.name = Nature::TIMID;

	team.stat_boost(Stat::SPE, 6);

	pokemon.ability.name = Ability::SWIFT_SWIM;

	pokemon.item.name = Item::CHOICE_SCARF;
	
	team.screens.activate_tailwind();
	
	calculate_speed(team, weather);

	if (pokemon.spe.stat != max_speed)
		throw IncorrectCalculation (pokemon.spe.stat, max_speed);
}

}	// unnamed namespace

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