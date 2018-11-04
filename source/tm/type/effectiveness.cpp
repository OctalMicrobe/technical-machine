// Effectiveness of a type
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

#include <tm/type/effectiveness.hpp>

#include <tm/type/collection.hpp>
#include <tm/type/type.hpp>
#include <tm/pokemon/pokemon.hpp>
#include <tm/rational.hpp>

#include <iterator>

namespace technicalmachine {
namespace {

constexpr auto no_effect = rational(0_bi, 1_bi);
constexpr auto not_very_effective = rational(1_bi, 2_bi);
constexpr auto regular = rational(1_bi, 1_bi);
constexpr auto super_effective = rational(2_bi, 1_bi);

constexpr auto lookup_effectiveness(Type const attacking, Type const defending) -> rational<bounded::integer<0, 2>, bounded::integer<1, 2>> {
	switch (attacking) {
		case Type::Bug: switch(defending) {
			case Type::Bug: return regular;
			case Type::Dark: return super_effective;
			case Type::Dragon: return regular;
			case Type::Electric: return regular;
			case Type::Fighting: return not_very_effective;
			case Type::Fire: return not_very_effective;
			case Type::Flying: return not_very_effective;
			case Type::Ghost: return not_very_effective;
			case Type::Grass: return super_effective;
			case Type::Ground: return regular;
			case Type::Ice: return regular;
			case Type::Normal: return regular;
			case Type::Poison: return not_very_effective;
			case Type::Psychic: return super_effective;
			case Type::Rock: return regular;
			case Type::Steel: return not_very_effective;
			case Type::Water: return regular;
			case Type::Typeless: return regular;
		}
		case Type::Dark: switch(defending) {
			case Type::Bug: return regular;
			case Type::Dark: return not_very_effective;
			case Type::Dragon: return regular;
			case Type::Electric: return regular;
			case Type::Fighting: return not_very_effective;
			case Type::Fire: return regular;
			case Type::Flying: return regular;
			case Type::Ghost: return super_effective;
			case Type::Grass: return regular;
			case Type::Ground: return regular;
			case Type::Ice: return regular;
			case Type::Normal: return regular;
			case Type::Poison: return regular;
			case Type::Psychic: return super_effective;
			case Type::Rock: return regular;
			case Type::Steel: return not_very_effective;
			case Type::Water: return regular;
			case Type::Typeless: return regular;
		}
		case Type::Dragon: switch(defending) {
			case Type::Bug: return regular;
			case Type::Dark: return regular;
			case Type::Dragon: return super_effective;
			case Type::Electric: return regular;
			case Type::Fighting: return regular;
			case Type::Fire: return regular;
			case Type::Flying: return regular;
			case Type::Ghost: return regular;
			case Type::Grass: return regular;
			case Type::Ground: return regular;
			case Type::Ice: return regular;
			case Type::Normal: return regular;
			case Type::Poison: return regular;
			case Type::Psychic: return regular;
			case Type::Rock: return regular;
			case Type::Steel: return not_very_effective;
			case Type::Water: return regular;
			case Type::Typeless: return regular;
		}
		case Type::Electric: switch(defending) {
			case Type::Bug: return regular;
			case Type::Dark: return regular;
			case Type::Dragon: return not_very_effective;
			case Type::Electric: return not_very_effective;
			case Type::Fighting: return regular;
			case Type::Fire: return regular;
			case Type::Flying: return super_effective;
			case Type::Ghost: return regular;
			case Type::Grass: return not_very_effective;
			case Type::Ground: return no_effect;
			case Type::Ice: return regular;
			case Type::Normal: return regular;
			case Type::Poison: return regular;
			case Type::Psychic: return regular;
			case Type::Rock: return regular;
			case Type::Steel: return regular;
			case Type::Water: return super_effective;
			case Type::Typeless: return regular;
		}
		case Type::Fighting: switch(defending) {
			case Type::Bug: return not_very_effective;
			case Type::Dark: return super_effective;
			case Type::Dragon: return regular;
			case Type::Electric: return regular;
			case Type::Fighting: return regular;
			case Type::Fire: return regular;
			case Type::Flying: return not_very_effective;
			case Type::Ghost: return no_effect;
			case Type::Grass: return regular;
			case Type::Ground: return regular;
			case Type::Ice: return super_effective;
			case Type::Normal: return super_effective;
			case Type::Poison: return not_very_effective;
			case Type::Psychic: return not_very_effective;
			case Type::Rock: return super_effective;
			case Type::Steel: return super_effective;
			case Type::Water: return regular;
			case Type::Typeless: return regular;
		}
		case Type::Fire: switch(defending) {
			case Type::Bug: return super_effective;
			case Type::Dark: return regular;
			case Type::Dragon: return not_very_effective;
			case Type::Electric: return regular;
			case Type::Fighting: return regular;
			case Type::Fire: return not_very_effective;
			case Type::Flying: return regular;
			case Type::Ghost: return regular;
			case Type::Grass: return super_effective;
			case Type::Ground: return regular;
			case Type::Ice: return super_effective;
			case Type::Normal: return regular;
			case Type::Poison: return regular;
			case Type::Psychic: return regular;
			case Type::Rock: return not_very_effective;
			case Type::Steel: return super_effective;
			case Type::Water: return not_very_effective;
			case Type::Typeless: return regular;
		}
		case Type::Flying: switch(defending) {
			case Type::Bug: return super_effective;
			case Type::Dark: return regular;
			case Type::Dragon: return regular;
			case Type::Electric: return not_very_effective;
			case Type::Fighting: return super_effective;
			case Type::Fire: return regular;
			case Type::Flying: return regular;
			case Type::Ghost: return regular;
			case Type::Grass: return super_effective;
			case Type::Ground: return regular;
			case Type::Ice: return regular;
			case Type::Normal: return regular;
			case Type::Poison: return regular;
			case Type::Psychic: return regular;
			case Type::Rock: return not_very_effective;
			case Type::Steel: return not_very_effective;
			case Type::Water: return regular;
			case Type::Typeless: return regular;
		}
		case Type::Ghost: switch(defending) {
			case Type::Bug: return regular;
			case Type::Dark: return not_very_effective;
			case Type::Dragon: return regular;
			case Type::Electric: return regular;
			case Type::Fighting: return regular;
			case Type::Fire: return regular;
			case Type::Flying: return regular;
			case Type::Ghost: return super_effective;
			case Type::Grass: return regular;
			case Type::Ground: return regular;
			case Type::Ice: return regular;
			case Type::Normal: return no_effect;
			case Type::Poison: return regular;
			case Type::Psychic: return super_effective;
			case Type::Rock: return regular;
			case Type::Steel: return not_very_effective;
			case Type::Water: return regular;
			case Type::Typeless: return regular;
		}
		case Type::Grass: switch(defending) {
			case Type::Bug: return not_very_effective;
			case Type::Dark: return regular;
			case Type::Dragon: return not_very_effective;
			case Type::Electric: return regular;
			case Type::Fighting: return regular;
			case Type::Fire: return not_very_effective;
			case Type::Flying: return not_very_effective;
			case Type::Ghost: return regular;
			case Type::Grass: return not_very_effective;
			case Type::Ground: return super_effective;
			case Type::Ice: return regular;
			case Type::Normal: return regular;
			case Type::Poison: return not_very_effective;
			case Type::Psychic: return regular;
			case Type::Rock: return super_effective;
			case Type::Steel: return not_very_effective;
			case Type::Water: return super_effective;
			case Type::Typeless: return regular;
		}
		case Type::Ground: switch(defending) {
			case Type::Bug: return not_very_effective;
			case Type::Dark: return regular;
			case Type::Dragon: return regular;
			case Type::Electric: return super_effective;
			case Type::Fighting: return regular;
			case Type::Fire: return super_effective;
			case Type::Flying: return no_effect;
			case Type::Ghost: return regular;
			case Type::Grass: return not_very_effective;
			case Type::Ground: return regular;
			case Type::Ice: return regular;
			case Type::Normal: return regular;
			case Type::Poison: return super_effective;
			case Type::Psychic: return regular;
			case Type::Rock: return super_effective;
			case Type::Steel: return super_effective;
			case Type::Water: return regular;
			case Type::Typeless: return regular;
		}
		case Type::Ice: switch(defending) {
			case Type::Bug: return regular;
			case Type::Dark: return regular;
			case Type::Dragon: return super_effective;
			case Type::Electric: return regular;
			case Type::Fighting: return regular;
			case Type::Fire: return not_very_effective;
			case Type::Flying: return super_effective;
			case Type::Ghost: return regular;
			case Type::Grass: return super_effective;
			case Type::Ground: return super_effective;
			case Type::Ice: return not_very_effective;
			case Type::Normal: return regular;
			case Type::Poison: return regular;
			case Type::Psychic: return regular;
			case Type::Rock: return regular;
			case Type::Steel: return not_very_effective;
			case Type::Water: return not_very_effective;
			case Type::Typeless: return regular;
		}
		case Type::Normal: switch(defending) {
			case Type::Bug: return regular;
			case Type::Dark: return regular;
			case Type::Dragon: return regular;
			case Type::Electric: return regular;
			case Type::Fighting: return regular;
			case Type::Fire: return regular;
			case Type::Flying: return regular;
			case Type::Ghost: return no_effect;
			case Type::Grass: return regular;
			case Type::Ground: return regular;
			case Type::Ice: return regular;
			case Type::Normal: return regular;
			case Type::Poison: return regular;
			case Type::Psychic: return regular;
			case Type::Rock: return not_very_effective;
			case Type::Steel: return not_very_effective;
			case Type::Water: return regular;
			case Type::Typeless: return regular;
		}
		case Type::Poison: switch(defending) {
			case Type::Bug: return regular;
			case Type::Dark: return regular;
			case Type::Dragon: return regular;
			case Type::Electric: return regular;
			case Type::Fighting: return regular;
			case Type::Fire: return regular;
			case Type::Flying: return regular;
			case Type::Ghost: return not_very_effective;
			case Type::Grass: return super_effective;
			case Type::Ground: return not_very_effective;
			case Type::Ice: return regular;
			case Type::Normal: return regular;
			case Type::Poison: return not_very_effective;
			case Type::Psychic: return regular;
			case Type::Rock: return not_very_effective;
			case Type::Steel: return no_effect;
			case Type::Water: return regular;
			case Type::Typeless: return regular;
		}
		case Type::Psychic: switch(defending) {
			case Type::Bug: return regular;
			case Type::Dark: return no_effect;
			case Type::Dragon: return regular;
			case Type::Electric: return regular;
			case Type::Fighting: return super_effective;
			case Type::Fire: return regular;
			case Type::Flying: return regular;
			case Type::Ghost: return regular;
			case Type::Grass: return regular;
			case Type::Ground: return regular;
			case Type::Ice: return regular;
			case Type::Normal: return regular;
			case Type::Poison: return super_effective;
			case Type::Psychic: return not_very_effective;
			case Type::Rock: return regular;
			case Type::Steel: return not_very_effective;
			case Type::Water: return regular;
			case Type::Typeless: return regular;
		}
		case Type::Rock: switch(defending) {
			case Type::Bug: return super_effective;
			case Type::Dark: return regular;
			case Type::Dragon: return regular;
			case Type::Electric: return regular;
			case Type::Fighting: return not_very_effective;
			case Type::Fire: return super_effective;
			case Type::Flying: return super_effective;
			case Type::Ghost: return regular;
			case Type::Grass: return regular;
			case Type::Ground: return not_very_effective;
			case Type::Ice: return super_effective;
			case Type::Normal: return regular;
			case Type::Poison: return regular;
			case Type::Psychic: return regular;
			case Type::Rock: return regular;
			case Type::Steel: return not_very_effective;
			case Type::Water: return regular;
			case Type::Typeless: return regular;
		}
		case Type::Steel: switch(defending) {
			case Type::Bug: return regular;
			case Type::Dark: return regular;
			case Type::Dragon: return regular;
			case Type::Electric: return not_very_effective;
			case Type::Fighting: return regular;
			case Type::Fire: return not_very_effective;
			case Type::Flying: return regular;
			case Type::Ghost: return regular;
			case Type::Grass: return regular;
			case Type::Ground: return regular;
			case Type::Ice: return super_effective;
			case Type::Normal: return regular;
			case Type::Poison: return regular;
			case Type::Psychic: return regular;
			case Type::Rock: return super_effective;
			case Type::Steel: return not_very_effective;
			case Type::Water: return not_very_effective;
			case Type::Typeless: return regular;
		}
		case Type::Water: switch(defending) {
			case Type::Bug: return regular;
			case Type::Dark: return regular;
			case Type::Dragon: return not_very_effective;
			case Type::Electric: return regular;
			case Type::Fighting: return regular;
			case Type::Fire: return super_effective;
			case Type::Flying: return regular;
			case Type::Ghost: return regular;
			case Type::Grass: return not_very_effective;
			case Type::Ground: return super_effective;
			case Type::Ice: return regular;
			case Type::Normal: return regular;
			case Type::Poison: return regular;
			case Type::Psychic: return regular;
			case Type::Rock: return super_effective;
			case Type::Steel: return regular;
			case Type::Water: return not_very_effective;
			case Type::Typeless: return regular;
		}
		case Type::Typeless: switch(defending) {
			case Type::Bug: return regular;
			case Type::Dark: return regular;
			case Type::Dragon: return regular;
			case Type::Electric: return regular;
			case Type::Fighting: return regular;
			case Type::Fire: return regular;
			case Type::Flying: return regular;
			case Type::Ghost: return regular;
			case Type::Grass: return regular;
			case Type::Ground: return regular;
			case Type::Ice: return regular;
			case Type::Normal: return regular;
			case Type::Poison: return regular;
			case Type::Psychic: return regular;
			case Type::Rock: return regular;
			case Type::Steel: return regular;
			case Type::Water: return regular;
			case Type::Typeless: return regular;
		}
	}
}

template<typename Container, typename... Products>
auto check_effectiveness(Container const & effectiveness, Products... results) {
	auto const value = effectiveness[0_bi] * effectiveness[1_bi];
	return (... or (value == results));
}



}	// namespace

Effectiveness::Effectiveness(Type const attacking, Type const defending1, Type const defending2):
	m_effectiveness({
		lookup_effectiveness(attacking, defending1),
		lookup_effectiveness(attacking, defending2)
	}) {
	// TODO: Write better trait that looks only at the values
	#if 0
	static_assert(
		std::is_same<decltype(lookup_effectiveness(attacking, defending1)), SingleType>::value,
		"Incorrect effectiveness type."
	);
	#endif
}

Effectiveness::Effectiveness(Type const type, Pokemon const & defender):
	Effectiveness(type, *begin(get_type(defender).types), *containers::next(begin(get_type(defender).types))) {
}

Effectiveness::Effectiveness(Type const attacking, Type const defending):
	Effectiveness(attacking, defending, Type::Typeless) {
}

auto Effectiveness::is_super_effective() const -> bool {
	return check_effectiveness(m_effectiveness, Product(super_effective), Product(super_effective * super_effective));
}

auto Effectiveness::is_not_very_effective() const -> bool {
	return check_effectiveness(m_effectiveness, Product(not_very_effective), Product(not_very_effective * not_very_effective));
}

auto Effectiveness::has_no_effect() const -> bool {
	return check_effectiveness(m_effectiveness, Product(no_effect));
}

}	// namespace technicalmachine