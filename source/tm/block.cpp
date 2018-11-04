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

#include <tm/move/move.hpp>
#include <tm/move/moves.hpp>
#include <tm/move/is_switch.hpp>

#include <tm/pokemon/pokemon.hpp>
#include <tm/pokemon/active_pokemon.hpp>

#include <containers/algorithms/all_any_none.hpp>

#include <cassert>

namespace technicalmachine {
namespace {

auto is_blocked_by_bide(ActivePokemon const user, Moves const move) {
	return is_locked_in_to_bide(user) and move == Moves::Bide;
}

auto would_switch_to_different_pokemon(PokemonCollection const & collection, Moves const move) {
	return to_replacement(move) != collection.index();
}

auto is_blocked_from_switching(ActivePokemon const user, Pokemon const & other, Weather const weather) {
	auto const block_attempted = blocks_switching(get_ability(other), user, weather) or trapped(user);
	auto const result = block_attempted and !allows_switching(get_item(user));
	return result;
}

auto is_not_illegal_switch(Team const & user, Moves const move, ActivePokemon const other, Weather const weather) {
	return is_switch(move) ?
		would_switch_to_different_pokemon(user.all_pokemon(), move) and !is_blocked_from_switching(user.pokemon(), other, weather) :
		true;
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
		case Moves::Softboiled:
		case Moves::Swallow:
		case Moves::Synthesis:
		case Moves::Wish:
			return true;
		default:
			return false;
	}
}

auto imprison(Moves const move, ActivePokemon const other) {
	return used_imprison(other) and containers::any_equal(regular_moves(other), move);
}

// Things that both block selection and block execution in between sleep and confusion
auto block1 (ActivePokemon const user, Move const move, ActivePokemon const other) {
	if (!is_regular(move.name())) {
		return false;
	}
	return
		(move.pp().is_empty()) or
		(is_disabled(user, move.name())) or
		(heal_block_is_active(user) and (is_healing(move.name()))) or
		(imprison(move.name(), other));
}

auto is_blocked_by_taunt(Moves const move) {
	return !is_damaging(move);
}

auto is_blocked_by_gravity(Moves const move) {
	switch (move) {
		case Moves::Bounce:
		case Moves::Fly:
		case Moves::Hi_Jump_Kick:
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
	return !is_switch(move) and
			((is_taunted(user) and is_blocked_by_taunt(move)) or
			(weather.gravity() and is_blocked_by_gravity(move)));
}

auto blocked_by_torment(ActivePokemon const user, Moves const move) {
	return is_tormented(user) and last_used_move(user).was_used_last(move) and not is_switch(move) and move != Moves::Struggle;
}

auto is_locked_in(ActivePokemon const user) {
	return is_encored(user) or is_recharging(user) or is_choice_item(get_item(user));
}

auto is_locked_in_to_different_move(ActivePokemon const user, Moves const move) {
	return last_used_move(user).moved_since_switch() and not last_used_move(user).was_used_last(move);
}

auto standard_move_lock_in(ActivePokemon const user, Moves const move) {
	return is_locked_in(user) ? is_locked_in_to_different_move(user, move) : false;
}

auto is_blocked_due_to_lock_in(ActivePokemon const user, Moves const move) {
	return !is_regular(move) ?
		is_recharging(user) :
		standard_move_lock_in(user, move);
}

auto is_legal_selection(Team const & user, Move const move, ActivePokemon const other, Weather const weather, bool const found_selectable_move) {
	auto const & pokemon = user.pokemon();
	if (switch_decision_required(pokemon)) {
		return is_switch(move.name()) and would_switch_to_different_pokemon(user.all_pokemon(), move.name());
	}
	auto const is_pass = move == Moves::Pass;
	if (switch_decision_required(other)) {
		return is_pass;
	}
	if (moved(pokemon)) {
		return is_pass;
	}
	return
		!is_pass and
		!is_blocked_by_bide(pokemon, move.name()) and
		is_not_illegal_switch(user, move.name(), other, weather) and
		(move != Moves::Struggle or !found_selectable_move) and
		!((block1(pokemon, move, other)) or (block2(pokemon, move.name(), weather)) or blocked_by_torment(pokemon, move.name())) and
		!is_blocked_due_to_lock_in(pokemon, move.name());
}

}	// namespace

auto legal_selections(Team const & user, ActivePokemon const other, Weather const weather) -> StaticVectorMove {
	// TODO: implement as
	// auto result = filter(all_moves(user.pokemon()), [] { legal selection; });
	// assert(!empty);
	// return result;
	auto result = StaticVectorMove{};
	for (auto const move : all_moves(user.pokemon())) {
		bool const found_selectable_move = !empty(result);
		if (is_legal_selection(user, move, other, weather, found_selectable_move)) {
			result.emplace_back(move.name());
		}
	}
	assert(!empty(result));
	return result;
}


namespace {

bool is_blocked_by_freeze(Pokemon const & user, Moves const move) {
	return is_frozen(get_status(user)) and !is_usable_while_frozen(move);
}

bool is_blocked_by_sleep(Moves const move) {
	switch (move) {
		case Moves::Sleep_Talk:
		case Moves::Snore:
			return false;
		default:
			return true;
	}
}

bool handle_sleep_counter(MutableActivePokemon user, Moves const move, bool const awakens) {
	if (!is_sleeping(get_status(user))) {
		return false;
	}
	user.increase_sleep_counter(awakens);
	return is_blocked_by_sleep(move);
}

auto is_blocked_due_to_status(MutableActivePokemon user, Moves const move, bool const awakens) {
	return is_blocked_by_freeze(user, move) or handle_sleep_counter(user, move, awakens);
}

}	// namespace

bool can_execute_move(MutableActivePokemon user, Move const move, ActivePokemon const other, Weather const weather, bool const awakens) {
	assert(!is_switch(move.name()) or !is_recharging(user));
	
	if (is_switch(move.name())) {
		return true;
	}
	if (get_hp(user) == 0_bi) {
		return false;
	}

	bool execute = !(is_blocked_due_to_status(user, move.name(), awakens) or
			block1(user, move, other) or
			is_loafing(user));

	if (execute) {
		// Confusion doesn't block execution, it just changes the move that will
		// execute
		user.handle_confusion();
		if (flinched(user)) {
			if (boosts_speed_when_flinched(get_ability(user)))
				boost(stage(user), StatNames::SPE, 1_bi);
			execute = false;
		} else if (block2(user, move.name(), weather) or is_fully_paralyzed(user)) {
			execute = false;
		}
	}

	if (user.recharge())
		execute = false;
	return execute;
}

}	// namespace technicalmachine