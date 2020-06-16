// Block selection and execution of moves
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

#include <tm/block.hpp>

#include <tm/ability.hpp>
#include <tm/team.hpp>
#include <tm/weather.hpp>

#include <tm/move/category.hpp>
#include <tm/move/move.hpp>
#include <tm/move/moves.hpp>
#include <tm/move/is_switch.hpp>

#include <tm/pokemon/pokemon.hpp>
#include <tm/pokemon/active_pokemon.hpp>

#include <bounded/assert.hpp>

#include <containers/algorithms/all_any_none.hpp>

#include <cassert>

namespace technicalmachine {
namespace {

auto would_switch_to_same_pokemon(PokemonCollection const & collection, Moves const move) {
	return to_replacement(move) == collection.index();
}

auto is_blocked_from_switching(Generation const generation, ActivePokemon const user, ActivePokemon const other, Weather const weather) {
	auto const block_attempted = blocks_switching(generation, other.ability(), user, weather) or user.trapped();
	auto const result = block_attempted and !allows_switching(user.item(generation, weather));
	return result;
}

auto is_illegal_switch(Generation const generation, Team const & user, Moves const move, ActivePokemon const other, Weather const weather) {
	return is_switch(move) and (
		would_switch_to_same_pokemon(user.all_pokemon(), move) or
		is_blocked_from_switching(generation, user.pokemon(), other, weather)
	);
}

auto is_healing(Moves const name) {
	switch (name) {
		case Moves::Heal_Order:
		case Moves::Milk_Drink:
		case Moves::Moonlight:
		case Moves::Morning_Sun:
		case Moves::Recover:
		case Moves::Rest:
		case Moves::Roost:
		case Moves::Slack_Off:
		case Moves::Soft_Boiled:
		case Moves::Swallow:
		case Moves::Synthesis:
		case Moves::Wish:
			return true;
		default:
			return false;
	}
}

auto imprison(Moves const move, ActivePokemon const other) {
	return other.used_imprison() and containers::any_equal(regular_moves(other), move);
}

// Things that both block selection and block execution in between sleep and confusion
auto block1 (ActivePokemon const user, Move const move, ActivePokemon const other) {
	if (!is_regular(move.name())) {
		return false;
	}
	return
		(move.pp().is_empty()) or
		(user.is_disabled(move.name())) or
		(user.heal_block_is_active() and (is_healing(move.name()))) or
		(imprison(move.name(), other));
}

auto is_blocked_by_taunt(Moves const move) {
	return !is_damaging(move);
}

auto is_blocked_by_gravity(Moves const move) {
	switch (move) {
		case Moves::Bounce:
		case Moves::Fly:
		case Moves::High_Jump_Kick:
		case Moves::Jump_Kick:
		case Moves::Magnet_Rise:
		case Moves::Splash:
			return true;
		default:
			return false;
	}
}

// Things that both block selection and block execution after flinching
auto block2(ActivePokemon const user, Moves const move, Weather const weather) {
	return !is_switch(move) and (
		(user.is_taunted() and is_blocked_by_taunt(move)) or
		(weather.gravity() and is_blocked_by_gravity(move))
	);
}

auto blocked_by_torment(ActivePokemon const user, Moves const move) {
	return user.is_tormented() and user.last_used_move().name() == move and not is_switch(move) and move != Moves::Struggle;
}

auto is_locked_in(Generation const generation, ActivePokemon const user, Weather const weather) {
	return user.is_encored() or user.is_locked_in_by_move() or is_choice_item(user.item(generation, weather));
}

auto is_locked_in_to_different_move(Generation const generation, ActivePokemon const user, Moves const move, Weather const weather) {
	if (not is_locked_in(generation, user, weather)) {
		return false;
	}
	auto const last_move = user.last_used_move().name();
	return not is_switch(last_move) and last_move != move;
}

auto is_blocked_due_to_lock_in(Generation const generation, ActivePokemon const user, Moves const move, Weather const weather) {
	return !is_regular(move) ?
		user.is_locked_in_by_move() :
		is_locked_in_to_different_move(generation, user, move, weather);
}

auto is_legal_selection(Generation const generation, Team const & user, Move const move, Team const & other, Weather const weather, bool const found_selectable_move) {
	BOUNDED_ASSERT(move != Moves::Hit_Self);
	auto const pokemon = user.pokemon();
	auto const other_pokemon = other.pokemon();
	if (user.size() > 1_bi and pokemon.switch_decision_required()) {
		return is_switch(move.name()) and !would_switch_to_same_pokemon(user.all_pokemon(), move.name());
	}
	auto const is_pass = move == Moves::Pass;
	if (other.size() > 1_bi and other_pokemon.switch_decision_required()) {
		return is_pass;
	}
	if (pokemon.moved()) {
		return is_pass;
	}
	if (move == Moves::Struggle) {
		return !found_selectable_move;
	}
	return
		!is_pass and
		!is_blocked_due_to_lock_in(generation, pokemon, move.name(), weather) and
		!is_illegal_switch(generation, user, move.name(), other_pokemon, weather) and
		!block1(pokemon, move, other_pokemon) and
		!block2(pokemon, move.name(), weather) and
		!blocked_by_torment(pokemon, move.name());
}

}	// namespace

auto legal_selections(Generation const generation, Team const & user, Team const & other, Weather const weather) -> StaticVectorMove {
	// TODO: implement as
	// auto result = filter(user.pokemon().all_moves(), [] { legal selection; });
	// BOUNDED_ASSERT(!empty);
	// return result;
	auto result = StaticVectorMove{};
	for (auto const move : user.pokemon().all_moves()) {
		bool const found_selectable_move = !empty(result);
		if (is_legal_selection(generation, user, move, other, weather, found_selectable_move)) {
			containers::push_back(result, move.name());
		}
	}
	BOUNDED_ASSERT(!empty(result));
	return result;
}


namespace {

bool is_blocked_by_freeze(Pokemon const & user, Moves const move) {
	return is_frozen(user.status()) and !is_usable_while_frozen(move);
}

constexpr bool usable_while_sleeping(Moves const move) {
	switch (move) {
		case Moves::Sleep_Talk:
		case Moves::Snore:
			return true;
		default:
			return false;
	}
}

bool is_blocked_by_sleep(Generation const generation, Pokemon const & user, Moves const move, bool const user_was_asleep) {
	return generation == Generation::one ? user_was_asleep : usable_while_sleeping(move) != is_sleeping(user.status());
}

auto is_blocked_due_to_status(Generation const generation, Pokemon const & user, Moves const move, bool const user_was_asleep) {
	return is_blocked_by_freeze(user, move) or is_blocked_by_sleep(generation, user, move, user_was_asleep);
}

}	// namespace

auto can_attempt_move_execution(Generation const generation, ActivePokemon user, Move const move, ActivePokemon const other, bool const user_was_asleep) -> bool {
	if (is_switch(move.name())) {
		return true;
	}
	if (get_hp(user) == 0_bi) {
		return false;
	}

	auto const blocked_due_to_status = is_blocked_due_to_status(generation, user, move.name(), user_was_asleep);
	if (blocked_due_to_status or block1(user, move, other) or user.is_loafing()) {
		return false;
	}
	return true;
}

auto can_execute_move(ActivePokemon user, Move const move, Weather const weather, bool const is_recharging) -> bool {
	// TODO: handle is_fully_paralyzed
	constexpr auto is_fully_paralyzed = false;
	auto const switching = is_switch(move.name());
	if (switching or move.name() == Moves::Hit_Self) {
		BOUNDED_ASSERT(!is_recharging or (switching and get_hp(user).current() == 0_bi));
		return true;
	}
	return !user.flinched() and !block2(user, move.name(), weather) and !is_fully_paralyzed and !is_recharging;
}

}	// namespace technicalmachine
