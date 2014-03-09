// Random effects of moves
// Copyright (C) 2014 David Stone
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

#ifndef VARIABLE_HPP_
#define VARIABLE_HPP_

#include <cstdint>
#include <vector>

#include <bounded_integer/bounded_integer.hpp>

#include "rational.hpp"
#include "move/moves_forward.hpp"
#include "pokemon/collection.hpp"
#include "pokemon/level.hpp"
#include "pokemon/species_forward.hpp"

namespace technicalmachine {
class ActivePokemon;
class Team;

// Used for moves with a variable power / length / other integer range. Moves of
// variable power: Magnitude = 4-10, Psywave = 5-15, Present = 0-4 (0 = heal).
// It is also used to determine whether random effects activate.
class Variable {
public:
	using value_type = bounded_integer::native_integer<0, 150>;
	using Probability = bounded_rational<bounded_integer::native_integer<0, 79>, bounded_integer::native_integer<1, 101>>;
	Variable();
	Variable(value_type value, Probability probability);
	// Team is the Team that was phazed, not the team that used the phazing move
	auto set_phaze_index(Team const & team, Species species) -> void;
	auto set_flinch(bool set = true) -> void;
	auto value() const -> value_type;
	auto probability() const -> Probability;
	auto effect_activates() const -> bool;
	auto phaze_index(PokemonCollection::index_type foe_index) const -> PokemonCollection::index_type;
	auto present_heals() const -> bool;

	using PsywaveDamage = bounded_integer::native_integer<1, 150>;
	auto psywave_damage(Level const level) const -> PsywaveDamage {
		return bounded_integer::max(1_bi, level() * static_cast<bounded_integer::native_integer<50, 150>>(value()) / 100_bi);
	}
	using Magnitude = bounded_integer::checked_integer<4, 10>;
	auto set_magnitude(Magnitude magnitude) -> void;
private:
	value_type m_value;
	Probability m_probability;
};

using Probabilities = std::vector<Variable>;
auto all_probabilities(ActivePokemon const & pokemon, TeamSize foe_size) -> Probabilities;

}	// namespace technicalmachine
#endif	// VARIABLE_HPP_
