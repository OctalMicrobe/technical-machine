// Connect to an arbitrary networked Pokemon sim
// Copyright (C) 2013 David Stone
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

#ifndef CLIENTS__NETWORK__CLIENT_HPP_
#define CLIENTS__NETWORK__CLIENT_HPP_

#include <cstdint>
#include <random>
#include <string>
#include <vector>

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "../battle.hpp"
#include "../client.hpp"

namespace technicalmachine {
class Party;
enum class Result;
namespace network {
class GenericBattleSettings;
class InMessage;
class OutMessage;

class Client : public ::technicalmachine::Client {
	public:
		void handle_channel_message (uint32_t channel_id, std::string const & user, std::string const & message) const;
		void send_message(OutMessage & msg);
	protected:
		explicit Client(unsigned set_depth);
		void reconnect ();
		virtual void send_channel_message(std::string const & channel, std::string const & message) = 0;
		virtual void send_channel_message(uint32_t channel_id, std::string const & message) = 0;
		virtual void send_private_message(std::string const & user, std::string const & message) = 0;
		void read_header(InMessage & msg);
		template<typename SimulatorInMessage>
		void run_main_service() {
			SimulatorInMessage msg;
			read_header(msg);
			io.run();
		}
		Team generate_team();
		virtual void send_keep_alive_message () = 0;
		std::string const & username() const;
		std::string const & password() const;
		void handle_server_message (std::string const & sender, std::string const & message) const;
		void handle_incoming_challenge (std::string const & opponent, GenericBattleSettings const & settings);
		template<typename Battle, typename ... Args>
		Battle const & add_pending_challenge (Team const & team, std::string const & opponent, Args && ... args) {
			return ::technicalmachine::Client::add_pending_challenge<Battle>(opponent, rd(), depth, std::forward<Args>(args)..., team);
		}
		template<typename Battle, typename ... Args>
		Battle const & add_pending_challenge (std::string const & opponent, Args && ... args) {
			return ::technicalmachine::Client::add_pending_challenge<Battle>(opponent, rd(), depth, std::forward<Args>(args)..., team_file_name);
		}
		template<typename Timer>
		std::unique_ptr<Timer> make_timer() {
			return std::unique_ptr<Timer>(new Timer(io));
		}
		virtual void handle_finalize_challenge (std::string const & opponent, bool accepted, bool challenger) = 0;
		void handle_private_message (std::string const & sender, std::string const & message);
	private:
		bool is_trusted (std::string const & user) const;
		void load_settings (bool reloading);
		void connect ();
		virtual void join_channel (std::string const & channel) = 0;
		virtual void part_channel (std::string const & channel) = 0;
		bool is_highlighted (std::string const & message) const;
		void do_request (std::string const & user, std::string const & request);
		void handle_challenge_command (std::string const & request, size_t start);
		void handle_depth_change_command (std::string const & user, std::string const & request, size_t start);
		void handle_join_channel_command (std::string const & request, size_t start);
		void handle_send_message_command (std::string const & request, size_t start);
		void handle_part_channel_command (std::string const & request, size_t start);
		void handle_send_pm_command (std::string const & request, size_t start);
		void handle_reload_settings_command ();
		virtual void send_battle_challenge (std::string const & opponent) = 0;

		boost::asio::io_service io;
		std::string host;
		std::string port;
		std::random_device rd;
		std::mt19937 random_engine;
		std::unique_ptr<boost::asio::ip::tcp::socket> socket;
		std::string current_username;
		std::string current_password;
		std::string team_file_name;
		std::vector <std::string> highlights;
		std::vector <std::string> trusted_users;
		unsigned chattiness;
		unsigned depth;
};

}	// namespace network
}	// namespace technicalmachine
#endif	// CLIENTS__NETWORK__CLIENT_HPP_
