// Test checked collections
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

#include <tm/test/collections/collection.hpp>

#include <tm/test/collections/move_container.hpp>
#include <tm/test/collections/variable_collection.hpp>

#include <iostream>

namespace technicalmachine {

void collection_tests () {
	std::cout << "Running collection tests.\n";
	move_container_tests();
	variable_collection_tests();
	std::cout << "Collection tests passed.\n\n";
}

}	// namespace technicalmachine
