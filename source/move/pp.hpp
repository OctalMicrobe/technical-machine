// PP class
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

#ifndef MOVE__PP_HPP_
#define MOVE__PP_HPP_

#include <cstdint>
#include <utility>
#include <bounded_integer/optional.hpp>
#include <bounded_integer/bounded_integer.hpp>
#include "moves_forward.hpp"

namespace technicalmachine {
class Ability;

using namespace bounded::literal;

class Pp {
public:
	using pp_ups_type = bounded::checked_integer<0, 3>;
	Pp(Moves move, pp_ups_type pp_ups);
	uint64_t hash () const;
	uint64_t max_hash () const;
	auto is_empty() const -> bool;
	auto has_unlimited_pp() const -> bool;
	auto decrement(Ability const & foe_ability) -> void;
	auto trump_card_power() const -> bounded::integer<40, 200>;
	// Assumes max PP is the same because it assumes the same Move on the same
	// Pokemon
	friend auto operator== (Pp const & lhs, Pp const & rhs) -> bool;
private:
	using base_type = bounded::integer<1, 40>;
	using max_type = decltype(std::declval<base_type>() * (std::declval<pp_ups_type>() + 5_bi) / 5_bi);
	// clamped_integer simplifies situations like Pressure and Leppa
	using current_type = bounded::clamped_integer<0, static_cast<intmax_t>(std::numeric_limits<max_type>::max())>;
	bounded::optional<max_type> m_max;
	bounded::optional<current_type> m_current;
};
auto operator!= (Pp const & lhs, Pp const & rhs) -> bool;

}	// namespace technicalmachine
#endif	// MOVE__PP_HPP_
