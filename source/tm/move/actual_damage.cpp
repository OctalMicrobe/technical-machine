// Copyright (C) 2019 David Stone
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

#include <tm/move/actual_damage.hpp>

#include <tm/move/calculate_damage.hpp>
#include <tm/move/category.hpp>
#include <tm/move/will_be_recharge_turn.hpp>

#include <tm/team.hpp>

#include <bounded/detail/overload.hpp>

namespace technicalmachine {

auto ActualDamage::value(Generation const generation, Team const & user, ExecutedMove const executed, bool const move_weakened_from_item, Team const & other, OtherMove const other_move, Weather const weather) const -> damage_type {
	auto calculate = [&]{
		auto const substitute = substitute_interaction(generation, executed.move.name);
		auto const no_damage =
			!is_damaging(executed.move.name) or
			(other.pokemon().substitute() and substitute != Substitute::bypassed) or
			will_be_recharge_turn(user.pokemon(), executed.move.name, other.pokemon().ability(), weather);
		return no_damage ? 0_bi : calculate_damage(generation, user, executed, move_weakened_from_item, other, other_move, weather);
	};

	return bounded::visit(m_value, bounded::overload(
		[=](Unknown) { return calculate(); },
		[=](Capped const capped) -> damage_type { return bounded::min(calculate(), capped.value); },
		[](Known const known) -> damage_type { return known.value; }
	));
}

} // namespace technicalmachine
