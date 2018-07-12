// Test checked collections
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

#include "collection.hpp"

#include "invalid_collection.hpp"
#include "move_container.hpp"
#include "variable_collection.hpp"

#include <bounded/integer_range.hpp>

#include <containers/array/make_array.hpp>
#include <containers/static_vector/static_vector.hpp>

#include <cassert>
#include <iostream>

namespace technicalmachine {

void collection_tests () {
	std::cout << "Running collection tests.\n";
	move_container_tests();
	variable_collection_tests();
	std::cout << "Collection tests passed.\n\n";
}

}	// namespace technicalmachine
