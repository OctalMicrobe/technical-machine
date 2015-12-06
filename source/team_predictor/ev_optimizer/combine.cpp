// Combine all optimized EVs and correct the Pokemon
// Copyright (C) 2015 David Stone
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

#include "combine.hpp"

#include "defensive.hpp"
#include "offensive.hpp"
#include "speed.hpp"

#include "../../pokemon/pokemon.hpp"

#include "../../string_conversions/nature.hpp"

#include <bounded_integer/bounded_integer.hpp>

#include <containers/static_vector/static_vector.hpp>

#include <algorithm>
#include <cassert>
#include <iostream>

namespace technicalmachine {
namespace {

struct Combined {
	Nature nature;
	EV hp;
	EV attack;
	EV defense;
	EV special_attack;
	EV special_defense;
	EV speed;
};

constexpr auto sum(Combined const combined) {
	return combined.hp.value() + combined.attack.value() + combined.defense.value() + combined.special_attack.value() + combined.special_defense.value() + combined.speed.value();
}

}	// namespace

void combine(OffensiveEVs const & o, DefensiveEVs const & d, SpeedEVs const & speed_container, Pokemon & pokemon) {
	containers::static_vector<Combined, SpeedEVs::max_size> container;
	for (auto const & speed : speed_container) {
		auto const offensive = o.container.find(speed.nature);
		if (offensive == o.container.end()) {
			continue;
		}
		auto const defensive = d.container.find(speed.nature);
		if (defensive == d.container.end()) {
			continue;
		}
		auto combined = Combined{
			speed.nature,
			defensive->second.hp,
			offensive->second.attack,
			defensive->second.defense,
			offensive->second.special_attack,
			defensive->second.special_defense,
			speed.ev
		};
		if (sum(combined) > EV::max_total) {
			continue;
		}
		push_back(container, combined);
	}

	auto const lesser_mapped_type = [](auto const & lhs, auto const & rhs) {
		return sum(lhs) < sum(rhs);
	};
	auto const it = std::min_element(container.begin(), container.end(), lesser_mapped_type);

	if (it == container.end()) {
		std::cerr << to_string(pokemon) << '\n';
		std::cerr << "Speed:\n";
		for (auto const & value : speed_container) {
			std::cerr << '\t' << to_string(value.nature) << " : " << value.ev.value() << '\n';
		}
		std::cerr << "Offensive:\n";
		for (auto const & value : o.container) {
			std::cerr << '\t' << to_string(value.first) << " : " << value.second.attack.value() << ", " << value.second.special_attack.value() << '\n';
		}
		std::cerr << "Defensive:\n";
		for (auto const & value : d.container) {
			std::cerr << '\t' << to_string(value.first) << " : " << value.second.hp.value() << ", " << value.second.defense.value() << ", " << value.second.special_defense.value() << '\n';
		}
	}
	assert(it != container.end());
	assert(sum(*it) <= EV::max_total);

	set_hp_ev(pokemon, it->hp);
	set_stat_ev(pokemon, StatNames::ATK, it->attack);
	set_stat_ev(pokemon, StatNames::DEF, it->defense);
	set_stat_ev(pokemon, StatNames::SPA, it->special_attack);
	set_stat_ev(pokemon, StatNames::SPD, it->special_defense);
	set_stat_ev(pokemon, StatNames::SPE, it->speed);
	get_nature(pokemon) = it->nature;
}

}	// namespace technicalmachine
