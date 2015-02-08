// Priority data structure
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

#ifndef MOVE__PRIORITY_HPP_
#define MOVE__PRIORITY_HPP_

#include <bounded_integer/bounded_integer.hpp>
#include "moves.hpp"

namespace technicalmachine {

class Priority {
public:
	explicit Priority(Moves move);
	friend auto operator== (Priority lhs, Priority rhs) -> bool;
	friend auto operator< (Priority lhs, Priority rhs) -> bool;
private:
	bounded::checked_integer<-6, 6> priority;
};

auto operator!= (Priority lhs, Priority rhs) -> bool;
auto operator> (Priority lhs, Priority rhs) -> bool;
auto operator<= (Priority lhs, Priority rhs) -> bool;
auto operator>= (Priority lhs, Priority rhs) -> bool;

}	// namespace technicalmachine
#endif	// MOVE__MOVE_HPP_
