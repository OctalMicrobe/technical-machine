// Class that handles Embargo
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

#include "embargo.hpp"

namespace technicalmachine {
using namespace bounded::literal;

auto Embargo::is_active() const -> bool {
	return static_cast<bool>(m_turns_remaining);
}

auto Embargo::activate() -> void {
	m_turns_remaining = 0_bi;
}

auto Embargo::advance_one_turn() -> void {
	if (!is_active()) {
		return;
	}
	if (*m_turns_remaining == std::numeric_limits<value_type>::max()) {
		m_turns_remaining = bounded::none;
	} else {
		++*m_turns_remaining;
	}
}

auto operator==(Embargo const lhs, Embargo const rhs) -> bool {
	return lhs.m_turns_remaining == rhs.m_turns_remaining;
}

auto operator!=(Embargo const lhs, Embargo const rhs) -> bool {
	return !(lhs == rhs);
}

}	// namespace technicalmachine
