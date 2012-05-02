// End of turn effects
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

#include "endofturn.hpp"

#include <cstdint>

#include "ability.hpp"
#include "damage.hpp"
#include "heal.hpp"
#include "move.hpp"
#include "pokemon.hpp"
#include "status.hpp"
#include "team.hpp"
#include "weather.hpp"

namespace technicalmachine {
namespace {

void endofturn0 (Team & team);
void endofturn1 (Team & team);
void endofturn2 (Team & team);
void endofturn3 (Team & team, Weather const & weather);
void endofturn5 (Team & team, Pokemon & foe, Weather & weather);
void endofturn6 (Team & target, Weather const & weather);
void endofturn7 (Team & team);
void reset_variable (Team & team);

template<typename Integer>
void decrement (Integer & n) {
	if (n > 0)
		--n;
}

}	// unnamed namespace

void endofturn (Team & first, Team & last, Weather & weather) {
	endofturn0 (first);
	endofturn0 (last);
	endofturn1 (first);
	endofturn1 (last);
	endofturn2 (first);
	endofturn2 (last);
	weather.decrement();	// The order doesn't matter here.
	if (!first.pokemon().ability.blocks_weather () and !last.pokemon().ability.blocks_weather ()) {
		endofturn3 (first, weather);
		endofturn3 (last, weather);
	}
	endofturn5 (first, last.pokemon(), weather);
	endofturn5 (last, first.pokemon(), weather);
	endofturn6 (first, weather);
	endofturn6 (last, weather);
	endofturn7 (first);
	endofturn7 (last);
	reset_variable (first);
	reset_variable (last);
}

namespace {

void endofturn0 (Team & team) {
	team.damage = 0;
	team.damaged = false;
	team.endure = false;
	team.flinch = false;
	team.moved = false;
	team.me_first = false;
	team.loaf = !team.loaf;
	team.protect = false;
	team.replacing = false;
}

void endofturn1 (Team & team) {
	decrement (team.light_screen);
	decrement (team.lucky_chant);
	decrement (team.mist);
	decrement (team.reflect);
	decrement (team.safeguard);
	decrement (team.tailwind);
}

void endofturn2 (Team & team) {
	if (team.wish == 1)
		heal (team.pokemon(), 2);
	decrement (team.wish);
}

void endofturn3 (Team & team, Weather const & weather) {
	if (weather.hail() and !team.pokemon().type.is_immune_to_hail())
		heal (team.pokemon(), -16);
	if (weather.sand() and !team.pokemon().type.is_immune_to_sandstorm())
		heal (team.pokemon(), -16);
	switch (team.pokemon().ability.name) {
		case Ability::DRY_SKIN:
			if (weather.rain())
				heal (team.pokemon(), 8);
			else if (weather.sun())
				heal (team.pokemon(), -8);
			break;
		case Ability::HYDRATION:
			if (weather.rain())
				team.pokemon().status.clear ();
			break;
		case Ability::ICE_BODY:
			if (weather.hail())
				heal (team.pokemon(), 16);
			break;
		case Ability::RAIN_DISH:
			if (weather.rain())
				heal (team.pokemon(), 16);
			break;
		default:
			break;
	}
}

void endofturn5 (Team & team, Pokemon & foe, Weather & weather) {
	Pokemon & pokemon = team.pokemon();
	if (team.ingrain)
		heal (pokemon, 16);
	if (team.aqua_ring)
		heal (pokemon, 16);
	if (pokemon.ability.boosts_speed())
		Stat::boost (team.stage [Stat::SPE], 1);
	else if (team.shed_skin)
		pokemon.status.clear ();
	switch (pokemon.item.name) {
		case Item::LEFTOVERS:
			heal (pokemon, 16);
			break;
		case Item::BLACK_SLUDGE:
			heal (pokemon, (is_type (team, Type::POISON)) ? 16 : -16);
			break;
		default:
			break;
	}
	if (team.leech_seed) {
		unsigned n = pokemon.hp.stat;
		heal (pokemon, -8);
		if (foe.hp.stat != 0) {
			if (pokemon.ability.damages_leechers ())
				damage_side_effect (foe, n - pokemon.hp.stat);
			else {
				foe.hp.stat += n - pokemon.hp.stat;
				if (foe.hp.stat > foe.hp.max)
					foe.hp.stat = foe.hp.max;
			}
		}
	}
	switch (pokemon.status.name()) {
		case Status::BURN:
			heal(pokemon, pokemon.ability.weakens_burn() ? -16 : -8);
			break;
		case Status::POISON:
			heal(pokemon, pokemon.ability.absorbs_poison_damage() ? 8 : -8);
			break;
		case Status::POISON_TOXIC:
			if (pokemon.ability.absorbs_poison_damage ())
				heal (pokemon, 8);
			else {
				if (team.toxic < 15)
					++team.toxic;
				heal (pokemon, -16, team.toxic);
			}
			break;
		case Status::SLEEP:
			if (team.nightmare)
				heal (pokemon, -4);
			if (foe.ability.harms_sleepers())
				heal (pokemon, -8);
			break;
		default:
			break;
	}
	switch (pokemon.item.name) {
		case Item::FLAME_ORB:
			Status::burn (pokemon, pokemon, weather);
			break;
		case Item::TOXIC_ORB:
			Status::poison_toxic (pokemon, pokemon, weather);
			break;
		default:
			break;
	}
	if (team.curse)
		heal (pokemon, -4);
	if (team.partial_trap > 0) {
		heal (pokemon, -16);
		--team.partial_trap;
	}
	
	// Can't use decrement here because I only want to cause confusion when team.rampage becomes 0.
	if (team.rampage) {
		--team.rampage;
		if (team.rampage == 0)
			team.confused = true;
	}
	else
		decrement (team.uproar);
		// weather.uproar is already decremented
	
	pokemon.move.for_each_regular_move([](Move & move) {
		decrement (move.disable);
	});
	decrement (team.encore);
	decrement (team.taunt);
	decrement (team.magnet_rise);
	decrement (team.heal_block);
	decrement (team.embargo);
	if (team.yawn == 1)
		Status::sleep (pokemon, pokemon, weather);
	decrement (team.yawn);
	if (pokemon.item.name == Item::STICKY_BARB)
		heal (pokemon, -8);
}

void endofturn6 (Team & target, Weather const & weather) {		// Doom Desire / Future Sight
	if (target.counter == 1) {
	}
	decrement (target.counter);
}

void endofturn7 (Team & team) {
	if (team.perish_song == 1)
		team.pokemon().hp.stat = 0;
	decrement (team.perish_song);
}

void reset_variable (Team & team) {
	team.pokemon.for_each([](Pokemon & pokemon) {
		pokemon.move.for_each([](Move & move) {
			move.variable.reset_index();
		});
	});
}

}	// unnamed namespace
}	// namespace technicalmachine
