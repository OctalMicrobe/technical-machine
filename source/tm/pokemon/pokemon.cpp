// Copyright (C) 2016 David Stone
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

#include <tm/pokemon/pokemon.hpp>

#include <tm/ability.hpp>
#include <tm/gender.hpp>
#include <tm/operators.hpp>
#include <tm/rational.hpp>
#include <tm/weather.hpp>

#include <tm/move/is_switch.hpp>
#include <tm/move/move.hpp>

#include <tm/stat/stat.hpp>

#include <tm/string_conversions/ability.hpp>
#include <tm/string_conversions/item.hpp>
#include <tm/string_conversions/move.hpp>
#include <tm/string_conversions/nature.hpp>
#include <tm/string_conversions/pokemon.hpp>
#include <tm/string_conversions/status.hpp>

#include <containers/algorithms/all_any_none.hpp>
#include <containers/algorithms/concatenate.hpp>

#include <boost/format.hpp>

#include <cassert>
#include <cstdint>
#include <string>
#include <string_view>

namespace technicalmachine {

// TODO: Setting IVs requires modifying the Pokemon after construction, which
// will not update Hidden Power
Pokemon::Pokemon(Generation const generation, TeamSize const my_team_size, Species const species, Level const level, Gender const gender, Item const item, Ability const ability, Nature const nature, Happiness const happiness):
	m_moves(generation, my_team_size),
	current_type(generation, species),
	stats(generation, species, level),

	m_species(species),
	m_item(item),
	m_ability(ability),
	m_gender(gender),
	m_nature(nature),

	m_level(level),

	m_happiness(happiness),
	
	m_hidden_power(generation, GenericStats<IV>{IV(31_bi), IV(31_bi), IV(31_bi), IV(31_bi), IV(31_bi), IV(31_bi)}),
	
	m_has_been_seen(false),

	m_ability_is_known(true),
	m_item_is_known(true),
	m_nature_is_known(true)
{
}

Pokemon::Pokemon(Generation const generation, TeamSize const my_team_size, Species const species, Level const level, Gender const gender, Happiness const happiness) : 
	Pokemon::Pokemon(generation, my_team_size, species, level, gender, Item::None, Ability::Honey_Gather, Nature::Hardy, happiness)
	{
	m_ability_is_known = false;
	m_item_is_known = false;
	m_nature_is_known = false;
}


void Pokemon::change_type(Type const new_type) {
	current_type = PokemonTypes(new_type);
}

auto Pokemon::has_been_seen() const -> bool {
	return m_has_been_seen;
}

namespace {

auto status_can_apply(Statuses const status, Pokemon const user, Pokemon const target, Weather const weather, bool const uproar) {
	return
		is_clear(get_status(target)) and
		(ignores_blockers(get_ability(user)) or !blocks_status(get_ability(target), status, weather)) and
		!containers::any(get_type(target), [=](Type const type) { return blocks_status(type, status); }) and
		!weather.blocks_status(status) and
		(!uproar or (status != Statuses::sleep and status != Statuses::rest));
}

constexpr auto reflected_status(Statuses const status) -> bounded::optional<Statuses> {
	switch (status) {
	case Statuses::burn:
	case Statuses::paralysis:
	case Statuses::poison:
		return status;
	case Statuses::toxic:
		return Statuses::poison;
	case Statuses::clear:
	case Statuses::freeze:
	case Statuses::sleep:
	case Statuses::rest:
		return bounded::none;
	}
}

}	// namespace

void activate_pinch_item(Pokemon & pokemon) {
	// TODO: Confusion damage does not activate healing berries in Generation 5+
	auto consume = [&] { set_item(pokemon, Item::None); };
	auto const current_hp = hp_ratio(pokemon);
	auto healing_berry = [&](auto const amount) {
		if (current_hp <= rational(1_bi, 2_bi)) {
			change_hp(pokemon, amount);
			consume();
		}
	};
	switch (get_item(pokemon)) {
		case Item::Berry:
			healing_berry(10_bi);
			break;
		case Item::Berry_Juice:
			healing_berry(20_bi);
			break;
		case Item::Gold_Berry:
			healing_berry(30_bi);
			break;
		default:
			break;
	}
}

auto apply_status(Statuses const status, Pokemon & user, Pokemon & target, Weather const weather, bool const uproar) -> void {
	BOUNDED_ASSERT_OR_ASSUME(status != Statuses::clear);
	BOUNDED_ASSERT_OR_ASSUME(status != Statuses::rest);
	if (!status_can_apply(status, user, target, weather, uproar)) {
		return;
	}
	target.set_status(status);
	auto const reflected = reflected_status(status);
	if (reflected and reflects_status(get_ability(target))) {
		apply_status(*reflected, user, weather, uproar);
	}
}

containers::string to_string(Pokemon const pokemon) {
	double const per_cent_hp = 100.0 * static_cast<double>(hp_ratio(pokemon));

	auto const output_status = !is_clear(get_status(pokemon));
	
	#define TECHNICALMACHINE_STAT(stat, str) \
		std::string_view(" / "), std::string_view(bounded::to_string(get_stat(pokemon, stat).ev().value())), std::string_view(" " str)
	
	auto moves_to_string = [&]{
		containers::string output;
		for (auto const & move : regular_moves(pokemon)) {
			output = containers::concatenate<containers::string>(std::move(output), std::string_view("\n\t- "), to_string(move.name()));
		}
		return output;
	};

	return containers::concatenate<containers::string>(
		to_string(get_species(pokemon)),
		std::string_view(" ("), std::string_view((boost::format("%.1f") % per_cent_hp).str()), std::string_view("% HP) @ "),
		to_string(get_item(pokemon)),
		std::string_view("\n\tAbility: "), to_string(get_ability(pokemon)), std::string_view("\n"),
		(output_status ? containers::concatenate<containers::string>(std::string_view("\tStatus: "), to_string(get_status(pokemon).name()), std::string_view("\n")) : containers::string("")),
		std::string_view("\tNature: "), to_string(get_nature(pokemon)),
		std::string_view("\n\t"),
		std::string_view(bounded::to_string(get_hp(pokemon).ev().value())), std::string_view(" HP"),
		TECHNICALMACHINE_STAT(StatNames::ATK, "Atk"),
		TECHNICALMACHINE_STAT(StatNames::DEF, "Def"),
		TECHNICALMACHINE_STAT(StatNames::SPA, "SpA"),
		TECHNICALMACHINE_STAT(StatNames::SPD, "SpD"),
		TECHNICALMACHINE_STAT(StatNames::SPE, "Spe"),
		moves_to_string()
	);
	#undef TECHNICALMACHINE_STAT
}

}	// namespace technicalmachine
