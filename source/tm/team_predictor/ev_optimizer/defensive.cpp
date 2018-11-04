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

#include <tm/team_predictor/ev_optimizer/defensive.hpp>

#include <tm/pokemon/pokemon.hpp>

#include <tm/stat/calculate.hpp>
#include <tm/stat/nature.hpp>
#include <tm/stat/stat_names.hpp>

#include <containers/algorithms/transform.hpp>
#include <containers/integer_range.hpp>

#include <cassert>
#include <iostream>

namespace technicalmachine {
namespace {

using namespace bounded::literal;

constexpr auto ev_sum(DataPoint const data) {
	return data.hp.value() + data.defense.value() + data.special_defense.value();
}

template<typename LHS, typename RHS>
constexpr auto round_up_divide(LHS const lhs, RHS const rhs) {
	return lhs / rhs + BOUNDED_CONDITIONAL(lhs % rhs == 0_bi, 0_bi, 1_bi);
}

template<typename T>
auto reverse_initial_stat(T const target, Nature const nature, StatNames const stat_name, Stat::base_type const base, IV const iv, Level const level) {
	return bounded::max(0_bi, (round_up_divide((round_up_divide(target, boost(nature, stat_name)) - 5_bi) * 100_bi, level()) - 2_bi * base - iv.value()) * 4_bi);
}

}	// namespace

DefensiveEVs::DefensiveEVs(Species const species, Level const level, Nature const original_nature, HP const original_hp, Stat const defense, Stat const special_defense) {
	auto product = [=](Nature const nature, HP const hp, StatNames const name, Stat const stat) {
		return hp.max() * initial_stat(name, stat, level, nature);
	};
	auto initial_product = [=](StatNames const name, Stat const stat) {
		return product(original_nature, original_hp, name, stat);
	};
	auto const defense_product = initial_product(StatNames::DEF, defense);
	auto const special_defense_product = initial_product(StatNames::SPD, special_defense);

	auto defensive_product = [=](DataPoint const value) {
		auto const hp = HP(species, level, value.hp);
		auto single_product = [=](StatNames const stat, EV const ev) {
			return product(value.nature, hp, stat, Stat(species, stat, ev));
		};

		return single_product(StatNames::DEF, value.defense) * single_product(StatNames::SPD, value.special_defense);
	};

	for (auto const nature : containers::enum_range<Nature>()) {
		constexpr auto ev_range = containers::transform(
			containers::integer_range(0_bi, EV::max + 4_bi, 4_bi),
			[](auto const ev) { return EV(ev); }
		);
		auto best_per_nature = bounded::optional<DataPoint>{};
		for (auto const hp_ev : ev_range) {
			auto const hp = HP(species, level, hp_ev, original_hp.iv());
			auto find_minimum_matching = [=](StatNames const stat_name, Stat const stat, auto const original_product) {
				auto const target_stat = round_up_divide(original_product, hp.max());
				auto const expected = reverse_initial_stat(target_stat, nature, stat_name, stat.base(), stat.iv(), level);
				return BOUNDED_CONDITIONAL(expected <= EV::max, EV(EV::value_type(expected)), bounded::none);
			};

			auto const defense_ev = find_minimum_matching(StatNames::DEF, defense, defense_product);
			if (!defense_ev) {
				continue;
			}
			auto const special_defense_ev = find_minimum_matching(StatNames::SPD, special_defense, special_defense_product);
			if (!special_defense_ev) {
				continue;
			}
			auto is_better = [=](DataPoint const candidate, DataPoint const current) {
				auto const cmp = compare(ev_sum(candidate), ev_sum(current));
				if (cmp < 0) {
					return true;
				} else if (cmp > 0) {
					return false;
				}
				auto const candidate_product = defensive_product(candidate);
				auto const current_product = defensive_product(current);
				return candidate_product > current_product;
			};
			auto const candidate = DataPoint{nature, hp_ev, *defense_ev, *special_defense_ev};
			if (!best_per_nature or is_better(candidate, *best_per_nature)) {
				best_per_nature.emplace(candidate);
			}
		}
		if (best_per_nature) {
			push_back(m_container, *best_per_nature);
		}
	}
	assert(!empty(m_container));
}

}	// namespace technicalmachine