// Pokemon Lab outgoing messages
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

#ifndef POKEMON_ONLINE__OUTMESSAGE_HPP_
#define POKEMON_ONLINE__OUTMESSAGE_HPP_

#include <cstdint>
#include <string>

#include "../network/outmessage.hpp"

namespace technicalmachine {
class Pokemon;
class Team;
namespace po {

class BattleSettings;

class OutMessage : public network::OutMessage {
	public:
		explicit OutMessage (uint8_t code);
		void write_string (std::string const & str);
		void write_team (Team const & team, std::string const & username);
		void write_pokemon (Pokemon const & pokemon);
		void write_move (uint32_t field_id, uint8_t move_index, uint8_t target = 1);
		void write_switch (uint32_t field_id, uint8_t slot);
		void write_challenge (uint32_t user_id, uint8_t generation, BattleSettings const & settings);
		void write_color ();
		void reset_action_code ();
		void finalize();
		enum Message {
			// WHAT_ARE_YOU and WHO_ARE_YOU are unused.
			LOG_IN = 2,
			LOG_OUT = 3,
			SERVER_MESSAGE = 4,		// "SendMessage"
			PLAYERS_LIST = 5,
			SEND_TEAM = 6,
			CHALLENGE_STUFF = 7,
			BATTLE_BEGIN = 8,			// "EngageBattle"
			BATTLE_FINISHED = 9,
			BATTLE_MESSAGE = 10,
			BATTLE_CHAT = 11,
			KEEP_ALIVE = 12,
			ASK_FOR_PASS = 13,
			REGISTER = 14,
			PLAYER_KICK = 15,
			PLAYER_BAN = 16,
			SERV_NUM_CHANGE = 17,
			SERV_DESC_CHANGE = 18,
			SERV_NAME_CHANGE = 19,
			SEND_PM = 20,
			AWAY = 21,
			GET_USER_INFO = 22,
			GET_USER_ALIAS = 23,
			GET_BANLIST = 24,
			CP_BAN = 25,
			CP_UNBAN = 26,
			SPECTATE_BATTLE = 27,
			SPECTATING_BATTLE_MESSAGE = 28,
			SPECTATING_BATTLE_CHAT = 29,
			SPECTATING_BATTLE_FINISHED = 30,
			LADDER_CHANGE = 31,
			SHOW_TEAM_CHANGE = 32,
			VERSION_CONTROL = 33,
			TIER_SELECTION = 34,
			SERV_MAX_CHANGE = 35,
			FIND_BATTLE = 36,
			SHOW_RANKINGS = 37,
			ANNOUNCEMENT = 38,
			CP_TBAN = 39,
			CP_TUNBAN = 40,
			PLAYER_TBAN = 41,
			GET_TBAN_LIST = 42,
			BATTLE_LIST = 43,
			CHANNELS_LIST = 44,
			CHANNEL_PLAYERS = 45,
			JOIN_CHANNEL = 46,
			LEAVE_CHANNEL = 47,
			CHANNEL_BATTLE = 48,
			REMOVE_CHANNEL = 49,
			ADD_CHANNEL = 50,
			CHANNEL_MESSAGE = 51,
			CHAN_NAME_CHANGE = 52,
			HTML_MESSAGE = 53,
			HTML_CHANNEL = 54,
			SERVER_NAME = 55,
			SPECIAL_PASS = 56,
			SERVER_LIST_END = 57,
			SET_IP = 58
		};
};

}	// namespace po
}	// namespace technicalmachine
#endif	// POKEMON_ONLINE__OUTMESSAGE_HPP_