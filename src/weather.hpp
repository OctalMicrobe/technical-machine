// Weather class
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

#ifndef WEATHER_HPP_
#define WEATHER_HPP_

#include <cstdint>
#include "status.hpp"

namespace technicalmachine {

// Weather is the set of things that are not specific to either team.

// Weathers are represented as an int8_t due to the "acid weather" effect,
// which means that multiple weathers can be in effect at the same time. The
// order of the weathers is their order when all effects are active. Uproar is
// present because it can be activated without being associated with any
// particular Pokemon.

// The number represents the number of turns remaining on that weather. A value
// of -1 indicates permanent weather. Fog is a bool because it only exists as a
// permanent weather condition.

class Weather {
	public:
		int8_t trick_room;
		bool fog;
		int8_t gravity;
		int8_t uproar;
		int8_t hail;
		int8_t sun;
		int8_t sand;
		int8_t rain;
	
		bool operator== (Weather const & other) const;
		Weather ();
		void set_trick_room ();
		void set_gravity ();
		void set_uproar (int8_t duration);
		void set_hail (int8_t duration);
		void set_sun (int8_t duration);
		void set_sand (int8_t duration);
		void set_rain (int8_t duration);
		template<Status::Statuses status>
		bool blocks_status () const {
			return false;
		}
		uint32_t hash () const;
};

}	// namespace technicalmachine
#endif	// WEATHER_HPP_
