// Handle Pokemon Showdown messages in a battle
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

#pragma once

#include "inmessage.hpp"
#include "slot_memory.hpp"

#include "../battle.hpp"

#include "../../evaluate/evaluate.hpp"

#include <boost/beast/websocket.hpp>

#include <random>
#include <string>
#include <string_view>
#include <utility>

namespace technicalmachine {
namespace ps {

struct BattleParser {
	BattleParser(
		boost::beast::websocket::stream<boost::asio::ip::tcp::socket &> & websocket,
		std::string id_,
		std::string username,
		UsageStats const & usage_stats,
		Evaluate evaluate,
		Party party,
		std::string opponent,
		unsigned const depth,
		std::mt19937 random_engine,
		Team team,
		TeamSize opponent_team_size
	):
		m_usage_stats(usage_stats),
		m_websocket(websocket),
		m_id(std::move(id_)),
		m_username(std::move(username)),
		m_random_engine(random_engine),
		m_slot_memory(team.size()),
		m_evaluate(evaluate),
		m_battle(
			party,
			std::move(opponent),
			std::move(team),
			opponent_team_size,
			100_bi
		),
		m_depth(depth)
	{
	}
	
	void handle_message(InMessage message);

	std::string_view id() const {
		return m_id;
	}	
	bool completed() const {
		return m_completed;
	}
private:
	Moves determine_action();
	void send_move(Moves const move);
	void send_random_move();
	void send_message(std::string_view message);

	UsageStats const & m_usage_stats;
		
	boost::beast::websocket::stream<boost::asio::ip::tcp::socket &> & m_websocket;
	std::string m_id;
	std::string m_username;
	std::mt19937 m_random_engine;

	SlotMemory m_slot_memory;

	Evaluate m_evaluate;
	Battle m_battle;
	unsigned m_depth;
	struct PhazeData {
		Party party;
		Moves move;
	};
	bounded::optional<PhazeData> m_phaze_move;
	bool m_completed = false;
	bool m_replacing_fainted = false;
};

constexpr auto make_party(std::string_view player_id) {
	return 	Party(BOUNDED_CONDITIONAL(player_id == "p1", 0_bi, 1_bi));
}

// This adds additional string scanning, but I don't think the performance
// matters that much here
inline auto parse_details(std::string_view details) {
	auto parser = BufferView(details, ", ");
	auto const species = from_string<Species>(parser.next());
	auto const level = Level(bounded::to_integer<Level::min, Level::max>(parser.next().substr(1)));
	auto const gender_str = parser.next();
	auto const gender =
		(gender_str == "F") ? Gender::female :
		(gender_str == "M") ? Gender::male :
		(gender_str == "") ? Gender::genderless :
		throw std::runtime_error("Invalid gender string " + std::string(gender_str));
	struct result {
		Species species;
		Level level;
		Gender gender;
	};
	return result{species, level, gender};
}

}	// namespace ps
}	// namespace technicalmachine