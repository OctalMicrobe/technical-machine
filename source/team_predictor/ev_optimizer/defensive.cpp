// Optimize defensive EVs and nature to remove waste
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

#include "defensive.hpp"

#include "offensive.hpp"
#include "single_classification_evs.hpp"

#include "../../pokemon/pokemon.hpp"

#include "../../stat/nature.hpp"
#include "../../stat/stat_names.hpp"

#include <containers/algorithms/all_any_none.hpp>
#include <containers/algorithms/filter_iterator.hpp>
#include <containers/algorithms/minmax_element.hpp>
#include <containers/array/array.hpp>
#include <containers/vector.hpp>

#include <cassert>

namespace technicalmachine {
namespace {

using namespace bounded::literal;

using Estimates = containers::static_vector<DataPoint, detail::possible_defensive_ev_combinations()>;
using AllPossible = containers::array<Estimates, DefensiveEVs::number_of_natures.value()>;

auto combine_results(EqualDefensiveness const & physical, EqualDefensiveness const & special) {
	AllPossible all;
	auto it = containers::begin(all);
	auto nature = containers::front(containers::enum_range<Nature>());
	for (auto const & p : physical) {
		if (nature != p.nature) {
			++it;
			nature = p.nature;
		}
		for (auto const & s : special) {
			if (are_compatible(p, s)) {
				it->emplace_back(p, s);
			}
		}
	}
	return all;
}

auto filter_to_minimum_evs(Estimates const & per_nature) {
	assert(!empty(per_nature));
	auto const it = containers::min_element(containers::transform(per_nature, ev_sum));
	auto const minimum = [it](DataPoint const & value) { return ev_sum(value) == *it; };
	return containers::filter(per_nature, minimum);
}

template<typename Container>
DataPoint most_effective_equal_evs(Container const & original, Pokemon const & pokemon) {
	assert(!empty(original));
	auto const level = get_level(pokemon);
	auto const species = static_cast<Species>(pokemon);
	auto transformation = [=](auto const value) { return defensive_product(value, level, species); };
	auto const transformed = containers::transform(original, transformation);
	auto const it = containers::max_element(transformed).base();
	assert(it != end(original));
	return *it;
}

auto best_possible_per_nature(AllPossible const all, Pokemon const & pokemon) {
	DefensiveEVs::BestPerNature result;
	for (auto const & per_nature : all) {
		if (containers::empty(per_nature)) {
			continue;
		}
		push_back(result, most_effective_equal_evs(filter_to_minimum_evs(per_nature), pokemon));
	}
	return result;
}

auto divide_natures(DefensiveEVs::BestPerNature const & container) {
	constexpr auto boost = 0_bi;
	constexpr auto penalty = 1_bi;
	constexpr auto both = 2_bi;
	constexpr auto neutral = 3_bi;
	auto divided = containers::array<DefensiveEVs::Natures, 4>{};
	for (auto const & value : container) {
		auto const nature = value.nature;
		auto & stat =
			(boosts_defending_stat(nature) and !lowers_defending_stat(nature)) ? divided[boost] :
			(lowers_defending_stat(nature) and !boosts_defending_stat(nature)) ? divided[penalty] :
			(lowers_defending_stat(nature) and boosts_defending_stat(nature)) ? divided[both] :
			divided[neutral];
		stat.emplace_back(nature);
	}
	return divided;
}

bool boosts_same(Nature const nature, Nature const reference_nature) {
	return (boosts_stat(nature, StatNames::DEF) and boosts_stat(reference_nature, StatNames::DEF))
			or (boosts_stat(nature, StatNames::SPD) and boosts_stat(reference_nature, StatNames::SPD))
			or (!boosts_defending_stat(nature) and !boosts_defending_stat(reference_nature));
}

bool penalizes_same(Nature const nature, Nature const reference_nature) {
	return (lowers_stat(nature, StatNames::DEF) and lowers_stat(reference_nature, StatNames::DEF))
			or (lowers_stat(nature, StatNames::SPD) and lowers_stat(reference_nature, StatNames::SPD))
			or (!lowers_defending_stat(nature) and !lowers_defending_stat(reference_nature));
}

bool has_same_effect_on_defenses(Nature const nature, Nature const reference_nature) {
	return boosts_same(nature, reference_nature) and penalizes_same(nature, reference_nature);
}

constexpr auto matches_nature(Nature const nature) {
	return [=](auto const value) { return value.nature == nature; };
}

auto used_natures(DefensiveEVs::BestPerNature const & container) {
	auto used = DefensiveEVs::Natures();
	for (auto const & value : container) {
		assert(!containers::any_equal(used, value.nature));
		used.emplace_back(value.nature);
	}
	return used;
}

}	// namespace

DefensiveEVs::DefensiveEVs(Pokemon const & pokemon) {
	auto const physical = equal_defensiveness(pokemon, true);
	auto const special = equal_defensiveness(pokemon, false);
	m_container = best_possible_per_nature(combine_results(physical, special), pokemon);
	for (auto const & value : divide_natures(m_container)) {
		remove_inefficient_natures(value);
	}
	add_other_potential_natures();
	assert(!empty(m_container));
}

void DefensiveEVs::remove_inefficient_natures(DefensiveEVs::Natures const & divided_natures) {
	auto const capacity = static_cast<std::intmax_t>(DefensiveEVs::Natures::capacity());
	auto filter = [&](DataPoint const value) { return containers::any_equal(divided_natures, value.nature); };
	containers::static_vector<DataPoint, capacity> boosters;
	for (auto const & value : containers::filter(m_container, filter)) {
		boosters.emplace_back(value);
	}
	auto const best = containers::min_element(containers::transform(boosters, ev_sum)).base();
	for (auto const & nature : divided_natures) {
		if (nature != best->nature) {
			containers::erase(m_container, containers::find_if(m_container, matches_nature(nature)));
		}
	}
}

void DefensiveEVs::add_other_potential_natures() {
	for (auto const reference_nature : used_natures(m_container)) {
		for (auto const boosted : containers::enum_range(StatNames::NORMAL_END)) {
			for (auto const penalized : containers::enum_range(StatNames::NORMAL_END)) {
				auto const nature = make_nature(boosted, penalized);
				if (!has_same_effect_on_defenses(nature, reference_nature)) {
					continue;
				}
				if (nature == reference_nature) {
					continue;
				}
				auto const old_data_point = containers::find_if(m_container, matches_nature(reference_nature));
				assert(old_data_point != end(m_container));
				m_container.emplace_back(*old_data_point, nature);
			}
		}
	}
}

}	// namespace technicalmachine
