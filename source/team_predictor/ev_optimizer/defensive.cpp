// Optimize defensive EVs and nature to remove waste
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

#include "defensive.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <stdexcept>
#include <string>

#include "offensive.hpp"

#include "../../pokemon/pokemon.hpp"

#include "../../stat/nature.hpp"
#include "../../stat/stat.hpp"

#include <iostream>

namespace technicalmachine {
namespace {
enum NatureBoost { Penalty, Neutral, Boost };

template<Stat::Stats stat>
Nature::Natures nature_effect(NatureBoost nature);
Nature::Natures combine(NatureBoost physical, NatureBoost special);

template<Stat::Stats stat>
void set_ev(Pokemon & pokemon, unsigned const defensive_ev);
unsigned defensive_evs_available(Pokemon const & pokemon);

}	// unnamed namespace

class DefensiveEVs::SingleClassificationEVs {
	public:
		SingleClassificationEVs(unsigned hp_ev, unsigned defensive_ev, NatureBoost nature);
		template<Stat::Stats stat>
		std::string to_string(std::string const & stat_name) const {
			Nature const nature = nature_effect<stat>(nature_boost);
			return nature.to_string() + " " + std::to_string(hp) + " HP / " + std::to_string(defensive) + " " + stat_name;
		}
		static NatureBoost convert(Nature nature);
		unsigned hp;
		unsigned defensive;
		NatureBoost nature_boost;
};

DefensiveEVs::DataPoint::DataPoint(unsigned hp_ev, unsigned defense_ev, unsigned special_defense_ev, Nature const a_nature):
	hp(hp_ev),
	defense(defense_ev),
	special_defense(special_defense_ev),
	nature(a_nature) {
}

std::string DefensiveEVs::DataPoint::to_string() const {
	return nature.to_string() + " " + std::to_string(hp) + " HP / " + std::to_string(defense) + " Def / " + std::to_string(special_defense) + " SpD";
}

unsigned DefensiveEVs::DataPoint::sum() const {
	return hp + defense + special_defense;
}

namespace {
template<Stat::Stats stat>
std::vector<DefensiveEVs::SingleClassificationEVs> defensiveness(Pokemon pokemon) {
	unsigned const initial_product = pokemon.hp.max * initial_stat<stat>(pokemon);
	std::vector<DefensiveEVs::SingleClassificationEVs> result;
	static std::array<Nature, 3> const natures = {{
		nature_effect<stat>(Boost),
		nature_effect<stat>(Neutral),
		nature_effect<stat>(Penalty)
	}};
	for (Nature const nature : natures) {
		pokemon.nature() = nature;
		for (unsigned hp_ev = 0; hp_ev <= 252; hp_ev += 4) {
			pokemon.hp.ev.set_value(hp_ev);
			unsigned const hp = initial_stat<Stat::HP>(pokemon);
			unsigned defensive_ev = 0;
			set_ev<stat>(pokemon, defensive_ev);
			while (initial_stat<stat>(pokemon) * hp < initial_product and defensive_ev <= 252 - 4) {
				defensive_ev += 4;
				set_ev<stat>(pokemon, defensive_ev);
			}
			if (initial_stat<stat>(pokemon) * hp >= initial_product) {
				result.emplace_back(hp_ev, defensive_ev, DefensiveEVs::SingleClassificationEVs::convert(nature));
			}
		}
	}
	return result;
}

}	// unnamed namespace

DefensiveEVs::DefensiveEVs(Pokemon pokemon) {
	Single const physical = defensiveness<Stat::DEF>(pokemon);
	Single const special = defensiveness<Stat::SPD>(pokemon);
	unsigned const max_evs = defensive_evs_available(pokemon);
	combine_results(physical, special, max_evs);
	for (auto const & per_nature : container) {
		for (auto const & stat : per_nature.second)
			std::cerr << stat.to_string() + '\n';
	}
}

void DefensiveEVs::combine_results(Single const & physical, Single const & special, unsigned max_evs) {
	for (auto const & p : physical) {
		for (auto const & s : special) {
			if (p.hp != s.hp)
				continue;
			bool const evs_over_cap = (p.hp + p.defensive + s.defensive > max_evs);
			if (evs_over_cap)
				continue;
			bool const legal_nature_combination = (p.nature_boost != s.nature_boost or p.nature_boost == Neutral);
			if (legal_nature_combination) {
				Nature const nature = combine(p.nature_boost, s.nature_boost);
				container[nature.name].emplace_back(p.hp, p.defensive, s.defensive, nature);
			}
		}
	}
	filter_to_minimum_evs();
}

void DefensiveEVs::filter_to_minimum_evs() {
	for (auto & per_nature : container) {
		minimum_evs_per_nature(per_nature.second);
	}
}

void DefensiveEVs::minimum_evs_per_nature(Estimates & original) {
	static auto const least_sum = [](DataPoint const & value, DataPoint const & least) {
		return value.sum() < least.sum();
	};
	auto const it = std::min_element(std::begin(original), std::end(original), least_sum);
	std::cerr << "Sum: " << it->sum() << '\n';
	auto const invalid = [it](DataPoint const & value) {
		return value.sum() != it->sum();
	};
	original.erase(std::remove_if(std::begin(original), std::end(original), invalid), std::end(original));
}

DefensiveEVs::SingleClassificationEVs::SingleClassificationEVs(unsigned hp_ev, unsigned defensive_ev, NatureBoost nature):
	hp(hp_ev),
	defensive(defensive_ev),
	nature_boost(nature) {
}

NatureBoost DefensiveEVs::SingleClassificationEVs::convert(Nature nature) {
	switch (nature.name) {
	case Nature::IMPISH:
	case Nature::CALM:
		return Boost;
	case Nature::HASTY:
	case Nature::NAIVE:
		return Penalty;
	default:
		assert(nature.name == Nature::HARDY);
		return Neutral;
	}
}


namespace {

unsigned defensive_evs_available(Pokemon const & pokemon) {
	constexpr unsigned max_total_evs = 510;
	return max_total_evs - pokemon.atk.ev.value() + pokemon.spa.ev.value() + pokemon.spe.ev.value();
}

template<>
void set_ev<Stat::DEF>(Pokemon & pokemon, unsigned const defensive_ev) {
	pokemon.def.ev.set_value(defensive_ev);
}
template<>
void set_ev<Stat::SPD>(Pokemon & pokemon, unsigned const defensive_ev) {
	pokemon.spd.ev.set_value(defensive_ev);
}




class InvalidNatureCombination : public std::logic_error {
	public:
		InvalidNatureCombination():
			std::logic_error("Attempt to create a nature that cannot exist.") {
		}
};

Nature::Natures combine(NatureBoost const physical, NatureBoost const special) {
	switch (physical) {
	case Boost:
		switch (special) {
		case Boost:
			throw InvalidNatureCombination();
		case Neutral:
			return Nature::IMPISH;
		case Penalty:
			return Nature::LAX;
		}
	case Neutral:
		switch (special) {
		case Boost:
			return Nature::CALM;
		case Neutral:
			return Nature::HARDY;
		case Penalty:
			return Nature::NAIVE;
		}
	case Penalty:
		switch (special) {
		case Boost:
			return Nature::GENTLE;
		case Neutral:
			return Nature::HASTY;
		case Penalty:
			throw InvalidNatureCombination();
		}
	}
	throw InvalidNatureCombination();
}

template<>
Nature::Natures nature_effect<Stat::DEF>(NatureBoost nature) {
	switch (nature) {
	case Boost:
		return Nature::IMPISH;
	case Penalty:
		return Nature::HASTY;
	default:
		return Nature::HARDY;
	}
}
template<>
Nature::Natures nature_effect<Stat::SPD>(NatureBoost nature) {
	switch (nature) {
	case Boost:
		return Nature::CALM;
	case Penalty:
		return Nature::NAIVE;
	default:
		return Nature::HARDY;
	}
}

}	// unnamed namespace
}	// namespace technicalmachine