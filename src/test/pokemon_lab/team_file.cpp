// Test PL team files
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

#include "team_file.hpp"

#include <iostream>
#include <random>

#include "../../team.hpp"
#include "../../pokemon_lab/read_team_file.hpp"
#include "../../pokemon_lab/write_team_file.hpp"

namespace technicalmachine {
namespace pl {

void test_team_file () {
	std::cout << "\tRunning Pokemon Lab team file tests.\n";
	// Temporary until I redesign my Team constructor to not require a random
	// engine when it's not needed.
	std::mt19937 unused;
	Team team (false, 6, unused);
	load_team (team, "src/test/test1.sbt", 6);
	write_team (team, "src/test/test2.sbt");
}

}	// namespace pl
}	// namespace technicalmachine
