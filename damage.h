// Damage calculator forward declarations
// Copyright 2011 David Stone
//
// This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License
// as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef DAMAGE_H_
#define DAMAGE_H_

#include "pokemon.h"
#include "team.h"
#include "weather.h"

namespace technicalmachine {

void movepower (Team &attacker, Team const &defender, Weather const weather);

int damageknown (Team const &attacker, Team const &defender, Weather const &weather, int &rl, int &weather_mod, int &ff, int &mf);

int damagenonrandom (Team const &attacker, Team const &defender, int const &rl, int const &weather_mod, int const &ff, int const &mf, int &stab, int const &type1, int const &type2, int &aem, int &eb, int &tl, int &rb, int damage);

int damagerandom (Pokemon const &attacker, Team const &defender, int const &stab, int const &type1, int const &type2, int const &aem, int const &eb, int const &tl, int const &rb, int damage);

int damagecalculator (Team const &attacker, Team const &defender, Weather const &weather);

void recoil (Pokemon &user, int damage, int denominator);
}

#endif
