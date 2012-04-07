// Read and write settings files
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

#ifndef SETTINGS_FILE_HPP_
#define SETTINGS_FILE_HPP_

#include <string>
#include <vector>

#include <boost/property_tree/ptree.hpp>

namespace technicalmachine {
namespace network {
class GenericClient;
}	// namespace network

class Server {
private:
	std::string server_name;
public:
	std::string host;
	std::string port;
	std::string username;
	std::string password;
	explicit Server (boost::property_tree::ptree const & root);
	void add (boost::property_tree::ptree & root) const;
};

class Settings {
public:
	std::string team_file;
	std::vector <Server> servers;
	std::string time_format;
	unsigned chattiness;
	static std::string const file_name;
	Settings ();
	void write () const;
};

}	// namespace technicalmachine
#endif	// SETTINGS_FILE_HPP_