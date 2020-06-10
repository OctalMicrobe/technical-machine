// Test function that determines the score functions
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

#include <tm/test/evaluate/expectiminimax.hpp>

#include <tm/evaluate/evaluate.hpp>
#include <tm/evaluate/expectiminimax.hpp>

#include <tm/move/call_move.hpp>
#include <tm/move/moves.hpp>

#include <tm/pokemon/species.hpp>

#include <tm/end_of_turn.hpp>
#include <tm/team.hpp>
#include <tm/variable.hpp>
#include <tm/weather.hpp>

#include <bounded/assert.hpp>
#include <bounded/integer.hpp>

#include <containers/array/array.hpp>
#include <containers/append.hpp>

#include <iostream>
#include <random>

namespace technicalmachine {
namespace {
using namespace bounded::literal;

constexpr auto generation = Generation::four;

auto make_shuffled_array(auto & random_engine, auto... ts) {
	// Random order to prevent ordering effects from accidentally arriving at
	// the correct move each time
	auto array = containers::array{Move(generation, ts)...};
	// gcc's stdlib does not support std::shuffle user defined integers
	std::shuffle(data(array), data(array) + size(array), random_engine);
	return array;
}

void ohko_tests(Evaluate const & evaluate, Weather const weather, std::mt19937 & random_engine) {
	auto const shuffled = [&](auto... args) {
		return make_shuffled_array(random_engine, args...);
	};
	constexpr auto depth = Depth(1U, 0U);

	Team team1(1_bi, true);
	{
		team1.add_pokemon(generation, Species::Jolteon, Level(100_bi), Gender::male, Item::Leftovers, Ability::Volt_Absorb, Nature::Timid);
		auto jolteon = team1.pokemon();
		jolteon.switch_in(generation, weather);
		containers::append(regular_moves(jolteon), shuffled(Moves::Thunderbolt, Moves::Charm, Moves::Thunder, Moves::Shadow_Ball));
		set_ev(generation, jolteon, PermanentStat::spa, IV(31_bi), EV(252_bi));
		team1.reset_start_of_turn();
	}

	Team team2(1_bi);
	{
		team2.add_pokemon(generation, Species::Gyarados, Level(100_bi), Gender::male, Item::Leftovers, Ability::Intimidate, Nature::Adamant);
		auto gyarados = team2.pokemon();
		gyarados.switch_in(generation, weather);
		containers::append(regular_moves(gyarados), shuffled(Moves::Dragon_Dance, Moves::Waterfall, Moves::Stone_Edge, Moves::Taunt));
		set_ev(generation, gyarados, PermanentStat::atk, IV(31_bi), EV(252_bi));
		team2.reset_start_of_turn();
	}

	BOUNDED_ASSERT(expectiminimax(generation, team1, team2, weather, evaluate, depth, std::cout) == Moves::Thunderbolt);
	
	Team team3(1_bi);
	{
		team3.add_pokemon(generation, Species::Shedinja, Level(100_bi), Gender::male, Item::Lum_Berry, Ability::Wonder_Guard, Nature::Adamant);
		auto shedinja = team3.pokemon();
		shedinja.switch_in(generation, weather);
		containers::append(regular_moves(shedinja), shuffled(Moves::Swords_Dance, Moves::X_Scissor, Moves::Shadow_Sneak, Moves::Will_O_Wisp));
		set_ev(generation, shedinja, PermanentStat::atk, IV(31_bi), EV(252_bi));
		team3.reset_start_of_turn();
	}
	
	BOUNDED_ASSERT(expectiminimax(generation, team1, team3, weather, evaluate, depth, std::cout) == Moves::Shadow_Ball);
}

void one_turn_damage_tests(Evaluate const & evaluate, Weather const weather, std::mt19937 & random_engine) {
	auto const shuffled = [&](auto... args) {
		return make_shuffled_array(random_engine, args...);
	};
	constexpr auto depth = Depth(1U, 0U);
	
	Team attacker(1_bi, true);
	{
		attacker.add_pokemon(generation, Species::Jolteon, Level(100_bi), Gender::male, Item::Leftovers, Ability::Volt_Absorb, Nature::Timid);
		auto jolteon = attacker.pokemon();
		jolteon.switch_in(generation, weather);
		containers::append(regular_moves(jolteon), shuffled(Moves::Thunderbolt, Moves::Charm, Moves::Thunder, Moves::Shadow_Ball));
		set_ev(generation, jolteon, PermanentStat::spa, IV(31_bi), EV(252_bi));
		attacker.reset_start_of_turn();
	}

	Team defender(1_bi);
	{
		defender.add_pokemon(generation, Species::Swampert, Level(100_bi), Gender::male, Item::Leftovers, Ability::Torrent, Nature::Bold);
		auto swampert = defender.pokemon();
		swampert.switch_in(generation, weather);
		containers::append(regular_moves(swampert), shuffled(Moves::Surf, Moves::Ice_Beam));
		set_ev(generation, swampert, PermanentStat::hp, IV(31_bi), EV(252_bi));
		set_ev(generation, swampert, PermanentStat::def, IV(31_bi), EV(252_bi));
		defender.reset_start_of_turn();
	}

	BOUNDED_ASSERT(expectiminimax(generation, attacker, defender, weather, evaluate, depth, std::cout) == Moves::Shadow_Ball);
}

void bellyzard_vs_defensive(Evaluate const & evaluate, Weather const weather, std::mt19937 & random_engine) {
	auto const shuffled = [&](auto... args) {
		return make_shuffled_array(random_engine, args...);
	};
	constexpr auto depth = Depth(2U, 0U);
	Team attacker(1_bi, true);
	{
		attacker.add_pokemon(generation, Species::Charizard, Level(100_bi), Gender::male, Item::Salac_Berry, Ability::Blaze, Nature::Adamant);
		auto charizard = attacker.pokemon();
		charizard.switch_in(generation, weather);
		containers::append(regular_moves(charizard), shuffled(Moves::Fire_Punch, Moves::Belly_Drum, Moves::Earthquake, Moves::Double_Edge));
		set_ev(generation, charizard, PermanentStat::atk, IV(31_bi), EV(252_bi));
		attacker.reset_start_of_turn();
	}

	Team defender(1_bi);
	{
		defender.add_pokemon(generation, Species::Mew, Level(100_bi), Gender::male, Item::Leftovers, Ability::Synchronize, Nature::Impish);
		auto mew = defender.pokemon();
		mew.switch_in(generation, weather);
		containers::append(regular_moves(mew), shuffled(Moves::Soft_Boiled));
		set_ev(generation, mew, PermanentStat::hp, IV(31_bi), EV(252_bi));
		defender.reset_start_of_turn();
	}

	BOUNDED_ASSERT(expectiminimax(generation, attacker, defender, weather, evaluate, depth, std::cout) == Moves::Belly_Drum);
}

void hippopotas_vs_wobbuffet(Evaluate const & evaluate, Weather const weather, std::mt19937 & random_engine) {
	auto const shuffled = [&](auto... args) {
		return make_shuffled_array(random_engine, args...);
	};
	constexpr auto depth = Depth(7U, 0U);
	Team attacker(1_bi, true);
	{
		attacker.add_pokemon(generation, Species::Hippopotas, Level(100_bi), Gender::male, Item::Leftovers, Ability::Sand_Stream, Nature::Adamant);
		auto hippopotas = attacker.pokemon();
		hippopotas.switch_in(generation, weather);
		containers::append(regular_moves(hippopotas), shuffled(Moves::Curse, Moves::Crunch));
		set_ev(generation, hippopotas, PermanentStat::hp, IV(31_bi), EV(252_bi));
		set_ev(generation, hippopotas, PermanentStat::atk, IV(31_bi), EV(252_bi));
		attacker.reset_start_of_turn();
	}

	Team defender(1_bi);
	{
		defender.add_pokemon(generation, Species::Wobbuffet, Level(100_bi), Gender::genderless, Item::Leftovers, Ability::Shadow_Tag, Nature::Bold);
		auto wobbuffet = defender.pokemon();
		wobbuffet.switch_in(generation, weather);
		containers::append(regular_moves(wobbuffet), shuffled(Moves::Counter, Moves::Encore));
		set_ev(generation, wobbuffet, PermanentStat::hp, IV(31_bi), EV(252_bi));
		set_ev(generation, wobbuffet, PermanentStat::def, IV(31_bi), EV(252_bi));
		defender.reset_start_of_turn();
	}

	BOUNDED_ASSERT(expectiminimax(generation, attacker, defender, weather, evaluate, depth, std::cout) == Moves::Curse);
}


void baton_pass(Evaluate const & evaluate, Weather const weather, std::mt19937 & random_engine) {
	auto const shuffled = [&](auto... args) {
		return make_shuffled_array(random_engine, args...);
	};
	constexpr auto depth = Depth(4U, 0U);
	Team attacker(2_bi, true);
	{
		attacker.add_pokemon(generation, Species::Smeargle, Level(100_bi), Gender::male, Item::Leftovers, Ability::Own_Tempo, Nature::Jolly);
		auto smeargle = attacker.pokemon();
		smeargle.switch_in(generation, weather);
		containers::append(regular_moves(smeargle), shuffled(Moves::Baton_Pass, Moves::Belly_Drum));
	}

	{
		auto & alakazam = attacker.add_pokemon(generation, Species::Alakazam, Level(100_bi), Gender::male, Item::Lum_Berry, Ability::Synchronize, Nature::Jolly);
		containers::append(regular_moves(alakazam), shuffled(Moves::Psycho_Cut, Moves::Recover));
		set_ev(generation, alakazam, PermanentStat::atk, IV(31_bi), EV(252_bi));
	}
	attacker.reset_start_of_turn();

	Team defender(2_bi);
	{
		defender.add_pokemon(generation, Species::Gengar, Level(100_bi), Gender::male, Item::Choice_Specs, Ability::Levitate, Nature::Modest);
		auto gengar = defender.pokemon();
		gengar.switch_in(generation, weather);
		containers::append(regular_moves(gengar), shuffled(Moves::Shadow_Ball));
		set_ev(generation, gengar, PermanentStat::spa, IV(31_bi), EV(252_bi));
	}

	{
		auto & misdreavus = defender.add_pokemon(generation, Species::Misdreavus, Level(100_bi), Gender::female, Item::Choice_Specs, Ability::Levitate, Nature::Modest);
		containers::append(regular_moves(misdreavus), shuffled(Moves::Shadow_Ball));
		set_ev(generation, misdreavus, PermanentStat::spa, IV(31_bi), EV(252_bi));
	}
	defender.reset_start_of_turn();

	BOUNDED_ASSERT(expectiminimax(generation, attacker, defender, weather, evaluate, depth, std::cout) == Moves::Belly_Drum);
}


void replace_fainted(Evaluate const & evaluate, std::mt19937 & random_engine) {
	auto weather = Weather{};
	auto const shuffled = [&](auto... args) {
		return make_shuffled_array(random_engine, args...);
	};
	constexpr auto depth = Depth(2U, 0U);
	Team attacker(3_bi, true);

	attacker.add_pokemon(generation, Species::Magikarp, Level(5_bi), Gender::male, Item::Leftovers, Ability::Swift_Swim, Nature::Jolly);
	attacker.pokemon().switch_in(generation, weather);

	{
		auto & slugma = attacker.add_pokemon(generation, Species::Slugma, Level(100_bi), Gender::male, Item::Choice_Specs, Ability::Magma_Armor, Nature::Jolly);
		containers::append(regular_moves(slugma), shuffled(Moves::Flamethrower, Moves::Earth_Power));
	}

	{
		auto & zapdos = attacker.add_pokemon(generation, Species::Zapdos, Level(100_bi), Gender::genderless, Item::Choice_Specs, Ability::Pressure, Nature::Modest);
		all_moves(zapdos).add(Move(generation, Moves::Thunderbolt));
		set_ev(generation, zapdos, PermanentStat::spa, IV(31_bi), EV(252_bi));
	}
	attacker.reset_start_of_turn();

	Team defender(1_bi);
	{
		defender.add_pokemon(generation, Species::Suicune, Level(100_bi), Gender::genderless, Item::Leftovers, Ability::Pressure, Nature::Bold);
		auto suicune = defender.pokemon();
		suicune.switch_in(generation, weather);
		containers::append(regular_moves(suicune), shuffled(Moves::Calm_Mind, Moves::Surf, Moves::Ice_Beam));
		set_ev(generation, suicune, PermanentStat::hp, IV(31_bi), EV(252_bi));
		set_ev(generation, suicune, PermanentStat::def, IV(31_bi), EV(252_bi));
	}

	call_move(
		generation,
		defender,
		UsedMove{Moves::Surf},
		attacker,
		FutureMove{false},
		weather,
		false,
		ActualDamage::Unknown{}
	);
	
	defender.reset_start_of_turn();

	BOUNDED_ASSERT(expectiminimax(generation, attacker, defender, weather, evaluate, depth, std::cout) == Moves::Switch2);
}


void latias_vs_suicune(Evaluate const & evaluate, std::mt19937 & random_engine) {
	auto const weather = Weather{};
	auto const shuffled = [&](auto... args) {
		return make_shuffled_array(random_engine, args...);
	};
	constexpr auto depth = Depth(3U, 0U);
	Team attacker(1_bi, true);
	{
		attacker.add_pokemon(generation, Species::Latias, Level(100_bi), Gender::female, Item::Leftovers, Ability::Levitate, Nature::Calm);
		auto latias = attacker.pokemon();
		latias.switch_in(generation, weather);
		containers::append(regular_moves(latias), shuffled(Moves::Calm_Mind, Moves::Dragon_Pulse, Moves::Recover));
		set_ev(generation, latias, PermanentStat::hp, IV(31_bi), EV(252_bi));
		set_ev(generation, latias, PermanentStat::spa, IV(31_bi), EV(120_bi));
		set_ev(generation, latias, PermanentStat::spd, IV(31_bi), EV(136_bi));
		attacker.reset_start_of_turn();
	}

	Team defender(1_bi);
	{
		defender.add_pokemon(generation, Species::Suicune, Level(100_bi), Gender::genderless, Item::Leftovers, Ability::Pressure, Nature::Calm);
		auto suicune = defender.pokemon();
		suicune.switch_in(generation, weather);
		containers::append(regular_moves(suicune), shuffled(Moves::Ice_Beam, Moves::Rest));
		set_ev(generation, suicune, PermanentStat::hp, IV(31_bi), EV(252_bi));
		set_ev(generation, suicune, PermanentStat::spa, IV(31_bi), EV(120_bi));
		set_ev(generation, suicune, PermanentStat::spd, IV(31_bi), EV(136_bi));
		defender.reset_start_of_turn();
	}

	BOUNDED_ASSERT(expectiminimax(generation, attacker, defender, weather, evaluate, depth, std::cout) == Moves::Calm_Mind);
}

void sleep_talk(Evaluate const & evaluate, std::mt19937 & random_engine) {
	auto weather = Weather{};
	auto const shuffled = [&](auto... args) {
		return make_shuffled_array(random_engine, args...);
	};
	constexpr auto depth = Depth(1U, 0U);
	auto attacker = Team(1_bi, true);
	{
		attacker.add_pokemon(generation, Species::Jolteon, Level(100_bi), Gender::female, Item::Leftovers, Ability::Volt_Absorb, Nature::Timid);
		auto jolteon = attacker.pokemon();
		jolteon.switch_in(generation, weather);
		containers::append(regular_moves(jolteon), shuffled(Moves::Sleep_Talk, Moves::Thunderbolt));
		set_ev(generation, jolteon, PermanentStat::spa, IV(31_bi), EV(252_bi));
		set_ev(generation, jolteon, PermanentStat::spe, IV(31_bi), EV(252_bi));
		attacker.reset_start_of_turn();
	}

	auto defender = Team(1_bi);
	{
		defender.add_pokemon(generation, Species::Gyarados, Level(100_bi), Gender::male, Item::Life_Orb, Ability::Intimidate, Nature::Adamant);
		auto gyarados = defender.pokemon();
		gyarados.switch_in(generation, weather);
		containers::append(regular_moves(gyarados), shuffled(Moves::Earthquake));
		set_ev(generation, gyarados, PermanentStat::atk, IV(31_bi), EV(252_bi));
		defender.reset_start_of_turn();
	}
	
	constexpr auto keep_status = false;
	constexpr auto unknown_damage = ActualDamage::Unknown{};
	constexpr auto sleep_talk = UsedMove{Moves::Sleep_Talk};
	constexpr auto thunderbolt = UsedMove{Moves::Thunderbolt};
	constexpr auto other_move = FutureMove{false};
	
	auto next_turn = [&]{
		constexpr auto end_of_turn_flags = EndOfTurnFlags(false, false);
		end_of_turn(generation, attacker, end_of_turn_flags, defender, end_of_turn_flags, weather);
		attacker.reset_start_of_turn();
		defender.reset_start_of_turn();
	};

	auto jolteon = attacker.pokemon();
	
	// TODO: Validate score, too

	BOUNDED_ASSERT(get_status(jolteon).name() == Statuses::clear);
	BOUNDED_ASSERT(expectiminimax(generation, attacker, defender, weather, evaluate, depth, std::cout) == Moves::Thunderbolt);

	call_move(generation, attacker, sleep_talk, defender, other_move, weather, keep_status, unknown_damage);
	apply_status_to_self(generation, Statuses::sleep, jolteon, weather);
	next_turn();
	BOUNDED_ASSERT(get_status(jolteon).name() == Statuses::sleep);
	BOUNDED_ASSERT(expectiminimax(generation, attacker, defender, weather, evaluate, depth, std::cerr) == Moves::Sleep_Talk);

	call_move(generation, attacker, thunderbolt, defender, other_move, weather, keep_status, unknown_damage);
	next_turn();
	BOUNDED_ASSERT(get_status(jolteon).name() == Statuses::sleep);
	BOUNDED_ASSERT(expectiminimax(generation, attacker, defender, weather, evaluate, depth, std::cout) == Moves::Sleep_Talk);

	call_move(generation, attacker, thunderbolt, defender, other_move, weather, keep_status, unknown_damage);
	next_turn();
	BOUNDED_ASSERT(get_status(jolteon).name() == Statuses::sleep);
	BOUNDED_ASSERT(expectiminimax(generation, attacker, defender, weather, evaluate, depth, std::cout) == Moves::Sleep_Talk);

	#if 0
		// Same probability of either move
		call_move(generation, attacker, thunderbolt, defender, other_move, weather, keep_status, unknown_damage);
		next_turn();
		BOUNDED_ASSERT(get_status(jolteon).name() == Statuses::sleep);
		BOUNDED_ASSERT(expectiminimax(generation, attacker, defender, weather, evaluate, depth, std::cout) == ?);
	#endif
}

void performance(Evaluate const & evaluate) {
	auto const weather = Weather{};
	constexpr auto depth = Depth(2U, 0U);
	auto add_pokemon = [&](Team & team, Species const species, auto... moves) {
		auto & pokemon = team.add_pokemon(generation, species, Level(100_bi), Gender::genderless, Item::Leftovers, Ability::Pickup, Nature::Hardy);
		containers::append(regular_moves(pokemon), containers::array{Move(generation, moves)...});
		set_ev(generation, pokemon, PermanentStat::hp, IV(31_bi), EV(252_bi));
		set_ev(generation, pokemon, PermanentStat::def, IV(31_bi), EV(120_bi));
		set_ev(generation, pokemon, PermanentStat::spd, IV(31_bi), EV(136_bi));
	};
	Team ai(6_bi, true);
	Team foe(6_bi, false);
	for (auto const species : {Species::Latias, Species::Latios, Species::Tyranitar, Species::Hippowdon, Species::Salamence, Species::Slugma}) {
		for (auto * team : {&ai, &foe}) {
			add_pokemon(*team, species, Moves::Recover, Moves::Dragon_Claw, Moves::Earthquake, Moves::Dragon_Dance);
		}
	}
	ai.pokemon().switch_in(generation, weather);
	foe.pokemon().switch_in(generation, weather);
	ai.reset_start_of_turn();
	foe.reset_start_of_turn();

	expectiminimax(generation, ai, foe, weather, evaluate, depth, std::cout);
}

}	// namespace

void expectiminimax_tests() {
	std::cout << "Running expectiminimax tests.\n";

	Evaluate const evaluate;
	Weather const weather;
	std::random_device rd;
	std::mt19937 random_engine(rd());

	ohko_tests(evaluate, weather, random_engine);
	one_turn_damage_tests(evaluate, weather, random_engine);
	bellyzard_vs_defensive(evaluate, weather, random_engine);
	hippopotas_vs_wobbuffet(evaluate, weather, random_engine);
	baton_pass(evaluate, weather, random_engine);
	replace_fainted(evaluate, random_engine);
	latias_vs_suicune(evaluate, random_engine);
	sleep_talk(evaluate, random_engine);
	performance(evaluate);
	
	std::cout << "Evaluate tests passed.\n\n";
}

}	// namespace technicalmachine
