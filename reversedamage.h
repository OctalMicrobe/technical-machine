// Reverse damage calculator function definitions
// Copyright 2011 David Stone
//
// This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License
// as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef REVERSEDAMAGE_H_
#define REVERSEDAMAGE_H_

#include <vector>
#include "team.h"
#include "weather.h"
#include "unknown.h"

namespace technicalmachine {

void reversedamagecalculator (teams &attacker, const teams &defender, const weathers &weather, int damage, std::vector<Unknown> &hidden);

}
#endif
