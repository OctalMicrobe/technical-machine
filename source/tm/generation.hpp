// Copyright David Stone 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <bounded/integer.hpp>

#include <cstdint>

namespace technicalmachine {

enum class Generation : std::uint8_t {
	one = 1,
	two = 2,
	three = 3,
	four = 4,
	five = 5,
	six = 6,
	seven = 7,
	eight = 8,
};

} // namespace technicalmachine
namespace bounded {

template<>
inline constexpr auto min_value<technicalmachine::Generation> = technicalmachine::Generation::one;

template<>
inline constexpr auto max_value<technicalmachine::Generation> = technicalmachine::Generation::eight;

}	// namespace bounded
