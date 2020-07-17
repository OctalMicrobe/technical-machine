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
#include <containers/legacy_iterator.hpp>

#include <iostream>
#include <random>

namespace technicalmachine {
namespace {
using namespace bounded::literal;

constexpr auto make_depth(unsigned const depth) {
	return Depth(DepthValues{depth, 0U}, 0U);
}

auto shuffled_regular_moves(Generation const generation, auto & random_engine, auto... ts) {
	// Random order to prevent ordering effects from accidentally arriving at
	// the correct move each time
	auto moves = RegularMoves{Move(generation, ts)...};
	std::shuffle(containers::legacy_iterator(begin(moves)), containers::legacy_iterator(end(moves)), random_engine);
	return moves;
}

void ohko_tests(Evaluate const & evaluate, Weather const weather, std::mt19937 & random_engine) {
	constexpr auto generation = Generation::four;
	auto const regular_moves = [&](auto... args) {
		return shuffled_regular_moves(generation, random_engine, args...);
	};
	constexpr auto depth = make_depth(1U);

	auto team1 = Team(1_bi, true);
	team1.add_pokemon(Pokemon(
		generation,
		Species::Jolteon,
		Level(100_bi),
		Gender::male,
		Item::Leftovers,
		Ability::Volt_Absorb,
		CombinedStats<IVAndEV>{
			Nature::Hardy,
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(252_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
		},
		regular_moves(Moves::Thunderbolt, Moves::Charm, Moves::Thunder, Moves::Shadow_Ball)
	));
	team1.pokemon().switch_in(generation, weather);
	team1.reset_start_of_turn();

	auto team2 = Team(1_bi);
	team2.add_pokemon(Pokemon(
		generation,
		Species::Gyarados,
		Level(100_bi),
		Gender::male,
		Item::Leftovers,
		Ability::Intimidate,
		CombinedStats<IVAndEV>{
			Nature::Hardy,
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(252_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
		},
		regular_moves(Moves::Dragon_Dance, Moves::Waterfall, Moves::Stone_Edge, Moves::Taunt)
	));
	team2.pokemon().switch_in(generation, weather);
	team2.reset_start_of_turn();

	{
		auto const best_move = expectiminimax(generation, team1, team2, weather, evaluate, depth, std::cout);
		BOUNDED_ASSERT(best_move.name == Moves::Thunderbolt);
		BOUNDED_ASSERT(best_move.score == double(victory));
	}
	
	auto team3 = Team(1_bi);
	team3.add_pokemon(Pokemon(
		generation,
		Species::Shedinja,
		Level(100_bi),
		Gender::male,
		Item::Lum_Berry,
		Ability::Wonder_Guard,
		CombinedStats<IVAndEV>{
			Nature::Hardy,
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(252_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
		},
		regular_moves(Moves::Swords_Dance, Moves::X_Scissor, Moves::Shadow_Sneak, Moves::Will_O_Wisp)
	));
	team3.pokemon().switch_in(generation, weather);
	team3.reset_start_of_turn();
	
	{
		auto const best_move = expectiminimax(generation, team1, team3, weather, evaluate, depth, std::cout);
		BOUNDED_ASSERT(best_move.name == Moves::Shadow_Ball);
		BOUNDED_ASSERT(best_move.score == double(victory));
	}
}

void one_turn_damage_tests(Evaluate const & evaluate, Weather const weather, std::mt19937 & random_engine) {
	constexpr auto generation = Generation::four;
	auto const regular_moves = [&](auto... args) {
		return shuffled_regular_moves(generation, random_engine, args...);
	};
	constexpr auto depth = make_depth(1U);
	
	auto attacker = Team(1_bi, true);
	attacker.add_pokemon(Pokemon(
		generation,
		Species::Jolteon,
		Level(100_bi),
		Gender::male,
		Item::Leftovers,
		Ability::Volt_Absorb,
		CombinedStats<IVAndEV>{
			Nature::Hardy,
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(252_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
		},
		regular_moves(Moves::Thunderbolt, Moves::Charm, Moves::Thunder, Moves::Shadow_Ball)
	));
	attacker.pokemon().switch_in(generation, weather);
	attacker.reset_start_of_turn();

	auto defender = Team(1_bi);
	defender.add_pokemon(Pokemon(
		generation,
		Species::Swampert,
		Level(100_bi),
		Gender::male,
		Item::Leftovers,
		Ability::Torrent,
		CombinedStats<IVAndEV>{
			Nature::Hardy,
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
		},
		regular_moves(Moves::Surf, Moves::Ice_Beam)
	));
	defender.pokemon().switch_in(generation, weather);
	defender.reset_start_of_turn();

	auto const best_move = expectiminimax(generation, attacker, defender, weather, evaluate, depth, std::cout);
	BOUNDED_ASSERT(best_move.name == Moves::Shadow_Ball);
}

void bellyzard_vs_defensive(Evaluate const & evaluate, Weather const weather, std::mt19937 & random_engine) {
	constexpr auto generation = Generation::four;
	auto const regular_moves = [&](auto... args) {
		return shuffled_regular_moves(generation, random_engine, args...);
	};
	constexpr auto depth = make_depth(2U);

	auto attacker = Team(1_bi, true);
	attacker.add_pokemon(Pokemon(
		generation,
		Species::Charizard,
		Level(100_bi),
		Gender::male,
		Item::Salac_Berry,
		Ability::Blaze,
		CombinedStats<IVAndEV>{
			Nature::Hardy,
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(252_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
		},
		regular_moves(Moves::Fire_Punch, Moves::Belly_Drum, Moves::Earthquake, Moves::Double_Edge)
	));
	attacker.pokemon().switch_in(generation, weather);
	attacker.reset_start_of_turn();

	auto defender = Team(1_bi);
	defender.add_pokemon(Pokemon(
		generation,
		Species::Mew,
		Level(100_bi),
		Gender::male,
		Item::Leftovers,
		Ability::Synchronize,
		CombinedStats<IVAndEV>{
			Nature::Hardy,
			{IV(31_bi), EV(252_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
		},
		regular_moves(Moves::Soft_Boiled)
	));
	defender.pokemon().switch_in(generation, weather);
	defender.reset_start_of_turn();

	auto const best_move = expectiminimax(generation, attacker, defender, weather, evaluate, depth, std::cout);
	BOUNDED_ASSERT(best_move.name == Moves::Belly_Drum);
	BOUNDED_ASSERT(best_move.score == double(victory));
}

void hippopotas_vs_wobbuffet(Evaluate const & evaluate, Weather const weather, std::mt19937 & random_engine) {
	constexpr auto generation = Generation::four;
	auto const regular_moves = [&](auto... args) {
		return shuffled_regular_moves(generation, random_engine, args...);
	};
	constexpr auto depth = make_depth(11U);
	auto attacker = Team(1_bi, true);
	attacker.add_pokemon(Pokemon(
		generation,
		Species::Hippopotas,
		Level(100_bi),
		Gender::male,
		Item::Leftovers,
		Ability::Sand_Stream,
		CombinedStats<IVAndEV>{
			Nature::Adamant,
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(252_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
		},
		regular_moves(Moves::Curse, Moves::Crunch)
	));
	attacker.pokemon().switch_in(generation, weather);
	attacker.reset_start_of_turn();

	// TODO: Implement Encore's effect ending when PP runs out, then Wobbuffet
	// can have Encore

	auto defender = Team(1_bi);
	defender.add_pokemon(Pokemon(
		generation,
		Species::Wobbuffet,
		Level(100_bi),
		Gender::genderless,
		Item::Leftovers,
		Ability::Shadow_Tag,
		CombinedStats<IVAndEV>{
			Nature::Hardy,
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(252_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
		},
		regular_moves(Moves::Counter)
	));
	defender.pokemon().switch_in(generation, weather);
	defender.reset_start_of_turn();

	auto const best_move = expectiminimax(generation, attacker, defender, weather, evaluate, depth, std::cout);
	BOUNDED_ASSERT(best_move.name == Moves::Curse);
	BOUNDED_ASSERT(best_move.score == double(victory));
}


void baton_pass(Evaluate const & evaluate, Weather const weather, std::mt19937 & random_engine) {
	constexpr auto generation = Generation::four;
	auto const regular_moves = [&](auto... args) {
		return shuffled_regular_moves(generation, random_engine, args...);
	};
	constexpr auto depth = Depth(DepthValues{4U, 0U}, 0U);
	auto attacker = Team(2_bi, true);
	attacker.add_pokemon(Pokemon(
		generation,
		Species::Smeargle,
		Level(100_bi),
		Gender::male,
		Item::Leftovers,
		Ability::Own_Tempo,
		CombinedStats<IVAndEV>{
			Nature::Hardy,
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
		},
		regular_moves(Moves::Baton_Pass, Moves::Belly_Drum)
	));
	attacker.pokemon().switch_in(generation, weather);
	attacker.add_pokemon(Pokemon(
		generation,
		Species::Alakazam,
		Level(100_bi),
		Gender::male,
		Item::Lum_Berry,
		Ability::Synchronize,
		CombinedStats<IVAndEV>{
			Nature::Adamant,
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(252_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
		},
		regular_moves(Moves::Psycho_Cut, Moves::Recover)
	));
	attacker.reset_start_of_turn();

	auto defender = Team(2_bi);
	defender.add_pokemon(Pokemon(
		generation,
		Species::Gengar,
		Level(100_bi),
		Gender::male,
		Item::Choice_Specs,
		Ability::Levitate,
		CombinedStats<IVAndEV>{
			Nature::Modest,
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(252_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
		},
		regular_moves(Moves::Shadow_Ball)
	));
	defender.pokemon().switch_in(generation, weather);

	defender.add_pokemon(Pokemon(
		generation,
		Species::Misdreavus,
		Level(100_bi),
		Gender::female,
		Item::Choice_Specs,
		Ability::Levitate,
		CombinedStats<IVAndEV>{
			Nature::Modest,
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(252_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
		},
		regular_moves(Moves::Shadow_Ball)
	));

	defender.reset_start_of_turn();

	auto const best_move = expectiminimax(generation, attacker, defender, weather, evaluate, depth, std::cerr);
	BOUNDED_ASSERT(best_move.name == Moves::Belly_Drum);
	BOUNDED_ASSERT(best_move.score == double(victory));
}


void replace_fainted(Evaluate const & evaluate, std::mt19937 & random_engine) {
	auto weather = Weather{};
	constexpr auto generation = Generation::four;
	auto const regular_moves = [&](auto... args) {
		return shuffled_regular_moves(generation, random_engine, args...);
	};
	constexpr auto depth = make_depth(2U);
	auto attacker = Team(3_bi, true);

	attacker.add_pokemon(Pokemon(
		generation,
		Species::Magikarp,
		Level(5_bi),
		Gender::male,
		Item::Leftovers,
		Ability::Swift_Swim,
		CombinedStats<IVAndEV>{
			Nature::Hardy,
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
		},
		regular_moves(Moves::Tackle)
	));
	attacker.pokemon().switch_in(generation, weather);

	attacker.add_pokemon(Pokemon(
		generation,
		Species::Slugma,
		Level(100_bi),
		Gender::male,
		Item::Choice_Specs,
		Ability::Magma_Armor,
		CombinedStats<IVAndEV>{
			Nature::Hardy,
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
		},
		regular_moves(Moves::Flamethrower, Moves::Earth_Power)
	));
	attacker.add_pokemon(Pokemon(
		generation,
		Species::Zapdos,
		Level(100_bi),
		Gender::genderless,
		Item::Choice_Specs,
		Ability::Pressure,
		CombinedStats<IVAndEV>{
			Nature::Modest,
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(252_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
		},
		regular_moves(Moves::Thunderbolt)
	));

	attacker.reset_start_of_turn();

	auto defender = Team(1_bi);
	defender.add_pokemon(Pokemon(
		generation,
		Species::Suicune,
		Level(100_bi),
		Gender::genderless,
		Item::Leftovers,
		Ability::Pressure,
		CombinedStats<IVAndEV>{
			Nature::Hardy,
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
		},
		regular_moves(Moves::Calm_Mind, Moves::Surf, Moves::Ice_Beam)
	));
	defender.pokemon().switch_in(generation, weather);

	defender.reset_start_of_turn();

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
	
	auto const best_move = expectiminimax(generation, attacker, defender, weather, evaluate, depth, std::cout);
	BOUNDED_ASSERT(best_move.name == Moves::Switch2);
}


void latias_vs_suicune(Evaluate const & evaluate, std::mt19937 & random_engine) {
	auto const weather = Weather{};
	constexpr auto generation = Generation::four;
	auto const regular_moves = [&](auto... args) {
		return shuffled_regular_moves(generation, random_engine, args...);
	};
	constexpr auto depth = make_depth(3U);
	auto attacker = Team(1_bi, true);
	attacker.add_pokemon(Pokemon(
		generation,
		Species::Latias,
		Level(100_bi),
		Gender::female,
		Item::Leftovers,
		Ability::Levitate,
		CombinedStats<IVAndEV>{
			Nature::Calm,
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(120_bi)},
			{IV(31_bi), EV(136_bi)},
			{IV(31_bi), EV(0_bi)},
		},
		regular_moves(Moves::Calm_Mind, Moves::Dragon_Pulse, Moves::Recover)
	));
	attacker.pokemon().switch_in(generation, weather);

	attacker.reset_start_of_turn();

	auto defender = Team(1_bi);
	defender.add_pokemon(Pokemon(
		generation,
		Species::Suicune,
		Level(100_bi),
		Gender::genderless,
		Item::Leftovers,
		Ability::Pressure,
		CombinedStats<IVAndEV>{
			Nature::Calm,
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(120_bi)},
			{IV(31_bi), EV(136_bi)},
			{IV(31_bi), EV(0_bi)},
		},
		regular_moves(Moves::Ice_Beam, Moves::Rest)
	));
	defender.pokemon().switch_in(generation, weather);

	defender.reset_start_of_turn();

	auto const best_move = expectiminimax(generation, attacker, defender, weather, evaluate, depth, std::cout);
	BOUNDED_ASSERT(best_move.name == Moves::Calm_Mind);
}

void sleep_talk(Evaluate const & evaluate, std::mt19937 & random_engine) {
	auto weather = Weather();
	constexpr auto generation = Generation::four;
	auto const regular_moves = [&](auto... args) {
		return shuffled_regular_moves(generation, random_engine, args...);
	};
	constexpr auto depth = make_depth(1U);
	auto attacker = Team(1_bi, true);

	attacker.add_pokemon(Pokemon(
		generation,
		Species::Jolteon,
		Level(100_bi),
		Gender::female,
		Item::Leftovers,
		Ability::Volt_Absorb,
		CombinedStats<IVAndEV>{
			Nature::Hardy,
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
		},
		regular_moves(Moves::Sleep_Talk, Moves::Thunderbolt)
	));
	attacker.pokemon().switch_in(generation, weather);
	attacker.reset_start_of_turn();

	auto defender = Team(1_bi);
	defender.add_pokemon(Pokemon(
		generation,
		Species::Gyarados,
		Level(100_bi),
		Gender::male,
		Item::Life_Orb,
		Ability::Intimidate,
		CombinedStats<IVAndEV>{
			Nature::Adamant,
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
		},
		regular_moves(Moves::Earthquake)
	));
	defender.pokemon().switch_in(generation, weather);

	defender.reset_start_of_turn();
	
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

	BOUNDED_ASSERT(jolteon.status().name() == Statuses::clear);
	BOUNDED_ASSERT(expectiminimax(generation, attacker, defender, weather, evaluate, depth, std::cout).name == Moves::Thunderbolt);

	call_move(generation, attacker, sleep_talk, defender, other_move, weather, keep_status, unknown_damage);
	apply_status_to_self(generation, Statuses::sleep, jolteon, weather);
	next_turn();
	BOUNDED_ASSERT(jolteon.status().name() == Statuses::sleep);
	BOUNDED_ASSERT(expectiminimax(generation, attacker, defender, weather, evaluate, depth, std::cerr).name == Moves::Sleep_Talk);

	call_move(generation, attacker, thunderbolt, defender, other_move, weather, keep_status, unknown_damage);
	next_turn();
	BOUNDED_ASSERT(jolteon.status().name() == Statuses::sleep);
	BOUNDED_ASSERT(expectiminimax(generation, attacker, defender, weather, evaluate, depth, std::cout).name == Moves::Sleep_Talk);

	call_move(generation, attacker, thunderbolt, defender, other_move, weather, keep_status, unknown_damage);
	next_turn();
	BOUNDED_ASSERT(jolteon.status().name() == Statuses::sleep);
	BOUNDED_ASSERT(expectiminimax(generation, attacker, defender, weather, evaluate, depth, std::cout).name == Moves::Sleep_Talk);

	#if 0
		// Same probability of either move
		call_move(generation, attacker, thunderbolt, defender, other_move, weather, keep_status, unknown_damage);
		next_turn();
		BOUNDED_ASSERT(jolteon.status().name() == Statuses::sleep);
		BOUNDED_ASSERT(expectiminimax(generation, attacker, defender, weather, evaluate, depth, std::cout).name == ?);
	#endif
}

void generation_one_frozen_last_pokemon(Evaluate const & evaluate) {
	constexpr auto generation = Generation::one;
	auto weather = Weather();
	auto regular_moves = [](auto const ... name) {
		return RegularMoves{Move(generation, name)...};
	};

	auto attacker = Team(1_bi, true);
	attacker.add_pokemon(Pokemon(
		generation,
		Species::Alakazam,
		Level(100_bi),
		Gender::genderless,
		Item::None,
		Ability::Honey_Gather,
		CombinedStats<IVAndEV>{
			Nature::Hardy,
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
		},
		regular_moves(Moves::Psychic, Moves::Recover, Moves::Thunder_Wave, Moves::Seismic_Toss)
	));
	attacker.pokemon().switch_in(generation, weather);

	auto defender = Team(1_bi);
	{
		auto gengar = Pokemon(
			generation,
			Species::Gengar,
			Level(100_bi),
			Gender::genderless,
			Item::None,
			Ability::Honey_Gather,
			CombinedStats<IVAndEV>{
				Nature::Hardy,
				{IV(31_bi), EV(0_bi)},
				{IV(31_bi), EV(0_bi)},
				{IV(31_bi), EV(0_bi)},
				{IV(31_bi), EV(0_bi)},
				{IV(31_bi), EV(0_bi)},
				{IV(31_bi), EV(0_bi)},
			},
			regular_moves(Moves::Explosion, Moves::Hypnosis, Moves::Thunderbolt, Moves::Night_Shade)
		);
		gengar.set_status(Statuses::freeze);
		gengar.set_hp(12_bi);

		defender.add_pokemon(gengar);
		defender.pokemon().switch_in(generation, weather);
	}
	
	attacker.reset_start_of_turn();
	defender.reset_start_of_turn();

	BOUNDED_ASSERT(expectiminimax(generation, attacker, defender, weather, evaluate, make_depth(1U), std::cout).name == Moves::Psychic);
	BOUNDED_ASSERT(expectiminimax(generation, attacker, defender, weather, evaluate, make_depth(2U), std::cout).name == Moves::Psychic);
}

} // namespace

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
	generation_one_frozen_last_pokemon(evaluate);
	
	std::cout << "Evaluate tests passed.\n\n";
}

}	// namespace technicalmachine
