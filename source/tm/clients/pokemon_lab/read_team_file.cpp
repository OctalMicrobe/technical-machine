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

#include <tm/clients/pokemon_lab/read_team_file.hpp>

#include <tm/move/move.hpp>

#include <tm/pokemon/pokemon.hpp>
#include <tm/pokemon/species.hpp>

#include <tm/string_conversions/move.hpp>
#include <tm/string_conversions/nature.hpp>
#include <tm/string_conversions/species.hpp>

#include <containers/array/array.hpp>
#include <containers/begin_end.hpp>
#include <containers/flat_map.hpp>

namespace technicalmachine {
namespace pl {

auto stat_from_simulator_string(std::string_view const str) -> PermanentStat {
	using Storage = containers::array<containers::map_value_type<std::string_view, PermanentStat>, 6>;
	constexpr auto converter = containers::basic_flat_map<Storage>(
		containers::assume_sorted_unique,
		Storage{{
			{ "Atk", PermanentStat::atk },
			{ "Def", PermanentStat::def },
			{ "HP", PermanentStat::hp },
			{ "SpAtk", PermanentStat::spa },
			{ "SpDef", PermanentStat::spd },
			{ "Spd", PermanentStat::spe },
		}}
	);
	return converter.at(str);
}

auto load_stats(boost::property_tree::ptree const & pt) -> CombinedStats<IVAndEV> {
	auto result = CombinedStats<IVAndEV>{
		from_string<Nature>(pt.get<std::string>("nature")),
		{IV(0_bi), EV(0_bi)},
		{IV(0_bi), EV(0_bi)},
		{IV(0_bi), EV(0_bi)},
		{IV(0_bi), EV(0_bi)},
		{IV(0_bi), EV(0_bi)},
		{IV(0_bi), EV(0_bi)},
	};
	for (auto const & value : pt.get_child("stats")) {
		auto const & stats = value.second;
		auto const stat_name = stat_from_simulator_string(stats.get<std::string>("<xmlattr>.name"));
		auto const iv = IV(stats.get<IV::value_type>("<xmlattr>.iv"));
		auto const ev = EV(stats.get<EV::value_type>("<xmlattr>.ev"));
		result[stat_name] = {iv, ev};
	}
	return result;
}

auto species_from_simulator_string(std::string_view const str) -> Species {
	using Storage = containers::array<containers::map_value_type<std::string_view, Species>, 16>;
	constexpr auto converter = containers::basic_flat_map<Storage>(
		containers::assume_sorted_unique,
		Storage{{
			{ "Deoxys", Species::Deoxys_Normal },
			{ "Deoxys-e", Species::Deoxys_Speed },
			{ "Deoxys-f", Species::Deoxys_Attack },
			{ "Deoxys-l", Species::Deoxys_Defense },
			{ "Giratina", Species::Giratina_Altered },
			{ "Giratina-o", Species::Giratina_Origin },
			{ "Rotom-c", Species::Rotom_Mow },
			{ "Rotom-f", Species::Rotom_Frost },
			{ "Rotom-h", Species::Rotom_Heat },
			{ "Rotom-s", Species::Rotom_Fan },
			{ "Rotom-w", Species::Rotom_Wash },
			{ "Shaymin", Species::Shaymin_Land },
			{ "Shaymin-s", Species::Shaymin_Sky },
			{ "Wormadam", Species::Wormadam_Plant },
			{ "Wormadam-g", Species::Wormadam_Sandy },
			{ "Wormadam-s", Species::Wormadam_Trash }
		}}
	);
	auto const it = converter.find(str);
	return (it != containers::end(converter)) ? it->mapped() : from_string<Species>(str);
}

auto load_moves(Generation const generation, boost::property_tree::ptree const & pt) -> RegularMoves {
	auto moves = RegularMoves();
	for (boost::property_tree::ptree::value_type const & value : pt) {
		auto const name = from_string<Moves>(value.second.get_value<std::string>());
		auto const pp_ups = value.second.get<PP::pp_ups_type>("<xmlattr>.pp-up");
		moves.push_back(Move(generation, name, pp_ups));
	}
	return moves;
}

} // namespace pl
} // namespace technicalmachine
