// Copyright David Stone 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <tm/clients/pokemon_showdown/battle_logger.hpp>
#include <tm/clients/pokemon_showdown/inmessage.hpp>

#include <tm/clients/party.hpp>

#include <tm/evaluate/depth.hpp>
#include <tm/evaluate/evaluate.hpp>

#include <tm/visible_hp.hpp>

#include <bounded/integer.hpp>
#include <bounded/detail/variant/variant.hpp>

#include <containers/trivial_inplace_function.hpp>

#include <fstream>
#include <memory>
#include <random>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

namespace technicalmachine {

struct AllUsageStats;

namespace ps {

using SendMessageFunction = containers::trivial_inplace_function<void(std::string_view) const, sizeof(void *)>;

template<Generation generation>
struct Teams {
	Team<generation> ai;
	Team<generation> foe;
};
using GenericTeams = bounded::variant<
	Teams<Generation::one>,
	Teams<Generation::two>,
	Teams<Generation::three>,
	Teams<Generation::four>,
	Teams<Generation::five>,
	Teams<Generation::six>,
	Teams<Generation::seven>,
	Teams<Generation::eight>
>;

struct BattleParser {
	virtual auto handle_message(InMessage message) -> void = 0;
	virtual auto id() const -> std::string_view = 0;
	virtual auto completed() const -> bool = 0;
	virtual ~BattleParser();
};

auto make_battle_parser(
	SendMessageFunction send_message,
	BattleLogger battle_logger,
	std::ofstream analysis_logger,
	std::string id,
	std::string username,
	AllUsageStats const & usage_stats,
	AllEvaluate evaluate,
	Party party,
	DepthValues const depth,
	std::mt19937 random_engine,
	GenericTeams const & teams,
	bool log_foe_teams
) -> std::unique_ptr<BattleParser>;


constexpr auto make_party(std::string_view const player_id) {
	if (player_id == "p1") {
		return Party(0_bi);
	} else if (player_id == "p2") {
		return Party(1_bi);
	} else {
		throw std::runtime_error("Invalid player id: " + std::string(player_id));
	}
}

// This adds additional string scanning, but I don't think the performance
// matters that much here
struct ParsedDetails {
	Species species;
	Level level;
	Gender gender;
};
auto parse_details(std::string_view details) -> ParsedDetails;

struct ParsedSwitch {
	Party party;
	Species species;
	Level level;
	Gender gender;
	VisibleHP hp;
	Statuses status;
};
auto parse_switch(InMessage message) -> ParsedSwitch;

}	// namespace ps
}	// namespace technicalmachine
