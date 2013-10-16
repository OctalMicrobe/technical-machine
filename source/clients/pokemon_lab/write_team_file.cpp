// Write Pokemon Lab teams
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

#include "write_team_file.hpp"

#include <string>
#include <vector>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "conversion.hpp"

#include "../../team.hpp"

#include "../../move/move.hpp"

#include "../../pokemon/pokemon.hpp"

#include "../../stat/stat.hpp"

#include "../../string_conversions/ability.hpp"
#include "../../string_conversions/gender.hpp"
#include "../../string_conversions/item.hpp"
#include "../../string_conversions/move.hpp"
#include "../../string_conversions/nature.hpp"

namespace technicalmachine {
namespace pl {
namespace {

void write_move (Move const & move, boost::property_tree::ptree & pt) {
	boost::property_tree::ptree & m = pt.add("moveset.move", to_string(move));
	// TODO: replace with real PP ups logic
	m.put ("<xmlattr>.pp-up", 3);
}

void write_stat (Stat const & stat, std::string const & str, boost::property_tree::ptree & pt) {
	boost::property_tree::ptree & s = pt.add ("stats.stat", "");
	s.put ("<xmlattr>.name", str);
	s.put ("<xmlattr>.iv", stat.iv);
	s.put ("<xmlattr>.ev", stat.ev.value());
}

void write_stats (Pokemon const & pokemon, boost::property_tree::ptree & pt) {
	static std::pair<Stat::Stats, std::string> const stats [] = {
		{ Stat::HP, "HP" },
		{ Stat::ATK, "Atk" },
		{ Stat::DEF, "Def" },
		{ Stat::SPE, "Spd" },
		{ Stat::SPA, "SpAtk" },
		{ Stat::SPD, "SpDef" }
	};
	for (auto const & stat : stats) {
		write_stat(get_stat(pokemon, stat.first), stat.second, pt);
	}
}

void write_pokemon (Pokemon const & pokemon, boost::property_tree::ptree & pt) {
	boost::property_tree::ptree & member = pt.add ("pokemon", "");
	member.put("<xmlattr>.species", to_simulator_string(pokemon));
	member.put ("nickname", pokemon.get_nickname());
	member.put ("level", get_level(pokemon));
	member.put ("happiness", pokemon.happiness());
	member.put ("gender", to_string(get_gender(pokemon).gender));
	member.put ("nature", to_string(get_nature(pokemon).name));
	member.put ("item", to_string(get_item(pokemon).name));
	member.put ("ability", to_string(get_ability(pokemon).name()));
	pokemon.move.for_each_regular_move ([&](Move const & move) {
		write_move (move, member);
	});
	write_stats (pokemon, member);
}

}	// anonymous namespace

void write_team (Team const & team, std::string const & file_name) {
	boost::property_tree::ptree pt;
	boost::property_tree::xml_writer_settings<char> settings ('\t', 1);
	boost::property_tree::ptree & t = pt.add ("shoddybattle", "");
	for (auto const & pokemon : team.all_pokemon()) {
		write_pokemon (pokemon, t);
	}
	write_xml (file_name, pt, std::locale (), settings);
}

}	// namespace pl
}	// namespace technicalmachine
