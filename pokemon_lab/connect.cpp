// Connect to Pokemon Lab
// Copyright 2011 David Stone
//
// This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License
// as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "connect.h"
#include "inmessage.h"
#include "outmessage.h"

#include "../crypt/md5.hpp"
#include "../crypt/sha2.hpp"
#include "../crypt/rijndael.h"


namespace technicalmachine {
namespace pl {

BotClient::BotClient (std::string const & host, std::string const & port, std::string const & user, std::string const & pswd):
	username (user),
	password (pswd),
	socket (io) {
	boost::asio::ip::tcp::resolver resolver (io);
	boost::asio::ip::tcp::resolver::query query (host, port);
	boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve (query);
	boost::asio::ip::tcp::resolver::iterator end;
	boost::system::error_code error = boost::asio::error::host_not_found;
	while (error and endpoint_iterator != end) {
		socket.close();
		socket.connect (*endpoint_iterator++, error);
	}
	authenticate();
}

void BotClient::authenticate () {
	OutMessage message (OutMessage::REQUEST_CHALLENGE);
	message.write_string (username);
	send (message);
}

std::string BotClient::get_shared_secret (int secret_style, std::string const & salt) {
	if (secret_style == 0)
		return password;
	else if (secret_style == 1)
		return getMD5HexHash (password);
	else if (secret_style == 2)
		return getMD5HexHash (getMD5HexHash (password) + salt);
	else {
		std::cerr << "Unknown secret style of " << secret_style << '\n';
		return "";
	}	
}

std::string BotClient::get_challenge_response (std::string const & challenge, int secret_style, std::string const & salt) {
	std::string digest = getSHA256Hash (get_shared_secret (secret_style, salt));
	rijndael_ctx ctx;
	rijndael_set_key (&ctx, reinterpret_cast <unsigned char const *> (digest.substr (16, 16).c_str()), 128);
	unsigned char middle [16];
	rijndael_decrypt (&ctx, reinterpret_cast <unsigned char const *> (challenge.c_str()), middle);
	rijndael_set_key (&ctx, reinterpret_cast <unsigned char const *> (digest.substr (0, 16).c_str()), 128);
	unsigned char result [16];
	rijndael_decrypt (&ctx, middle, result);
	
	uint32_t r = (result [0] << 3 * 8) + (result [1] << 2 * 8) + (result [2] << 1 * 8) + result [3] + 1;
	r = htonl (r);

	unsigned char response_array [16] = { 0 };
	uint8_t * byte = reinterpret_cast <uint8_t *> (&r);
	for (unsigned n = 0; n != sizeof (uint32_t); ++n)
		response_array [n] = (*(byte + n));
	rijndael_set_key (&ctx, reinterpret_cast <unsigned char const *> (digest.substr (0, 16).c_str()), 128);
	rijndael_encrypt (&ctx, response_array, middle);
	rijndael_set_key (&ctx, reinterpret_cast <unsigned char const *> (digest.substr (16, 16).c_str()), 128);
	rijndael_encrypt (&ctx, middle, response_array);
	std::string response = "";
	for (unsigned n = 0; n != 16; ++n)
		response += response_array [n];
	return response;
}

void BotClient::send (OutMessage message) {
	message.finalize (socket);
}

/*void activity_proxy (BotClient & client) {
	while (true) {
		boost::asio::deadline_timer timer (client.io, boost::posix_time::seconds (45));
		timer.wait ();
		std::cout << "sending activity notice\n";
		client.send (OutMessage (OutMessage::CLIENT_ACTIVITY));
	}
}*/

void BotClient::run () {
	while (true) {
		InMessage msg;
		// read in the five byte header
		msg.recvfully (socket, 5);

		// extract the message type and length components
		InMessage::Message code = static_cast <InMessage::Message> (msg.read_byte ());
		uint32_t length = msg.read_int ();

		// read in the whole message
		msg.recvfully (socket, length);
		handle_message (code, msg);
	}
}

class Channel {
	public:
		std::string name;
		uint8_t type;
		std::string topic;
		uint32_t population;
		Channel (InMessage & msg):
			name (msg.read_string()),
			type (msg.read_byte()),
			topic (msg.read_string()),
			population (msg.read_int()) {
		}
};

class Metagame {
	public:
		uint8_t index;
		std::string name;
		std::string id;
		std::string description;
		uint8_t party_size;
		uint8_t max_team_length;

		std::vector <uint16_t> bans;
		std::vector <std::string> clauses;

		bool timing;
		uint16_t pool_length;
		uint8_t periods;
		uint16_t period_length;
	private:
		void load_bans (InMessage &msg) {
			uint16_t ban_list_count = msg.read_short ();
			for (uint16_t n = 0; n != ban_list_count; ++n) {
				uint16_t species_id = msg.read_short ();
				bans.push_back (species_id);
			}
		}
		void load_clauses (InMessage &msg) {
			uint16_t clause_count = msg.read_short ();
			for (uint16_t b = 0; b != clause_count; ++b) {
				std::string clause_name = msg.read_string ();
				clauses.push_back (clause_name);
			}
		}
		void load_timer (InMessage &msg) {
			timing = msg.read_byte ();
			if (timing) {
				pool_length = msg.read_short ();
				periods = msg.read_byte ();
				period_length = msg.read_short ();
			}
		}
	public:
		Metagame (InMessage &msg):
			index (msg.read_byte ()),
			name (msg.read_string ()),
			id (msg.read_string ()),
			description (msg.read_string ()),
			party_size (msg.read_byte ()),
			max_team_length (msg.read_byte ()),
			pool_length (-1),
			periods (-1),
			period_length (-1) {
			load_bans (msg);
			load_clauses (msg);
			load_timer (msg);
		}
};

void BotClient::handle_message (InMessage::Message & code, InMessage & msg) {
	switch (code) {
		case InMessage::WELCOME_MESSAGE: {
			uint32_t version = msg.read_int();
			std::string server_name = msg.read_string();
			std::string message = msg.read_string();
			handle_welcome_message (version, server_name, message);
			break;
		}
		case InMessage::PASSWORD_CHALLENGE:
			handle_challenge (msg);
			break;
		case InMessage::REGISTRY_RESPONSE: {
			uint8_t type = msg.read_byte();
			std::string details = msg.read_string();
			handle_registry_response (type, details);
			break;
		}
		case InMessage::CHANNEL_INFO: {
			uint32_t id = msg.read_int();
			uint8_t info = msg.read_byte();
			std::string channel_name = msg.read_string();
			std::string topic = msg.read_string();
			uint32_t channel_flags = msg.read_int();
			uint32_t number_of_users = msg.read_int();
			std::vector <std::pair <std::string, uint32_t> > users;
			for (uint32_t n = 0; n != number_of_users; ++n) {
				std::string username = msg.read_string();
				uint32_t flags = msg.read_int();
				std::pair <std::string, uint32_t> user (username, flags);
				users.push_back (user);
			}
			handle_channel_info (id, info, channel_name, topic, channel_flags, users);
			break;
		}
		case InMessage::CHANNEL_JOIN_PART: {
			uint32_t id = msg.read_int();
			std::string user = msg.read_string();
			bool joining = msg.read_byte();
			handle_channel_join_part (id, user, joining);
			break;
		}
		case InMessage::CHANNEL_STATUS: {
			uint32_t channel_id = msg.read_int();
			std::string invoker = msg.read_string();
			std::string user = msg.read_string();
			uint32_t flags = msg.read_int();
			handle_channel_status (channel_id, invoker, user, flags);
			break;
		}
		case InMessage::CHANNEL_LIST: {
			uint32_t number_of_channels = msg.read_int();
			std::vector <Channel> channels;
			for (uint32_t n = 0; n != number_of_channels; ++n) {
				Channel channel (msg);
				channels.push_back (channel);
			}
			handle_channel_list (channels);
			break;
		}
		case InMessage::CHANNEL_MESSAGE: {
			uint32_t channel_id = msg.read_int();
			std::string user = msg.read_string ();
			std::string message = msg.read_string ();
			handle_channel_message (channel_id, user, message);
			break;
		}
		case InMessage::INCOMING_CHALLENGE: {
			std::string user = msg.read_string ();
			uint8_t generation = msg.read_byte ();
			uint32_t active_party_size = msg.read_int ();
			uint32_t max_team_length = msg.read_int ();
			handle_incoming_challenge (user, generation, active_party_size, max_team_length);
			break;
		}
		case InMessage::FINALIZE_CHALLENGE: {
			std::string user = msg.read_string ();
			bool accepted = msg.read_byte ();
			handle_finalize_challenge (user, accepted);
			break;
		}
		case InMessage::BATTLE_BEGIN: {
			uint32_t field_id = msg.read_int ();
			std::string opponent = msg.read_string ();
			uint8_t party = msg.read_byte ();
			handle_battle_begin (field_id, opponent, party);
			break;
		}
		case InMessage::REQUEST_ACTION: {
			uint32_t field_id = msg.read_int ();
			uint8_t slot = msg.read_byte ();
			uint8_t position = msg.read_byte ();
			bool replace = msg.read_byte ();
			uint8_t request_sequences = msg.read_byte ();
			uint8_t sequential_requests = msg.read_byte ();
			uint32_t number_of_pokemon = msg.read_int ();
			std::vector <uint8_t> switches;
			for (uint32_t n = 0; n != number_of_pokemon; ++n) {
				// Whether it's legal to switch to this Pokemon
				bool can_switch_to = msg.read_byte ();
				switches.push_back (can_switch_to);
			}

			bool can_switch = false;
			bool forced = false;
			std::vector <uint8_t> moves;
			if (!replace) {
				can_switch = msg.read_byte ();
				forced = msg.read_byte ();
				if (!forced) {
					uint8_t num_moves = msg.read_int ();
					for (uint8_t n = 0; n != num_moves; ++n)
						moves.push_back (msg.read_byte ());
				}
			}
			bool can_switch_to = false;
			for (std::vector <uint8_t>::const_iterator it = switches.begin(); it != switches.end(); ++it) {
				if (*it) {
					can_switch_to = true;
					break;
				}
			}
			can_switch = can_switch_to;
			handle_request_action (field_id, slot, position, replace, switches, can_switch, forced, moves);
			break;
		}
		case InMessage::BATTLE_POKEMON: {
			// int32 : field id
			// for 0..1:
			//	 for 0..n-1:
			//		 int16 : species id
			//		 if id != -1:
			//			 byte: gender
			//			 byte: level
			//			 byte: shiny
		   
			// the bot probably doesn't need to care about this
			msg.skip ();
			break;
		}
		case InMessage::BATTLE_PRINT: {
			uint32_t field_id = msg.read_int ();
			uint8_t category = msg.read_byte ();
			uint16_t message_id = msg.read_short ();
			uint8_t argc = msg.read_byte ();
			std::vector <std::string> arguments;
			for (uint8_t n = 0; n != argc; ++n) {
				std::string argument = msg.read_string ();
				arguments.push_back (argument);
			}
			handle_battle_print (field_id, category, message_id, arguments);
			break;
		}
		case InMessage::BATTLE_VICTORY: {
			uint32_t field_id = msg.read_int ();
			uint16_t party_id = msg.read_short ();
			handle_battle_victory (field_id, party_id);
			break;
		}
		case InMessage::BATTLE_USE_MOVE: {
			uint32_t field_id = msg.read_int ();
			uint8_t party = msg.read_byte ();
			uint8_t slot = msg.read_byte ();
			std::string nickname = msg.read_string ();
			uint16_t move_id = msg.read_short ();
			handle_battle_use_move (field_id, party, slot, nickname, move_id);
			break;
		}
		case InMessage::BATTLE_WITHDRAW: {
			uint32_t field_id = msg.read_int ();
			uint8_t party = msg.read_byte ();
			uint8_t slot = msg.read_byte ();
			std::string nickname = msg.read_string ();
			handle_battle_withdraw (field_id, party, slot, nickname);
		void handle_battle_withdraw (uint32_t field_id, uint8_t party, uint8_t slot, std::string const & nickname);
			break;
		}
		case InMessage::BATTLE_SEND_OUT: {
			uint32_t field_id = msg.read_int ();
			uint8_t party = msg.read_byte ();
			uint8_t slot = msg.read_byte ();
			uint8_t index = msg.read_byte ();
			std::string nickname = msg.read_string ();
			uint16_t species_id = msg.read_short ();
			uint8_t gender = msg.read_byte ();
			uint8_t level = msg.read_byte();
			handle_battle_send_out (field_id, party, slot, index, nickname, species_id, gender, level);
			break;
		}
		case InMessage::BATTLE_HEALTH_CHANGE: {
			uint32_t field_id = msg.read_int ();
			uint8_t party = msg.read_byte ();
			uint8_t slot = msg.read_byte ();
			uint16_t change_in_health = msg.read_short ();	// 0 through 48
			uint16_t remaining_health = msg.read_short ();	// 0 through 48
			uint16_t denominator = msg.read_short ();
			handle_battle_health_change (field_id, party, slot, change_in_health, remaining_health, denominator);
			break;
		}
		case InMessage::BATTLE_SET_PP: {
			uint32_t field_id = msg.read_int ();
			uint8_t party = msg.read_byte ();
			uint8_t slot = msg.read_byte ();
			uint8_t pp = msg.read_byte ();
			handle_battle_set_pp (field_id, party, slot, pp);
			break;
		}
		case InMessage::BATTLE_FAINTED: {
			uint32_t field_id = msg.read_int ();
			uint8_t party = msg.read_byte ();
			uint8_t slot = msg.read_byte ();
			std::string nickname = msg.read_string ();
			handle_battle_fainted (field_id, party, slot, nickname);
			break;
		}
		case InMessage::BATTLE_BEGIN_TURN: {
			uint32_t field_id = msg.read_int ();
			uint16_t turn_count = msg.read_short ();
			handle_battle_begin_turn (field_id, turn_count);
			break;
		}
		case InMessage::SPECTATOR_BEGIN: {
			msg.skip();
			break;
		}
		case InMessage::BATTLE_SET_MOVE: {
			uint32_t field_id = msg.read_int ();
			uint8_t pokemon = msg.read_byte ();
			uint8_t move_slot = msg.read_byte ();
			uint16_t new_move = msg.read_short ();
			uint8_t pp = msg.read_byte ();
			uint8_t max_pp = msg.read_byte ();
			handle_battle_set_move (field_id, pokemon, move_slot, new_move, pp, max_pp);
			break;
		}
		case InMessage::METAGAME_LIST: {
			uint16_t metagame_count = msg.read_short ();
			std::vector <Metagame> metagames;
			for (uint16_t n = 0; n != metagame_count; ++n) {
				Metagame metagame (msg);
				metagames.push_back (metagame);
			}
			handle_metagame_list (metagames);
			break;
		}
		default:
			std::cerr << "Unknown code: " << code << '\n';
			break;
	}
}

void BotClient::handle_welcome_message (uint32_t version, std::string const & server, std::string const & message) {
	std::cout << server + '\n';
	std::cout << message + '\n';
}

void BotClient::handle_challenge (InMessage msg) {
	std::string challenge = "";
	for (unsigned n = 0; n != 16; ++n)
		challenge += msg.read_byte();
	int secret_style = msg.read_byte();
	std::string salt = msg.read_string();
	std::string response = get_challenge_response (challenge, secret_style, salt);
	OutMessage out (1);
	for (unsigned n = 0; n != 16; ++n)
		out.write_byte (response [n]);
	send (out);
}

void BotClient::handle_registry_response (uint8_t type, std::string const & details) {
	if (type == 7) {
		std::cout << "Successfully authenticated!\n";
		join_channel ("main");
	}
	else {
		std::cout << "Authentication failed with code: " << static_cast <int> (type) << ". =(\n";
		if (details.length() > 0)
			std::cout << details + "\n";
	}
}

void BotClient::handle_channel_info (uint32_t id, uint8_t info, std::string const & channel_name, std::string const & topic, uint32_t channel_flags, std::vector <std::pair <std::string, uint32_t> > const & users) {
}

void BotClient::handle_channel_join_part (uint32_t id, std::string const & user, bool joining) {
}

void BotClient::handle_channel_status (uint32_t channel_id, std::string const & invoker, std::string const & user, uint32_t flags) {
}

void BotClient::handle_channel_list (std::vector <Channel> const & channels) {
}

void BotClient::handle_channel_message (uint32_t channel_id, std::string const & user, std::string const & message) {
}

void BotClient::handle_incoming_challenge (std::string const & user, uint8_t generation, uint32_t n, uint32_t team_length) {
	if (true or (n > 1 or team_length > 6 or generation != 4))
		reject_challenge (user);
	else {
//		accept_challenge (user, team);
	}
}

void BotClient::handle_finalize_challenge (std::string const & user, bool accepted) {
}

void BotClient::handle_battle_begin (uint32_t field_id, std::string const & opponent, uint8_t party) {
}

void BotClient::handle_request_action (uint32_t field_id, uint8_t slot, uint8_t position, bool replace, std::vector <uint8_t> const & switches, bool can_switch, bool forced, std::vector <uint8_t> const & moves) {
}

void BotClient::handle_battle_print (uint32_t field_id, uint8_t category, uint16_t message_id, std::vector <std::string> const & arguments) {
}

void BotClient::handle_battle_victory (uint32_t field_id, uint16_t party_id) {
}

void BotClient::handle_battle_use_move (uint32_t field_id, uint8_t party, uint8_t slot, std::string const & nickname, uint16_t move_id) {
}

void BotClient::handle_battle_withdraw (uint32_t field_id, uint8_t party, uint8_t slot, std::string const & nickname) {
}

void BotClient::handle_battle_send_out (uint32_t field_id, uint8_t party, uint8_t slot, uint8_t index, std::string const & nickname, uint16_t species_id, uint8_t gender, uint8_t level) {
}

void BotClient::handle_battle_health_change (uint32_t field_id, uint8_t party, uint8_t slot, uint16_t change_in_health, uint16_t remaining_health, uint16_t denominator) {
}

void BotClient::handle_battle_set_pp (uint32_t field_id, uint8_t party, uint8_t slot, uint8_t pp) {
}

void BotClient::handle_battle_fainted (uint32_t field_id, uint8_t party, uint8_t slot, std::string const & nickname) {
}

void BotClient::handle_battle_begin_turn (uint32_t field_id, uint16_t turn_count) {
}

void BotClient::handle_battle_set_move (uint32_t field_id, uint8_t pokemon, uint8_t move_slot, uint16_t new_move, uint8_t pp, uint8_t max_pp) {
}

void BotClient::handle_metagame_list (std::vector <Metagame> const & metagames) {
}

void BotClient::join_channel (std::string const & channel) {
	OutMessage msg (OutMessage::JOIN_CHANNEL);
	msg.write_string (channel);
	send (msg);
}

/* void BotClient::accept_challenge (std::string const & user, ??? team) {
	OutMessage msg (7);
	msg.write_string (user);
	msg.write_byte (1);
	write_team (msg, team);
	send (msg);
}
*/

void BotClient::reject_challenge (std::string const & user) {
	OutMessage msg (OutMessage::RESOLVE_CHALLENGE);
	msg.write_string (user);
	msg.write_byte (0);
	send (msg);
}

}
}
using namespace technicalmachine;
using namespace pl;

int main () {
	std::string const host = "lab.pokemonexperte.de";
	std::string const port = "8446";
	std::string const username = "TM1.0";
	std::string const password = "Maximum Security";
	BotClient client (host, port, username, password);
	std::cout << "Authenticated.\n";
	client.run();
	return 0;
}
