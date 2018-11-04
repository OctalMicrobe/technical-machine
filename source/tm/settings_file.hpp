// Read and write settings files
// Copyright (C) 2016 David Stone
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

#include <containers/vector.hpp>

#include <boost/property_tree/ptree.hpp>

#include <filesystem>
#include <string>

namespace technicalmachine {

struct Server {
	explicit Server (boost::property_tree::ptree const & root);
	void add (boost::property_tree::ptree & root) const;

	std::string host;
	std::string port;
	std::string username;
	std::string password;
	boost::optional<std::string> resource;
private:
	std::string server_name;
};

struct Settings {
	Settings();
	void write() const;
	static std::filesystem::path const & file_name();

	std::filesystem::path team_file;
	containers::vector<Server> servers;
	unsigned chattiness;
};

}	// namespace technicalmachine