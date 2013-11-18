// Load Pokemon Online teams
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

#include "read_team_file.hpp"

#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "conversion.hpp"
#include "stat_order.hpp"

#include "../../ability.hpp"
#include "../../item.hpp"
#include "../../team.hpp"

#include "../../move/move.hpp"
#include "../../move/moves.hpp"

#include "../../pokemon/pokemon.hpp"
#include "../../pokemon/species_forward.hpp"

#include "../../stat/invalid_stat.hpp"
#include "../../stat/stat.hpp"

namespace technicalmachine {
namespace po {
namespace {

Move load_move(boost::property_tree::ptree const & pt) {
	unsigned const id = pt.get_value<unsigned>();
	constexpr auto pp_ups = 3_ri;
	return Move(id_to_move(id), pp_ups);
}

Stat & lookup_stat(Pokemon & pokemon, unsigned n) {
	if (n >= stat_order.size()) {
		throw InvalidStat(std::to_string(n));
	}
	return get_stat(pokemon, stat_order[n]);
}

bool is_real_pokemon(boost::property_tree::ptree const & pt) {
	// Pokemon Online gives Missingno. the ID 0, and uses that to represent the
	// empty slots in teams smaller than 6 Pokemon.
	return pt.get<unsigned>("<xmlattr>.Num");
}

unsigned number_of_pokemon(boost::property_tree::ptree const & pt) {
	unsigned pokemon_count = 0;
	for (auto const & value : pt) {
		if (value.first == "Pokemon" and is_real_pokemon(value.second))
			++pokemon_count;
	}
	return pokemon_count;
}

void load_pokemon(boost::property_tree::ptree const & pt, Team & team) {
	unsigned const id = pt.get<unsigned>("<xmlattr>.Num");
	unsigned const forme = pt.get<unsigned>("<xmlattr>.Forme");
	Species const species = id_to_species(id, forme);
	std::string const nickname = pt.get<std::string>("<xmlattr>.Nickname");
	unsigned const gender = pt.get<unsigned>("<xmlattr>.Gender");
	Level const level(checked_integer<Level::min, Level::max>(pt.get<uint8_t>("<xmlattr>.Lvl")));
	uint8_t const happiness = pt.get<uint8_t>("<xmlattr>.Happiness");
	team.add_pokemon(species, level, Gender(id_to_gender(gender)), nickname, happiness);
	Pokemon & pokemon = team.replacement();

	unsigned const item = pt.get<unsigned>("<xmlattr>.Item");
	get_item(pokemon).name = id_to_item(item);
	unsigned const ability = pt.get<unsigned>("<xmlattr>.Ability");
	get_ability(pokemon) = id_to_ability(ability);
	unsigned const nature = pt.get<unsigned>("<xmlattr>.Nature");
	get_nature(pokemon).name = id_to_nature(nature);

	unsigned n = 0;
	for (auto const & value : pt.get_child("")) {
		if (value.first == "Move") {
			Move const move(load_move(value.second));
			if (move != Moves::END) {
				pokemon.move.add(move);
			}
		}
		else if (value.first == "DV") {
			Stat & stat = lookup_stat(pokemon, n);
			stat.iv = value.second.get_value<unsigned>();
			n < 5 ? ++n : n = 0;
		}
		else if (value.first == "EV") {
			Stat & stat = lookup_stat(pokemon, n);
			stat.ev.set_value(value.second.get_value<unsigned>());
			n < 5 ? ++n : n = 0;
		}
	}
}

}	// anonymous namespace

void load_team(Team & team, std::string const & file_name) {
	boost::property_tree::ptree pt;
	read_xml(file_name, pt);
	
	auto const all_pokemon = pt.get_child("Team");
	team.all_pokemon().initialize_size(number_of_pokemon(all_pokemon));
	for (auto const & value : all_pokemon) {
		if (value.first == "Pokemon" and is_real_pokemon(value.second))
			load_pokemon(value.second, team);
	}
	team.all_pokemon().reset_index();
}

}	// namespace po
}	// namespace technicalmachine
