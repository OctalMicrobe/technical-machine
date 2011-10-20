// Exception class for invalid packets
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

#ifndef NETWORK_INVALID_PACKET_H_
#define NETWORK_INVALID_PACKET_H_

#include <stdexcept>
#include <string>

namespace technicalmachine {
namespace network {

class InvalidPacket : public std::runtime_error {
	public:
		InvalidPacket (std::string const & reason): std::runtime_error (reason) { }
};
} // namespace network
} // namespace technicalmachine
#endif // NETWORK_INVALID_PACKET_H_
