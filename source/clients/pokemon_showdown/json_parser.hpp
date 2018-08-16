// Parse json messages from Pokemon Showdown
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

#pragma once

#include <boost/property_tree/ptree.hpp>

#include <sstream>
#include <string_view>

namespace technicalmachine {
namespace ps {

struct JSONParser {
	boost::property_tree::ptree operator()(std::string_view str);
	
private:
	std::stringstream m_json_buffer;
};

}	// namespace ps
}	// namespace technicalmachine
