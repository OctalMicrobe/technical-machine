// Connect to an arbitrary Pokemon sim
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

#ifndef CLIENTS__CLIENT_HPP_
#define CLIENTS__CLIENT_HPP_

#include <cstdint>
#include <random>
#include <string>

#include "battles.hpp"

#include "../evaluate/evaluate.hpp"

#include "../team_predictor/detailed_stats.hpp"

namespace technicalmachine {
class Settings;
class Party;
enum class Result;
class BattleSettings;

class Client {
public:
	void print_with_time_stamp(std::ostream & stream, std::string const & message) const;
	DetailedStats const & detailed() const;
	Evaluate const & evaluation_constants() const;
	virtual ~Client() { }
	void handle_incoming_challenge(std::string const & opponent, BattleSettings const & settings);
protected:
	explicit Client(unsigned depth);
	void set_depth(unsigned new_depth);
	Settings load_settings(bool reload);
	Team generate_team();
	template<typename ... Args>
	void handle_challenge_withdrawn(Args && ... args) {
		return battles.handle_challenge_withdrawn(std::forward<Args>(args)...);
	}
	virtual void handle_finalize_challenge(std::string const & opponent, bool accepted, bool challenger) = 0;
	void handle_battle_begin(uint32_t battle_id, std::string const & opponent, Party party = Party());
	void handle_battle_end(uint32_t battle_id, Result result);
	template<typename ... Args>
	Battle const & find_battle(Args && ... args) const {
		return battles.find(std::forward<Args>(args)...);
	}
	template<typename ... Args>
	Battle & find_battle(Args && ... args) {
		return battles.find(std::forward<Args>(args)...);
	}
	template<typename Battle, typename ... Args>
	Battle const & add_pending_challenge (Team const & team, std::string const & opponent, Args && ... args) {
		return battles.add_pending_challenge<Battle>(opponent, rd(), m_depth, std::forward<Args>(args)..., team);
	}
	template<typename Battle, typename ... Args>
	Battle const & add_pending_challenge (std::string const & opponent, Args && ... args) {
		return battles.add_pending_challenge<Battle>(opponent, rd(), m_depth, std::forward<Args>(args)..., team_file_name);
	}
	bool challenges_are_queued() const;
	std::string const & first_challenger() const;
	std::string random_string(size_t size);
	virtual void send_battle_challenge(std::string const & opponent) = 0;
private:
	typedef std::mt19937 RandomEngine;
	std::string time_stamp() const;
	std::random_device rd;
	RandomEngine random_engine;
	Battles battles;
	DetailedStats detailed_stats;
	Evaluate m_evaluation_constants;
	std::string team_file_name;
	std::string time_format;
	unsigned m_depth;
};

}	// namespace technicalmachine
#endif	// CLIENTS__CLIENT_HPP_