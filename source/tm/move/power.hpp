// Copyright David Stone 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <tm/move/executed_move.hpp>

#include <tm/generation.hpp>
#include <tm/weather.hpp>

#include <bounded/integer.hpp>

namespace technicalmachine {
enum class Moves : std::uint16_t;
template<Generation>
struct Team;

// If a damaging move does not have power (for instance, OHKO moves and
// fixed-damage moves), the behavior of this function is undefined. If
// `executed.move.name` is Hidden Power, `attacker.pokemon().hidden_power()`
// must not be `none`.
using MovePower = bounded::integer<1, 1440>;
template<Generation generation>
auto move_power(Team<generation> const & attacker, ExecutedMove<generation> executed, Team<generation> const & defender, Weather weather) -> MovePower;

#define TECHNICALMACHINE_EXTERN_INSTANTIATION(generation) \
	extern template auto move_power<generation>(Team<generation> const & attacker_team, ExecutedMove<generation> const executed, Team<generation> const & defender_team, Weather const weather) -> MovePower

TECHNICALMACHINE_EXTERN_INSTANTIATION(Generation::one);
TECHNICALMACHINE_EXTERN_INSTANTIATION(Generation::two);
TECHNICALMACHINE_EXTERN_INSTANTIATION(Generation::three);
TECHNICALMACHINE_EXTERN_INSTANTIATION(Generation::four);
TECHNICALMACHINE_EXTERN_INSTANTIATION(Generation::five);
TECHNICALMACHINE_EXTERN_INSTANTIATION(Generation::six);
TECHNICALMACHINE_EXTERN_INSTANTIATION(Generation::seven);
TECHNICALMACHINE_EXTERN_INSTANTIATION(Generation::eight);

#undef TECHNICALMACHINE_EXTERN_INSTANTIATION

}	// namespace technicalmachine
