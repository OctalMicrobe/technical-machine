// Test stuff
// Copyright (C) 2011 David Stone
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

#include <iostream>

#include "string_conversion.hpp"
#include "pokemon_lab/test.hpp"
#include "pokemon_online/test.hpp"

int main () {
	using namespace technicalmachine;
	bool const string_conversion = string_conversion_tests ();
	std::cout << "String conversion tests " << (string_conversion ? "passed." : "failed.") << "\n\n";

	bool const pl = pl::test ();
	std::cout << "Pokemon Lab tests " << (pl ? "passed." : "failed.") << "\n\n";

	bool const po = po::test ();
	std::cout << "Pokemon Online tests " << (po ? "passed." : "failed.") << "\n\n";

	bool const passed = string_conversion and pl and po;
	if (passed)
		std::cout << "All tests passed.\n";
	else
		std::cerr << "Test failed.\n";
	return !passed;
}
