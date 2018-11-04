// Test PO stuff
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

#include <tm/test/pokemon_online/test.hpp>

#include <iostream>

#include <tm/test/pokemon_online/conversion.hpp>
#include <tm/test/pokemon_online/team_file.hpp>

namespace technicalmachine {
namespace po {

void test () {
	std::cout << "Running Pokemon Online tests.\n";
	test_conversions ();
	test_team_file ();
	std::cout << "Pokemon Online tests passed.\n\n";
}

}	// namespace po
}	// namespace technicalmachine