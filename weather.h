// Weather data structure
// Copyright 2010 David Stone
//
// This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License
// as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef WEATHER_H_
#define WEATHER_H_

/*
Weather is defined as the set of things that are not specific to either team.

Weathers are represented as an char due to the "acid weather" effect, which means that multiple weathers can be in effect at the same time. The order of the weathers is their order when all effects are active. Uproar is present because it can be activated without being associated with any particular Pokemon.

The number for the char represents the number of turns remaining on that weather. A value of -1 indicates permanent weather. Fog is a bool because it only exists as a permanent weather condition.
*/

struct weathers {
	char trick_room;
	bool fog;
	char gravity;
	char uproar;
	char hail;
	char sun;
	char sand;
	char rain;
};

#endif
