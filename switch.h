// Switching-related functions header
// Copyright 2011 David Stone
//
// This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License
// as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef SWITCH_H_
#define SWITCH_H_

#include <vector>

namespace technicalmachine {

class Pokemon;
class Team;
class Weather;

void reset_variables (Team & team);
void switchpokemon (Team & switcher, Team & other, Weather & weather);
void entry_hazards (Team & switcher, Weather const & weather);
void activate_ability (Team & switcher, Team & other, Weather & weather);

}

#endif		// SWITCH_H_
