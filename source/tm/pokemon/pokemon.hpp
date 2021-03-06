// Copyright David Stone 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <tm/pokemon/happiness.hpp>
#include <tm/pokemon/hidden_power.hpp>
#include <tm/pokemon/level.hpp>
#include <tm/pokemon/species.hpp>

#include <tm/ability.hpp>
#include <tm/compress.hpp>
#include <tm/exists_if.hpp>
#include <tm/gender.hpp>
#include <tm/generation.hpp>
#include <tm/held_item.hpp>
#include <tm/operators.hpp>
#include <tm/status.hpp>
#include <tm/weather.hpp>

#include <tm/move/container.hpp>

#include <tm/stat/combined_stats.hpp>
#include <tm/stat/nature.hpp>
#include <tm/stat/initial_stat.hpp>
#include <tm/stat/stats.hpp>

#include <bounded/assert.hpp>

#include <cstdint>

namespace technicalmachine {

template<Generation generation>
struct Pokemon {
	Pokemon(Species const species, Level const level, Gender const gender, Item const item, Ability const ability, CombinedStats<IVAndEV> stats, RegularMoves regular_moves_, Happiness const happiness = Happiness()):
		m_regular_moves(regular_moves_),
		m_stats(BaseStats(generation, species), stats, level),

		m_species(species),
		m_item(item),
		m_ability(ability),
		m_gender(gender),
		m_nature(stats.nature),

		m_level(level),

		m_happiness(happiness),

		// TODO: Make this none if there is no way to call Hidden Power
		// TODO: Use the IVs provided
		m_hidden_power([=]{
			constexpr auto dv = DV(15_bi);
			constexpr auto iv = IV(31_bi);
			return generation <= Generation::two ?
				HiddenPower(generation, DVs{dv, dv, dv, dv}) :
				HiddenPower(generation, IVs{iv, iv, iv, iv, iv, iv});
		}()),
		
		m_has_been_seen(false),

		m_ability_is_known(true),
		m_item_is_known(true),
		m_nature_is_known(true)
	{
	}

	Pokemon(Species const species, Level const level, Gender const gender) : 
		Pokemon::Pokemon(
			species,
			level,
			gender,
			Item::None,
			Ability::Honey_Gather,
			CombinedStats<IVAndEV>{
				Nature::Hardy,
				{default_iv(generation), EV(0_bi)},
				{default_iv(generation), EV(0_bi)},
				{default_iv(generation), EV(0_bi)},
				{default_iv(generation), EV(0_bi)},
				{default_iv(generation), EV(0_bi)},
				{default_iv(generation), EV(0_bi)},
			},
			RegularMoves(),
			Happiness()
		)
	{
		m_ability_is_known = false;
		m_item_is_known = false;
		m_nature_is_known = false;
	}
	
	auto hp() const {
		return m_stats.hp();
	}
	auto stat(RegularStat const stat_name) const {
		return m_stats[stat_name];
	}

	auto advance_status_from_move(Ability const ability, bool const clear_status) & {
		m_status.advance_from_move(ability, clear_status);
	}

	auto has_been_seen() const -> bool {
		return m_has_been_seen;
	}
	void mark_as_seen() & {
		m_has_been_seen = true;
	}

	auto regular_moves() const -> RegularMoves const & {
		return m_regular_moves;
	}
	auto regular_moves() -> RegularMoves & {
		return m_regular_moves;
	}

	void set_hp(auto const hp) & {
		m_stats.hp() = hp;
	}

	auto initial_ability() const {
		if constexpr (exists<decltype(m_ability)>) {
			return m_ability;
		} else {
			return Ability::Honey_Gather;
		}
	}
	void set_initial_ability(Ability const ability) & {
		if constexpr (exists<decltype(m_ability)>) {
			m_ability = ability;
			m_ability_is_known = true;
		}
	}

	auto gender() const {
		if constexpr (exists<decltype(m_gender)>) {
			return m_gender;
		} else {
			return Gender::genderless;
		}
	}

	auto happiness() const -> Happiness {
		if constexpr (exists<decltype(m_happiness)>) {
			return m_happiness;
		} else {
			return Happiness();
		}
	}

	auto hidden_power() const -> bounded::optional<HiddenPower> {
		if constexpr (exists<decltype(m_hidden_power)>) {
			return m_hidden_power;
		} else {
			return bounded::none;
		}
	}

	auto item(bool const embargo, bool const magic_room) const -> Item {
		if constexpr (exists<decltype(m_item)>) {
			return m_item.get(generation, embargo, magic_room);
		} else {
			return Item::None;
		}
	}
	auto remove_item() & -> bounded::optional<Item> {
		if constexpr (exists<decltype(m_item)>) {
			return m_item.remove();
		} else {
			return bounded::none;
		}
	}
	auto destroy_item() & -> bool {
		if constexpr (exists<decltype(m_item)>) {
			return m_item.destroy();
		} else {
			return false;
		}
	}
	auto recycle_item() & -> void {
		if constexpr (exists<decltype(m_item)>) {
			m_item.recycle();
		}
	}
	auto set_item(Item const item) & -> void {
		if constexpr (exists<decltype(m_item)>) {
			m_item = HeldItem(item);
			m_item_is_known = true;
		}
	}

	auto level() const -> Level {
		return m_level;
	}

	auto nature() const -> Nature {
		if constexpr (exists<decltype(m_nature)>) {
			return m_nature;
		} else {
			return Nature::Hardy;
		}
	}
	auto species() const -> Species {
		return m_species;
	}

	auto status() const -> Status {
		return m_status;
	}
	void set_status(Statuses const status) & {
		m_status = status;
	}

	auto ability_is_known() const -> bool {
		return m_ability_is_known;
	}
	auto item_is_known() const -> bool {
		return m_item_is_known;
	}
	auto set_nature(Nature const nature) -> void {
		if constexpr (exists<decltype(m_nature)>) {
			m_nature = nature;
			m_nature_is_known = true;
		}
	}
	auto nature_is_known() const -> bool {
		return m_nature_is_known;
	}

	auto set_ev(PermanentStat const stat_name, IV const iv, EV const ev) -> void {
		auto const base_stats = BaseStats(generation, species());
		if (stat_name == PermanentStat::hp) {
			m_stats.hp() = HP(base_stats, level(), iv, ev);
		} else {
			auto const regular = RegularStat(stat_name);
			auto & stat = m_stats[regular];
			stat = initial_stat(regular, base_stats[regular], nature(), iv, ev, level());
		}
	}

	friend auto operator==(Pokemon, Pokemon) -> bool = default;
	friend auto compress(Pokemon const value) {
		return compress_combine(
			value.m_regular_moves,
			value.m_stats.hp().current(),
			value.m_item,
			value.m_status,
			value.m_has_been_seen
		);
	}
private:
	RegularMoves m_regular_moves;
	
	Stats m_stats;

	Species m_species;
	[[no_unique_address]] ExistsIf<HeldItem, generation >= Generation::two> m_item;
	[[no_unique_address]] ExistsIf<Ability, generation >= Generation::three> m_ability;
	[[no_unique_address]] ExistsIf<Gender, generation >= Generation::two> m_gender;
	Status m_status;
	[[no_unique_address]] ExistsIf<Nature, generation >= Generation::three> m_nature;

	Level m_level;
	[[no_unique_address]] ExistsIf<Happiness, generation >= Generation::two> m_happiness;
	[[no_unique_address]] ExistsIf<bounded::optional<HiddenPower>, generation >= Generation::two> m_hidden_power;

	bool m_has_been_seen : 1;
	
	bool m_ability_is_known : 1;
	bool m_item_is_known : 1;
	bool m_nature_is_known : 1;
};

extern template struct Pokemon<Generation::one>;
extern template struct Pokemon<Generation::two>;
extern template struct Pokemon<Generation::three>;
extern template struct Pokemon<Generation::four>;
extern template struct Pokemon<Generation::five>;
extern template struct Pokemon<Generation::six>;
extern template struct Pokemon<Generation::seven>;
extern template struct Pokemon<Generation::eight>;

auto get_hidden_power_type(auto const pokemon) {
	auto const hidden_power = pokemon.hidden_power();
	return BOUNDED_CONDITIONAL(hidden_power, hidden_power->type(), bounded::none);
}

auto hp_ratio(auto const pokemon) {
	auto const hp = pokemon.hp();
	return rational(hp.current(), hp.max());
}

}	// namespace technicalmachine
