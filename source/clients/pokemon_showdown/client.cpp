// Connect to Pokemon Showdown
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

// See https://github.com/Zarel/Pokemon-Showdown/blob/master/protocol-doc.md
// for the full protocol.

#include "client.hpp"

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <string>
#include <vector>

#include "battle.hpp"
#include "inmessage.hpp"
#include "outmessage.hpp"

#include "../../settings_file.hpp"
#include "../../team.hpp"

namespace technicalmachine {
namespace ps {

namespace {
template<typename Container>
Container split(std::string const & str, char delimiter) {
	Container container;
	auto previous = str.begin();
	while (true) {
		auto const found = std::find(previous, str.end(), delimiter);
		container.emplace_back(previous, found);
		if (found == str.end()) {
			break;
		}
		previous = std::next(found);
	}
	return container;
}

using message_ptr = websocketpp::config::asio_client::message_type::ptr;

InMessage parse_message(message_ptr const & ptr) {
	static constexpr char delimiter = '|';
	auto tokens = split<std::vector<std::string> >(ptr->get_payload(), delimiter);
	assert(tokens.size() >= 2);
	std::string & room = *tokens.begin();
	std::string & type = *(tokens.begin() + 1);
	InMessage::Data data(std::make_move_iterator(tokens.begin() + 2), std::make_move_iterator(tokens.end()));
	return InMessage(std::move(room), std::move(type), std::move(data));
}
}	// namespace

Client::Client(unsigned depth):
	::technicalmachine::Client(depth) {
	load_settings (false);
	while (m_username.empty()) {
		std::cerr << "Add a username and password entry to " + Settings::file_name() + " and hit enter.";
		std::cin.get();
		load_settings(false);
	}
	socket.init_asio();
	socket.set_message_handler([&](websocketpp::connection_hdl handle, message_ptr message) {
		handle_message(parse_message(message));
		std::cout << "Waiting for next message.\n";
	});
	log_in();
}

void Client::log_in() {
	websocketpp::lib::error_code ec;
	auto connection_pointer = socket.get_connection(m_host, ec);
	m_handle = connection_pointer->get_handle();
	socket.connect(std::move(connection_pointer));
}

// Temporary copy and paste here until I implement my better structure for
// managing clients.
void Client::load_settings(bool const reloading) {
	auto settings = reloading ? Base::load_settings(true) : Settings();
	m_chattiness = settings.chattiness;
	
	if (!reloading) {
		Server & server = settings.servers.front();
		m_host = server.host;
		m_username = server.username;
		if (server.password.empty()) {
			server.password = random_string(31);
			settings.write();
		}
		m_password = server.password;
	}
}

void Client::run() {
	socket.run();
}

void Client::handle_message(InMessage const & message) {
	if (message.type() == "challstr") {
		auto const & key_id = message.at(0);
		auto const & challenge = message.at(1);
		websocketpp::lib::error_code ec;
		std::string const request = "|/join lobby";
		socket.send(m_handle, request, websocketpp::frame::opcode::text, ec);
		if (ec) {
			std::cerr << ec.message() << '\n';
		}
	}
	else if (message.type() == "popup") {
		for (auto const & text : message) {
			std::cout << text << '\n';
		}
	}
	else {
		for (auto const & text : message) {
			std::cout << text << '|';
		}
		std::cout << "\nPlease type in a command.\n";
		std::string request;
		std::getline(std::cin, request);
		if (request.empty()) {
			return;
		}
		websocketpp::lib::error_code ec;
		socket.send(m_handle, request, websocketpp::frame::opcode::text, ec);
		if (ec) {
			std::cerr << ec.message() << '\n';
		}
	}
}

void Client::send_battle_challenge(std::string const & opponent) {
}

void Client::handle_finalize_challenge(std::string const & opponent, bool accepted, bool unused) {
}

void Client::join_channel(std::string const & channel) {
}

void Client::part_channel(std::string const & channel) {
}

void Client::send_channel_message(std::string const & channel, std::string const & message) {
}

void Client::send_channel_message(uint32_t channel_id, std::string const & message) {
}

void Client::send_private_message(std::string const & user, std::string const & message) {
}

}	// namespace ps
}	// namespace technicalmachine