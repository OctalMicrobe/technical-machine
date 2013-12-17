// AI to win a 1v1 battle
// Copyright (C) 2013 David Stone
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

#include <boost/lexical_cast.hpp>

#include "exit_program.hpp"

#include "clients/network/invalid_packet.hpp"
#include "clients/pokemon_online/client.hpp"
#include "clients/pokemon_showdown/client.hpp"

using namespace technicalmachine;

namespace {
void print_debug_statements();
}	// unnamed namespace

int main (int argc, char * argv []) {
	try {
		print_debug_statements();
		unsigned const depth = (argc == 1) ? 2 : boost::lexical_cast <unsigned> (argv [1]);

		// TODO: This is not the correct solution, but it works "good enough".
		// I'll get back to this later.
		while (true) {
			try {
				po::Client client(depth);
				client.run();
			}
			catch (network::InvalidPacket const & error) {
				constexpr unsigned time_in_seconds = 10;
				std::cerr << error.what () << " Disconnected. Waiting " << time_in_seconds << " seconds and trying again.\n";
				// I disconnect from the server at this point and try again, because
				// this means an unrecoverable error.
				sleep (time_in_seconds);
				std::cerr << "Reconnecting.\n";
			}
		}
	}
	catch (ExitProgram const &) {
		return 0;
	}
	catch (...) {
		throw;
	}
}

namespace {
void print_debug_statements() {
	std::cout << "sizeof (Team): " << sizeof(Team) << '\n';
	std::cout << "sizeof (Pokemon): " << sizeof(Pokemon) << '\n';
	std::cout << "sizeof (Move): " << sizeof(Move) << '\n';
	constexpr auto heap_allocated_size = 6 * (sizeof(Pokemon) + 4 * (sizeof(Move)));
	constexpr auto full_team_size = sizeof(Team) + heap_allocated_size;
	std::cout << "size of full team: " << full_team_size << '\n';
	std::cout << "heap allocated_size: " << heap_allocated_size << '\n';
}
}	// unnamed namespace
