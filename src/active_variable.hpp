// Template specialization for Active
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

#ifndef ACTIVE_VARIABLE_HPP_
#define ACTIVE_VARIABLE_HPP_

#include "active.hpp"
#include <cassert>
#include <cstdint>
#include <functional>
#include <utility>

namespace technicalmachine {

template<>
class Active<std::pair<uint16_t, uint16_t>> : public detail::BaseActive<std::pair<uint16_t, uint16_t>> {
	public:
		Active () = default;
		Active (detail::BaseActive<std::pair<uint16_t, uint16_t>>::container_type const & pre_set):
			detail::BaseActive<std::pair<uint16_t, uint16_t>>(pre_set) {
		}
		void set_phaze_index (uint8_t const pokemon_index, uint8_t const new_index) {
			if (container.size() == 1) {
				assert (new_index == 0);
				reset_index();
			}
			else
				set_index ((new_index < pokemon_index) ? new_index : new_index - 1);
		}
		uint8_t phaze_index (uint8_t const pokemon_index) const {
			if (container.size() <= 1)
				throw InvalidActiveIndex (pokemon_index, container.size(), "phaze variable");
			return (operator()().first < pokemon_index) ? operator()().first : operator()().first + 1;
		}
};
}	// namespace technicalmachine
#endif	// ACTIVE_VARIABLE_HPP_
