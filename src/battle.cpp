// Generic battle
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

#include "battle.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "battle_result.hpp"
#include "endofturn.hpp"
#include "expectiminimax.hpp"
#include "gender.hpp"
#include "move.hpp"
#include "species.hpp"
#include "switch.hpp"
#include "team.hpp"
#include "team_predictor.hpp"
#include "use_move.hpp"
#include "weather.hpp"

#include "network/connect.hpp"
#include "network/outmessage.hpp"

#include "pokemon_lab/write_team_file.hpp"

namespace technicalmachine {

GenericBattle::GenericBattle (std::random_device::result_type seed, std::string const & _opponent, unsigned battle_depth, std::string const & team_file_name):
	opponent (_opponent),
	random_engine (seed),
	ai (6, random_engine, team_file_name),
	depth (battle_depth),
	party (unknown_party)
	{
	for (Pokemon const & pokemon : ai.pokemon.set)
		slot_memory.push_back (pokemon.name);
	initialize_turn ();
}

GenericBattle::GenericBattle (std::random_device::result_type seed, std::string const & _opponent, unsigned battle_depth, Team const & team):
	opponent (_opponent),
	random_engine (seed),
	ai (team),
	depth (battle_depth),
	party (unknown_party)
	{
	for (Pokemon const & pokemon : ai.pokemon.set)
		slot_memory.push_back (pokemon.name);
	initialize_turn ();
}

bool GenericBattle::is_me (uint32_t const other_party) const {
	return party == other_party;
}

void GenericBattle::set_if_party_unknown (uint8_t const new_party) {
 	if (party == 0xFF)
		party = new_party;
}

void GenericBattle::write_team (network::OutMessage & msg, std::string const & username) {
	msg.write_team (ai, username);
}

Team GenericBattle::predict_foe_team (int const detailed [Species::END][7]) const {
	return predict_team (detailed, foe, ai.size);
}

void GenericBattle::handle_begin_turn (uint16_t turn_count) const {
	std::cout << "Begin turn " << turn_count << '\n';
}

void GenericBattle::handle_request_action (network::GenericClient & client, network::OutMessage & msg, uint32_t battle_id, bool can_switch, std::vector <uint8_t> const & attacks_allowed, bool forced) {
	update_from_previous_turn (client, battle_id);
	if (!forced) {
		Move::Moves move = determine_action (client);
		if (Move::is_switch (move))
			msg.write_switch (battle_id, switch_slot (move));
		else {
			uint8_t move_index = 0;
			while (ai.pokemon().move(move_index).name != move)
				++move_index;
			msg.write_move (battle_id, move_index, get_target ());
		}
	}
	else {
		msg.write_move (battle_id, 1);
	}
	if (!ai.replacing)
		initialize_turn ();
}

void GenericBattle::update_from_previous_turn (network::GenericClient & client, uint32_t battle_id) {
	do_turn ();
	correct_hp_and_report_errors (*first);
	correct_hp_and_report_errors (*last);
	std::uniform_int_distribution <unsigned> distribution { 0, client.chattiness - 1 };
	if (distribution (random_engine) == 0)
		client.send_channel_message (battle_id, client.get_response ());
}

Move::Moves GenericBattle::determine_action (network::GenericClient & client) {
	std::cout << std::string (20, '=') + '\n';
	std::cout << "Predicting...\n";
	Team predicted = predict_team (client.detailed, foe, ai.size);
	std::cout << predicted.to_string ();

	return expectiminimax (ai, predicted, weather, depth, client.score, random_engine);
}

void GenericBattle::handle_use_move (uint8_t moving_party, uint8_t slot, Move::Moves move_name) {
	Team & active = is_me (moving_party) ? ai : foe;
	Team & inactive = is_me (moving_party) ? foe : ai;

	if (first == nullptr) {
		first = &active;
		last = &inactive;
	}

	active.moved = true;
	if (!active.at_replacement().find_move (move_name)) {
		Move move (move_name, 3, inactive.size);
		active.at_replacement().move.add (move);
	}
	active.at_replacement().move().variable.reset_index();
	if (active.at_replacement().move().basepower != 0)
		move_damage = true;
}

void GenericBattle::handle_send_out (uint8_t switching_party, uint8_t slot, uint8_t index, std::string const & nickname, Species species, Gender gender, uint8_t level) {
	Team & active = is_me (switching_party) ? ai : foe;
	Team & inactive = is_me (switching_party) ? foe : ai;

	if (first == nullptr) {
		first = &active;
		last = &inactive;
	}

	// This is needed to make sure I don't overwrite important information in a
	// situation in which a team switches multiple times in one turn (due to
	// replacing fainted Pokemon).
	size_t const replacement = active.replacement;
	
	// If it hasn't been seen already, add it to the team.
	if (!active.seen_pokemon (species)) {
		active.add_pokemon (species, nickname, level, gender);
		active.at_replacement ().new_hp = max_damage_precision ();
	}
	
	// Special analysis when a Pokemon is brought out due to a phazing move
	if (inactive.pokemon.set.size() == 0)
		std::cerr << is_me (switching_party) ? "The foe has no Pokemon.\n" : "TM has no Pokemon.\n";
	if (inactive.pokemon.set.size() != 0 and inactive.at_replacement().move().is_phaze()) {
		uint8_t variable_index = 0;
		while (active.pokemon(variable_index).name != species)
			++variable_index;
		inactive.at_replacement().move().variable.set_index(variable_index);
	}
	else if (!active.moved) {
		uint8_t const move_index = active.pokemon(replacement).index_of_first_switch();
		active.pokemon(replacement).move.set_index (move_index + active.replacement);
	}
}

void GenericBattle::handle_health_change (uint8_t party_changing_health, uint8_t slot, int16_t change_in_health, uint16_t remaining_hp, uint16_t denominator) {
	bool const my_team = party_changing_health == party;
	Team & changer = my_team ? ai : foe;
	Team & other = my_team ? foe : ai;
	Pokemon & pokemon = changer.at_replacement();
	if (move_damage) {
		Type const type = other.at_replacement().move().type;
		unsigned const effectiveness = get_effectiveness (type, pokemon);
		if (effectiveness > 0 and (type != Type::GROUND or grounded (changer, weather))) {
			std::cerr << pokemon.to_string() << '\n';
			std::cerr << "pokemon.hp.max: " << static_cast<int> (pokemon.hp.max) << '\n';
			std::cerr << "change_in_health: " << static_cast<int> (change_in_health) << '\n';
			std::cerr << "denominator: " << static_cast<int> (denominator) << '\n';
			std::cerr << "pokemon.hp.stat: " << static_cast<int> (pokemon.hp.stat) << '\n';
			changer.damage = std::min (pokemon.hp.max * change_in_health / static_cast<int>(denominator), static_cast<int> (pokemon.hp.stat));
			std::cerr << "changer.damage: " << static_cast<int> (changer.damage) << '\n';
		}
		move_damage = false;
	}
	pokemon.new_hp = remaining_hp;
}

void GenericBattle::correct_hp_and_report_errors (Team & team) {
	for (Pokemon & pokemon : team.pokemon.set) {
		unsigned const max_hp = (team.me) ? pokemon.hp.max : max_damage_precision ();
		unsigned const tm_estimate = max_hp * pokemon.hp.stat / pokemon.hp.max;
		if (tm_estimate != pokemon.new_hp) {
			unsigned const reported_hp = static_cast<unsigned> (pokemon.new_hp) * pokemon.hp.max / max_hp;
			if (!(tm_estimate - 1 <= pokemon.new_hp and pokemon.new_hp <= tm_estimate + 1)) {
				std::cerr << "Uh oh! " + pokemon.to_string () + " has the wrong HP! The server reports ";
				if (!team.me)
					std::cerr << "approximately ";
				std::cerr << reported_hp << " HP remaining, but TM thinks it has " << pokemon.hp.stat << ".\n";
				std::cerr << "max_hp: " << max_hp << '\n';
				std::cerr << "pokemon.hp.max: " << pokemon.hp.max << '\n';
				std::cerr << "pokemon.hp.stat: " << pokemon.hp.stat << '\n';
				std::cerr << "pokemon.new_hp: " << pokemon.new_hp << '\n';
				std::cerr << "tm_estimate: " << tm_estimate << '\n';
			}
			pokemon.hp.stat = reported_hp;
		}
	}
}

void GenericBattle::handle_set_pp (uint8_t party_changing_pp, uint8_t slot, uint8_t pp) {
}

void GenericBattle::handle_fainted (uint8_t fainting_party, uint8_t slot) {
	Team & fainter = (party == fainting_party) ? ai : foe;
	fainter.at_replacement().fainted = true;
}

void GenericBattle::handle_end (network::GenericClient & client, Result const result) const {
	std::string const verb = to_string (result);
	client.print_with_time_stamp (std::cout, verb + " a battle vs. " + opponent);
	if (result == LOST) {
		pl::write_team (predict_foe_team (client.detailed), client.generate_team_file_name ());
	}
}

uint8_t GenericBattle::switch_slot (Move::Moves move) const {
	uint8_t const slot = Move::to_replacement (move);
	for (uint8_t n = 0; n != slot_memory.size(); ++n) {
		if (slot_memory [n] == ai.pokemon(slot).name)
			return n;
	}
	assert (false);
	return 0;
}

uint16_t GenericBattle::max_damage_precision () const {
	return 48;
}

void GenericBattle::initialize_turn () {
	initialize_team (ai);
	initialize_team (foe);
	// Simulators might not send an HP change message if a move does 0 damage.
	move_damage = false;
	
	first = nullptr;
	last = nullptr;
}

void GenericBattle::initialize_team (Team & team) {
	for (Pokemon & pokemon : team.pokemon.set)
		pokemon.move.reset_index();
	team.ch = false;
	team.fully_paralyzed = false;
	team.hitself = false;
	team.miss = false;
	team.replacement = team.pokemon.index();
}

void GenericBattle::do_turn () {
	first->moved = false;
	last->moved = false;
	if (first->replacing) {
		normalize_hp ();
		switchpokemon (*first, *last, weather);
		first->moved = false;
		normalize_hp ();
		if (last->replacing) {
			switchpokemon (*last, *first, weather);
			last->moved = false;
			normalize_hp ();
			last->replacing = false;
		}
		first->replacing = false;
	}
	else {
		// Anything with recoil will mess this up

		call_move (*first, *last, weather, last->damage);
		last->pokemon().normalize_hp ();

		call_move (*last, *first, weather, first->damage);
		first->pokemon().normalize_hp ();

		endofturn (*first, *last, weather);
		normalize_hp ();
		
		// I only have to check if the foe fainted because if I fainted, I have
		// to make a decision to replace that Pokemon. I update between each
		// decision point so that is already taken into account.
		while (foe.pokemon().fainted) {
			// I suspect this check of is_switch() is not needed and may
			// actually be wrong, but I'm not sure, so I'm leaving it as is.
			if (!foe.pokemon().move().is_switch())
				foe.pokemon().move.set_index (foe.pokemon().index_of_first_switch() + foe.replacement);
			call_move (foe, ai, weather, first->damage);
		}
	}
	std::cout << first->to_string ();
	std::cout << last->to_string ();
}

void GenericBattle::normalize_hp () {
	ai.pokemon().normalize_hp ();
	foe.pokemon().normalize_hp ();
}

} // namespace technicalmachine
