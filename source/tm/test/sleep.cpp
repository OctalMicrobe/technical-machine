// Copyright (C) 2020 David Stone
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

#include <tm/test/sleep.hpp>

#include <tm/test/incorrect_calculation.hpp>

#include <tm/move/call_move.hpp>
#include <tm/move/moves.hpp>

#include <tm/pokemon/species.hpp>

#include <tm/team.hpp>
#include <tm/weather.hpp>

#include <bounded/assert.hpp>

#include <iostream>

namespace technicalmachine {
namespace {
using namespace bounded::literal;

constexpr auto damage = ActualDamage::Unknown{};	

constexpr auto regular_moves(Generation const generation, auto... moves) {
	return RegularMoves{Move(generation, moves)...};
}

void sleep_talk() {
	constexpr auto generation = Generation::four;
	auto weather = Weather{};
	auto attacker = Team(1_bi, true);
	{
		auto jolteon = Pokemon(
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
				{IV(31_bi), EV(252_bi)},
				{IV(31_bi), EV(0_bi)},
				{IV(31_bi), EV(0_bi)},
			},
			regular_moves(generation, Moves::Sleep_Talk, Moves::Thunderbolt)
		);
		jolteon.set_status(Statuses::sleep);
		
		attacker.add_pokemon(jolteon);
		attacker.pokemon().switch_in(generation, weather);
	}

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
			{IV(31_bi), EV(252_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
			{IV(31_bi), EV(0_bi)},
		},
		RegularMoves({Move(generation, Moves::Earthquake)})
	));
	defender.pokemon().switch_in(generation, weather);

	call_move(
		generation,
		attacker,
		UsedMove{Moves::Sleep_Talk, Moves::Thunderbolt},
		defender,
		FutureMove{false},
		weather,
		false,
		damage
	);
	BOUNDED_ASSERT(defender.pokemon().hp().current() == 0_bi);
}

struct Sleeper {
	explicit Sleeper(Generation const generation):
		m_generation(generation),
		m_sleeper(make_sleeper_team(m_generation, m_weather)),
		m_other(make_other_team(m_generation, m_weather))
	{
	}

	void use_move(Moves const selected, auto... executed) {
		auto pokemon = m_sleeper.pokemon();
		auto const probability_of_awakening = pokemon.status().probability_of_clearing(m_generation, pokemon.ability());
		BOUNDED_ASSERT(probability_of_awakening == 0.0 or probability_of_awakening == 1.0);
		call_move(
			m_generation,
			m_sleeper,
			UsedMove{selected, executed...},
			m_other,
			FutureMove{false},
			m_weather,
			probability_of_awakening == 1.0,
			ActualDamage::Unknown()
		);
	}

	void get_attacked() {
		call_move(
			m_generation,
			m_other,
			UsedMove{Moves::Seismic_Toss},
			m_sleeper,
			FutureMove{false},
			m_weather,
			false,
			ActualDamage::Unknown()
		);
	}

	void end_turn() {
		m_sleeper.reset_start_of_turn();
		m_other.reset_start_of_turn();
	}

	auto at_max_hp() const {
		auto const hp = m_sleeper.pokemon().hp();
		return hp.current() == hp.max();
	}
	auto asleep() const {
		return m_sleeper.pokemon().status().name() == Statuses::rest;
	}
	auto wished() const {
		return m_sleeper.wish_is_active();
	}

private:
	static auto make_team(Generation const generation, bool const is_me, RegularMoves const moves, Weather & weather) {
		auto sleeper = Team(1_bi, is_me);
		sleeper.add_pokemon(Pokemon(
			generation,
			Species::Blissey,
			Level(100_bi),
			Gender::female,
			Item::None,
			Ability::Natural_Cure,
			CombinedStats<IVAndEV>{
				Nature::Hardy,
				{IV(31_bi), EV(0_bi)},
				{IV(31_bi), EV(0_bi)},
				{IV(31_bi), EV(0_bi)},
				{IV(31_bi), EV(0_bi)},
				{IV(31_bi), EV(0_bi)},
				{IV(31_bi), EV(0_bi)},
			},
			moves
		));
		sleeper.pokemon().switch_in(generation, weather);
		return sleeper;
	}
	static auto make_sleeper_team(Generation const generation, Weather & weather) -> Team {
		return make_team(generation, true, regular_moves(generation, Moves::Rest, Moves::Sleep_Talk, Moves::Wish), weather);
	}
	static auto make_other_team(Generation const generation, Weather & weather) -> Team {
		return make_team(generation, false, regular_moves(generation, Moves::Seismic_Toss), weather);
	}

	Generation m_generation;
	Weather m_weather;
	Team m_sleeper;
	Team m_other;
};

void rest() {
	auto sleeper = Sleeper(Generation::three);
	BOUNDED_ASSERT(!sleeper.asleep());
	BOUNDED_ASSERT(sleeper.at_max_hp());
	BOUNDED_ASSERT(!sleeper.wished());


	sleeper.get_attacked();
	BOUNDED_ASSERT(!sleeper.asleep());
	BOUNDED_ASSERT(!sleeper.at_max_hp());
	BOUNDED_ASSERT(!sleeper.wished());

	sleeper.use_move(Moves::Rest);
	BOUNDED_ASSERT(sleeper.asleep());
	BOUNDED_ASSERT(sleeper.at_max_hp());
	BOUNDED_ASSERT(!sleeper.wished());

	sleeper.end_turn();
	BOUNDED_ASSERT(sleeper.asleep());
	BOUNDED_ASSERT(sleeper.at_max_hp());
	BOUNDED_ASSERT(!sleeper.wished());


	sleeper.use_move(Moves::Wish);
	BOUNDED_ASSERT(sleeper.asleep());
	BOUNDED_ASSERT(sleeper.at_max_hp());
	BOUNDED_ASSERT(!sleeper.wished());

	sleeper.get_attacked();
	BOUNDED_ASSERT(sleeper.asleep());
	BOUNDED_ASSERT(!sleeper.at_max_hp());
	BOUNDED_ASSERT(!sleeper.wished());

	sleeper.end_turn();
	BOUNDED_ASSERT(sleeper.asleep());
	BOUNDED_ASSERT(!sleeper.at_max_hp());
	BOUNDED_ASSERT(!sleeper.wished());


	sleeper.use_move(Moves::Wish);
	BOUNDED_ASSERT(sleeper.asleep());
	BOUNDED_ASSERT(!sleeper.at_max_hp());
	BOUNDED_ASSERT(!sleeper.wished());

	sleeper.get_attacked();
	BOUNDED_ASSERT(sleeper.asleep());
	BOUNDED_ASSERT(!sleeper.at_max_hp());
	BOUNDED_ASSERT(!sleeper.wished());

	sleeper.end_turn();
	BOUNDED_ASSERT(sleeper.asleep());
	BOUNDED_ASSERT(!sleeper.at_max_hp());
	BOUNDED_ASSERT(!sleeper.wished());


	sleeper.use_move(Moves::Wish);
	BOUNDED_ASSERT(!sleeper.asleep());
	BOUNDED_ASSERT(!sleeper.at_max_hp());
	BOUNDED_ASSERT(sleeper.wished());
}

void sleep_talk_rest_generation_3() {
	auto sleeper = Sleeper(Generation::three);
	BOUNDED_ASSERT(!sleeper.asleep());
	BOUNDED_ASSERT(sleeper.at_max_hp());
	BOUNDED_ASSERT(!sleeper.wished());


	sleeper.get_attacked();
	BOUNDED_ASSERT(!sleeper.asleep());
	BOUNDED_ASSERT(!sleeper.at_max_hp());
	BOUNDED_ASSERT(!sleeper.wished());

	sleeper.use_move(Moves::Rest);
	BOUNDED_ASSERT(sleeper.asleep());
	BOUNDED_ASSERT(sleeper.at_max_hp());
	BOUNDED_ASSERT(!sleeper.wished());

	sleeper.end_turn();
	BOUNDED_ASSERT(sleeper.asleep());
	BOUNDED_ASSERT(sleeper.at_max_hp());
	BOUNDED_ASSERT(!sleeper.wished());


	sleeper.use_move(Moves::Sleep_Talk, Moves::Rest);
	BOUNDED_ASSERT(sleeper.asleep());
	BOUNDED_ASSERT(sleeper.at_max_hp());
	BOUNDED_ASSERT(!sleeper.wished());

	sleeper.get_attacked();
	BOUNDED_ASSERT(sleeper.asleep());
	BOUNDED_ASSERT(!sleeper.at_max_hp());
	BOUNDED_ASSERT(!sleeper.wished());

	sleeper.end_turn();
	BOUNDED_ASSERT(sleeper.asleep());
	BOUNDED_ASSERT(!sleeper.at_max_hp());
	BOUNDED_ASSERT(!sleeper.wished());


	sleeper.use_move(Moves::Sleep_Talk, Moves::Rest);
	BOUNDED_ASSERT(sleeper.asleep());
	BOUNDED_ASSERT(!sleeper.at_max_hp());
	BOUNDED_ASSERT(!sleeper.wished());

	sleeper.get_attacked();
	BOUNDED_ASSERT(sleeper.asleep());
	BOUNDED_ASSERT(!sleeper.at_max_hp());
	BOUNDED_ASSERT(!sleeper.wished());

	sleeper.end_turn();
	BOUNDED_ASSERT(sleeper.asleep());
	BOUNDED_ASSERT(!sleeper.at_max_hp());
	BOUNDED_ASSERT(!sleeper.wished());


	sleeper.use_move(Moves::Wish);
	BOUNDED_ASSERT(!sleeper.asleep());
	BOUNDED_ASSERT(!sleeper.at_max_hp());
	BOUNDED_ASSERT(sleeper.wished());
}

}	// namespace

void sleep_tests() {
	std::cout << "Running sleep tests.\n";
	sleep_talk();
	rest();
	sleep_talk_rest_generation_3();
	std::cout << "Sleep tests passed.\n\n";
}

}	// namespace technicalmachine
