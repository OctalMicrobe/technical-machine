// Pokemon Online battle logic
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

#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "client.hpp"
#include "conversion.hpp"
#include "inmessage.hpp"
#include "outmessage.hpp"

#include "../network/invalid_simulator_data.hpp"

#include "../../team.hpp"

#include "../../pokemon/pokemon.hpp"

namespace technicalmachine {
namespace po {
namespace {

class Todo {
	public:
		explicit Todo (InMessage & in_msg, std::string const & str):
			msg (in_msg) {
			std::cerr << str + '\n';
		}
		explicit Todo (InMessage & in_msg):
			msg (in_msg) {
		}
		~Todo() {
			while (msg.index != msg.buffer.size ())
				std::cerr << static_cast<int> (msg.read_byte()) << '\n';
		}
	private:
		InMessage & msg;
};

std::array<int8_t, 7> parse_boosts(InMessage & msg);

}	// unnamed namespace

void Battle::handle_message (Client & client, uint32_t battle_id, uint8_t command, Party const party, InMessage & msg) {
	enum {
		SEND_OUT = 0,
		WITHDRAW = 1,		// "SendBack"
		USE_ATTACK = 2,
		OFFER_CHOICE = 3,
		BEGIN_TURN = 4,
		PP_CHANGE = 5,
		HP_CHANGE = 6,
		KO = 7,
		EFFECTIVENESS = 8,
		MISS = 9,
		CRITICAL_HIT = 10,
		NUMBER_OF_HITS = 11,
		STAT_CHANGE = 12,
		STATUS_CHANGE = 13,
		STATUS_MESSAGE = 14,
		FAILED = 15,
		BATTLE_CHAT = 16,
		MOVE_MESSAGE = 17,
		ITEM_MESSAGE = 18,
		NO_TARGET = 19,
		FLINCH = 20,
		RECOIL = 21,
		WEATHER_MESSAGE = 22,
		STRAIGHT_DAMAGE = 23,
		ABILITY_MESSAGE = 24,
		ABS_STATUS_CHANGE = 25, 
		SUBSTITUTE = 26,
		BATTLE_END = 27,
		BLANK_MESSAGE = 28,
		CANCEL_MOVE = 29,
		CLAUSE = 30,
		DYNAMIC_INFO = 31,
		DYNAMIC_STATS = 32,
		SPECTATING = 33,
		SPECTATOR_CHAT = 34,
		ALREADY_STATUSED = 35,
		TEMPORARY_POKEMON_CHANGE = 36,
		CLOCK_START = 37,
		CLOCK_STOP = 38,
		RATED = 39,
		TIER_SECTION = 40,
		END_MESSAGE = 41,
		POINT_ESTIMATE = 42,
		MAKE_YOUR_CHOICE = 43,
		AVOID = 44,
		REARRANGE_TEAM = 45,
		SPOT_SHIFTS = 46
	};
	switch (command) {
		case BEGIN_TURN:
			parse_begin_turn(msg);
			break;
		case SEND_OUT:
			parse_send_out(msg, party);
			break;
		case WITHDRAW:
			// Do nothing.
			break;
		case USE_ATTACK:
			parse_use_attack(msg, party);
			break;
		case STRAIGHT_DAMAGE:
			parse_straight_damage(msg);
			break;
		case HP_CHANGE:
			parse_hp_change(msg, party);
			break;
		case PP_CHANGE:
			parse_pp_change(msg);
			break;
		case KO: {
			constexpr uint8_t slot = 0;
			handle_fainted (party, slot);
			break;
		}
		case EFFECTIVENESS:
			parse_effectiveness(msg);
			break;
		case AVOID:
		case MISS:
			std::cerr << ((command == AVOID) ? "AVOID\n" : "MISS\n");
			handle_miss(party);
			break;
		case NO_TARGET:
			// "But there was no target..."
			break;
		case FAILED:
			// "But it failed!"
			break;
		case CRITICAL_HIT:
			handle_critical_hit(party);
			break;
		case NUMBER_OF_HITS:
			parse_number_of_hits(msg);
			break;
		case STAT_CHANGE:
			parse_stat_change(msg);
			break;
		case STATUS_MESSAGE:
			parse_status_message(msg);
			break;
		case STATUS_CHANGE:
			parse_status_change(msg);
			break;
		case ABS_STATUS_CHANGE:
			parse_abs_status_change(msg);
			break;
		case ALREADY_STATUSED:
			parse_already_statused(msg);
			break;
		case FLINCH:
			handle_flinch(party);
			break;
		case RECOIL:
			parse_recoil(msg);
			break;
		case WEATHER_MESSAGE:
			parse_weather_message(msg);
			break;
		case ABILITY_MESSAGE:
			parse_ability_message(msg, party);
			break;
		case ITEM_MESSAGE:
			parse_item_message(msg, party);
			break;
		case MOVE_MESSAGE:
			parse_move_message(msg);
			break;
		case SUBSTITUTE:
			parse_substitute(msg);
			break;
		case CLAUSE:
			std::cerr << "CLAUSE\n";
			break;
		case DYNAMIC_INFO:
			parse_dynamic_info(msg);
			break;
		case DYNAMIC_STATS:
			parse_dynamic_stats(msg);
			break;
		case SPECTATING:
			parse_spectating(msg);
			break;
		case TEMPORARY_POKEMON_CHANGE:
			parse_temporary_pokemon_change(msg);
			break;
		case CLOCK_START:
			parse_clock_start(msg);
			break;
		case CLOCK_STOP:
			parse_clock_stop(msg);
			break;
		case RATED:
			handle_rated(client, msg);
			break;
		case TIER_SECTION:
			parse_tier_section(msg);
			break;
		case BLANK_MESSAGE:
			// Apparently this is used to tell the client to print a new line...
			break;
		case BATTLE_CHAT:
		case END_MESSAGE:
			std::cerr << ((command == BATTLE_CHAT) ? "BATTLE_CHAT\n" : "END_MESSAGE\n");
			parse_battle_chat(client, msg);
			break;
		case SPECTATOR_CHAT:
			parse_spectator_chat(client, msg, battle_id);
			break;
		case POINT_ESTIMATE:
			parse_point_estimate(msg);
			break;
		case OFFER_CHOICE:
			parse_offer_choice(client, msg, battle_id);
			break;
		case MAKE_YOUR_CHOICE:
			handle_make_your_choice(client);
			break;
		case CANCEL_MOVE:
			handle_cancel_move();
			break;
		case REARRANGE_TEAM:
			parse_rearrange_team(msg);
			break;
		case SPOT_SHIFTS:
			parse_spot_shifts(msg);
			break;
		case BATTLE_END:
			parse_battle_end(msg);
			break;
		default:
			std::cerr << "Unknown battle message " << command << '\n';
			break;
	}
}

void Battle::parse_begin_turn (InMessage & msg) {
	uint32_t const turn = msg.read_int ();
	handle_begin_turn (turn);
}

void Battle::parse_send_out (InMessage & msg, Party const party) {
	bool const is_silent = msg.read_byte ();
	uint8_t const index = msg.read_byte ();
	uint16_t const species_id = msg.read_short ();
	uint8_t const forme_id = msg.read_byte ();
	Species const species = id_to_species (species_id, forme_id);
	std::string const nickname = msg.read_string ();
	uint8_t const hp_percent = msg.read_byte ();
	uint32_t const full_status = msg.read_int ();
	Gender const gender (id_to_gender (msg.read_byte ()));
	bool const shiny = msg.read_byte ();
	uint8_t const level = msg.read_byte ();
	uint8_t const slot = 0;
	handle_send_out (party, slot, index, nickname, species, gender, level);
	if (party == my_party) {
		for (Species & name : slot_memory) {
			if (ai.pokemon.at_replacement ().name == name)
				std::swap (slot_memory.front(), name);
		}
	}
}

void Battle::parse_use_attack (InMessage & msg, Party const party) {
	uint16_t const attack = msg.read_short ();
	constexpr uint8_t slot = 0;
	handle_use_move (party, slot, id_to_move(attack));
}

void Battle::parse_straight_damage (InMessage & msg) {
	damage = msg.read_short ();
}

void Battle::parse_hp_change (InMessage & msg, Party const party) {
	bool const my_team = party == my_party;
	uint16_t const remaining_hp = msg.read_short ();
	int16_t const change_in_hp = calculate_change_in_hp (my_team, remaining_hp);
	damage = 0;
	if (change_in_hp < 0)
		return;
	uint8_t const slot = 0;
	uint16_t const denominator = my_team ? ai.pokemon.at_replacement().hp.max : max_damage_precision ();
	handle_hp_change (party, slot, static_cast<uint16_t>(change_in_hp), remaining_hp, denominator);
}

int16_t Battle::calculate_change_in_hp (bool const my_team, uint16_t const remaining_hp) const {
	return (damage == 0) ?
		(my_team ? ai_change_in_hp (remaining_hp) : foe_change_in_hp (remaining_hp)) :
		damage;
}

void Battle::parse_pp_change (InMessage & msg) {
	uint8_t const move = msg.read_byte ();
	uint8_t const new_pp = msg.read_byte ();
}

void Battle::parse_effectiveness (InMessage & msg) {
	// This matters for Hidden Power. Do nothing with this for now.
	uint8_t const effectiveness = msg.read_byte ();
	// 0, 1, 2, 4, 8, 16
}

void Battle::handle_miss (Party const party) {
	Team & team = is_me (party) ? ai : foe;
	team.set_miss(true);
}

void Battle::handle_critical_hit (Party const party) {
	Team & team = is_me (party) ? ai : foe;
	team.set_critical_hit(true);
}

void Battle::parse_number_of_hits (InMessage & msg) {
	uint8_t const number = msg.read_byte ();
}

void Battle::parse_stat_change (InMessage & msg) {
	std::cerr << "STAT_CHANGE\n";
	// I think stat may work just as well unsigned.
	int8_t const stat = static_cast<int8_t> (msg.read_byte ());
	int8_t const boost = static_cast<int8_t> (msg.read_byte ());
}

void Battle::parse_status_message (InMessage & msg) {
	Todo const t (msg, "STATUS_MESSAGE");
	int8_t const status = static_cast<int8_t> (msg.read_byte ());
}

void Battle::parse_status_change (InMessage & msg) {
	std::cerr << "STATUS_CHANGE\n";
	int8_t const status = static_cast<int8_t> (msg.read_byte());
	// bool const multiple_turns = msg.read_byte ();
	// Includes things like confusion
}

void Battle::parse_abs_status_change (InMessage & msg) {
	uint8_t const index = msg.read_byte();
	if (index >= pokemon_per_team()) {
		std::cerr << "Invalid Pokemon index.\n";
		return;
	}
	int8_t const status = static_cast<int8_t> (msg.read_byte());
}

void Battle::parse_already_statused (InMessage & msg) {
	uint8_t const status = msg.read_byte ();
}

void Battle::handle_flinch (Party const party) {
	std::cerr << "FLINCH\n";
	Team & team = is_me (party) ? ai : foe;
	team.pokemon.at_replacement().move().variable.set_index(1);
}

void Battle::parse_recoil (InMessage & msg) {
	std::cerr << "RECOIL\n";
	bool const damaging = msg.read_byte ();
	if (damaging) {
		// is hit with recoil
	}
	else {
		// had its energy drained
	}
}

void Battle::parse_weather_message (InMessage & msg) {
	std::cerr << "WEATHER_MESSAGE\n";
	int8_t const wstatus = static_cast<int8_t> (msg.read_byte());
	int8_t const weather_var = static_cast<int8_t> (msg.read_byte());
}

void Battle::parse_ability_message (InMessage & msg, Party const party) {
	uint16_t const ability = msg.read_short ();
	uint8_t const part = msg.read_byte ();
	Team & team = (party == my_party) ? ai : foe;
	team.pokemon.at_replacement().ability.name = battle_id_to_ability (ability, part);
	#if 0
	int8_t const type = msg.read_byte ();
	int8_t const foe = msg.read_byte ();
	int16_t const other = msg.read_short ();
	#endif
}

void Battle::parse_item_message (InMessage & msg, Party const party) {
	uint16_t const item_id = msg.read_short ();
	uint8_t const part = msg.read_byte ();
	Item item (battle_id_to_item (item_id, part));
	Team & team = (party == my_party) ? ai : foe;
	team.pokemon.at_replacement().item.name = item.name;
	// int8_t const foe = msg.read_byte ();
	// int16_t const berry = msg.read_short ();
	// int16_t const other = msg.read_short ();
}

void Battle::parse_move_message (InMessage & msg) {
	std::cerr << "MOVE_MESSAGE\n";
	#if 0
	uint16_t const move = msg.read_short ();
	uint8_t const part = msg.read_byte ();
	int8_t const type = msg.read_byte ();
	int8_t const foe = msg.read_byte ();
	int16_t const other = msg.read_short ();
	std::string const q = msg.read_string ();		// No idea what this is
	#endif
}

void Battle::parse_substitute (InMessage & msg) {
	std::cerr << "SUBSTITUTE\n";
	bool const substitute = msg.read_byte ();
}

void Battle::parse_dynamic_info (InMessage & msg) {
	std::array<int8_t, 7> const boosts = parse_boosts(msg);
	enum DynamicFlags {
		Spikes=1,
		SpikesLV2=2,
		SpikesLV3=4,
		StealthRock=8,
		ToxicSpikes=16,
		ToxicSpikesLV2=32
	};
	uint8_t const flags = msg.read_byte ();
}

namespace {

std::array<int8_t, 7> parse_boosts(InMessage & msg) {
	std::array<int8_t, 7> boosts;
	for (int8_t & boost : boosts)
		boost = static_cast<int8_t>(msg.read_byte());
	return boosts;
}

}	// unnamed namespace

void Battle::parse_dynamic_stats (InMessage & msg) {
	for (unsigned n = 0; n != 5; ++n)
		int16_t const something = static_cast<int16_t> (msg.read_short());
}

void Battle::parse_spectating (InMessage & msg) {
	bool const joining = msg.read_byte ();
	uint32_t const user_id = msg.read_int ();
}

void Battle::parse_temporary_pokemon_change (InMessage & msg) {
	Todo const t (msg, "TEMPORARY_POKEMON_CHANGE");
	enum {
		TEMP_MOVE = 0,
		DEF_MOVE = 1,
		TEMP_PP = 2,
		TEMP_SPRITE = 3,
		DEFINITE_FORM = 4,
		AESTHETIC_FORM = 5
	};
	uint8_t const code = msg.read_byte ();
	switch (code) {
		case TEMP_MOVE:
		case DEF_MOVE: {
			std::cerr << "MOVE\n";
			int8_t const slot = static_cast<int8_t> (msg.read_byte ());
			break;
		}
		case TEMP_PP: {
			std::cerr << "TEMP_PP\n";
			int8_t const slot = static_cast<int8_t> (msg.read_byte ());
			int8_t const pp = static_cast<int8_t> (msg.read_byte ());
			break;
		}
		case TEMP_SPRITE: {
			std::cerr << "TEMP_SPRITE\n";
			// ???
			break;
		}
		case DEFINITE_FORM: {
			std::cerr << "DEFINITE_FORM\n";
			int8_t const pokemon = static_cast<int8_t> (msg.read_byte ());
			int16_t const form = static_cast<int16_t> (msg.read_short ());
			break;
		}
		case AESTHETIC_FORM: {
			std::cerr << "AESTHETIC_FORM\n";
			int16_t form = static_cast<int16_t> (msg.read_short ());
			break;
		}
		default:
			std::cerr << "Unknown TEMPORARY_POKEMON_CHANGE code: " << code << '\n';
			break;
	}
}

void Battle::parse_clock_start (InMessage & msg) {
	uint16_t const remaining_time = msg.read_short ();
}

void Battle::parse_clock_stop (InMessage & msg) {
	Todo const t (msg, "CLOCK_STOP");
	uint16_t const remaining_time = msg.read_short ();
}

void Battle::handle_rated (Client & client, InMessage & msg) {
	client.write_team();
	bool const rated = msg.read_byte ();
}

void Battle::parse_tier_section (InMessage & msg) {
	std::string const tier = msg.read_string ();
}

void Battle::parse_battle_chat (Client const & client, InMessage & msg) {
	Todo const t (msg);
	std::string const message = msg.read_string();
	client.print_with_time_stamp (std::cout, message);
}

void Battle::parse_spectator_chat (Client const & client, InMessage & msg, uint32_t const battle_id) {
	std::cerr << "SPECTATOR_CHAT\n";
	uint32_t const user_id = msg.read_int ();
	std::string const message = msg.read_string ();
	client.handle_channel_message (battle_id, client.get_user_name (user_id), message);
}

void Battle::parse_point_estimate (InMessage & msg) {
	Todo const t (msg, "POINT_ESTIMATE");
}

void Battle::parse_offer_choice (Client & client, InMessage & msg, uint32_t const battle_id) {
	int8_t const num_slot = static_cast<int8_t> (msg.read_byte());
	bool const can_switch = msg.read_byte();
	bool const can_attack = msg.read_byte();
	std::vector<uint8_t> attacks_allowed;
	attacks_allowed.reserve(moves_per_pokemon());
	for (unsigned n = 0; n != moves_per_pokemon(); ++n)
		attacks_allowed [n] = msg.read_byte();
	handle_request_action (client, action, battle_id, can_switch, attacks_allowed);
}

void Battle::handle_make_your_choice (Client & client) {
	client.send_message(action);
	action.reset_action_code();
}

void Battle::handle_cancel_move () {
	std::cerr << "CANCEL_MOVE\n";
	// Humans make foolish mistakes. Technical Machine does not.
}

void Battle::parse_rearrange_team (InMessage & msg) {
	Todo const t (msg, "REARRANGE_TEAM");
	for (unsigned n = 0; n != pokemon_per_team(); ++n) {
		uint16_t const species_id = msg.read_short ();
		uint8_t const form_id = msg.read_byte ();
		uint8_t const level = msg.read_byte ();
		uint8_t const gender = msg.read_byte ();
		bool const item = msg.read_byte ();
	}
}

void Battle::parse_spot_shifts (InMessage & msg) {
	std::cerr << "SPOT_SHIFTS\n";
	// Spinda is quite the Pokemon!
	int8_t const s1 = static_cast<int8_t> (msg.read_byte ());
	int8_t const s2 = static_cast<int8_t> (msg.read_byte ());
	bool const silent = msg.read_byte ();
}

void Battle::parse_battle_end (InMessage & msg) {
	// Forfeit, Win, Tie, Close seems to be the four options in order
	uint8_t const result = msg.read_byte ();
}

uint16_t Battle::max_damage_precision () const {
	return 100;
}

uint8_t Battle::get_target () const {
	return 1 - my_party();
}

int16_t Battle::ai_change_in_hp (uint16_t const remaining_hp) const {
	Stat const & hp = ai.pokemon.at_replacement().hp;
	if (hp.max < remaining_hp)
		throw network::InvalidSimulatorData (remaining_hp, static_cast<uint16_t>(0), hp.max, "AI's remaining_hp");
	return hp.stat - remaining_hp;
}

int16_t Battle::foe_change_in_hp (uint16_t const remaining_hp) const {
	if (max_damage_precision() < remaining_hp)
		throw network::InvalidSimulatorData (remaining_hp, static_cast<uint16_t>(0), max_damage_precision(), "Foe's remaining_hp");
	Stat const & hp = foe.pokemon.at_replacement().hp;
	uint16_t const pixel_hp = max_damage_precision() * hp.stat / hp.max;
	return pixel_hp - remaining_hp;
}

}	// namespace po
}	// namespace technicalmachine
