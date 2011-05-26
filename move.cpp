// Use moves
// Copyright 2011 David Stone
//
// This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License
// as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "move.h"
#include "movefunction.h"
#include "ability.h"
#include "block.h"
#include "damage.h"
#include "heal.h"
#include "pokemon.h"
#include "statfunction.h"
#include "statusfunction.h"
#include "switch.h"
#include "type.h"
#include "typefunction.h"
#include "weather.h"

namespace technicalmachine {

Move::Move (moves_list move, int pp_ups) :
	name (move),
	type (move_type [name]),
	basepower (base_power [name]),
	physical (is_physical [name]),
	disable (0),
	pp_max (get_pp [name] * (5 + pp_ups) / 5),
	pp (pp_max),
	r (100),
	times_used (0),
	probability (get_probability [name]) {
		set_priority();
		set_variable();
}

void Move::set_priority () {
	if (is_switch())
		priority = 6;
	else if (name == HELPING_HAND)
		priority = 5;
	else if (name == MAGIC_COAT or name == SNATCH)
		priority = 4;
	else if (name == DETECT or name == ENDURE or name == FOLLOW_ME or name == PROTECT)
		priority = 3;
	else if (name ==  FEINT)
		priority = 2;
	else if (name == AQUA_JET or name == BIDE or name == BULLET_PUNCH or name == EXTREMESPEED or name == FAKE_OUT or name == ICE_SHARD or name == MACH_PUNCH or name == QUICK_ATTACK or name == SHADOW_SNEAK or name == SUCKER_PUNCH or name == VACUUM_WAVE)
		priority = 1;
	else if (name == VITAL_THROW)
		priority = -1;
	else if (name == FOCUS_PUNCH)
		priority = -2;
	else if (name == AVALANCHE or name == REVENGE)
		priority = -3;
	else if (name == COUNTER or name == MIRROR_COAT)
		priority = -4;
	else if (name == ROAR  or name == WHIRLWIND)
		priority = -5;
	else if (name == TRICK_ROOM)
		priority = -6;
	else
		priority = 0;
}

void Move::set_variable () {
	if (name == ACUPRESSURE) {
		for (int n = 0; n <= 6; ++n)
			variable.set.push_back(n);
	}
	else if (name == BIND or name == CLAMP or name == FIRE_SPIN or name == MAGMA_STORM or name == SAND_TOMB or name == WHIRLPOOL or name == WRAP) {
		for (int n = 2; n <= 5; ++n)
			variable.set.push_back(n);
	}
	else if (name == ENCORE) {
		for (int n = 4; n <= 8; ++n)
			variable.set.push_back(n);
	}
	else if (name == MAGNITUDE ) {
		for (int n = 10; n <= 110; n += 20)
			variable.set.push_back(n);
		variable.set.push_back(150);
/*		4 = 10;
		5 = 30;
		6 = 50;
		7 = 70;
		8 = 90;
		9 = 110;
		10 = 150;*/
	}
	else if (name == OUTRAGE or name == PETAL_DANCE or name == THRASH) {
		variable.set.push_back (2);
		variable.set.push_back (3);
	}
	else if (name == PRESENT) {
		for (int n = 0; n <= 120; n += 40)
			variable.set.push_back(n);
	}
	else if (name == ROAR or name == WHIRLWIND) {
		for (unsigned int n = 0; n != 6; ++n)
			variable.set.push_back(n);
	}
	else if (name == TAUNT) {
		variable.set.push_back(2);
		variable.set.push_back(3);
	}
	else if (name == TRI_ATTACK) {
		for (int n = 0; n <= 2; ++n)
			variable.set.push_back(n);
	}
	else if (variable.set.size() == 0)
		variable.set.push_back(0);
}

int usemove (Team &user, Team &target, Weather &weather, int log_damage) {
	int damage = 0;
	user.destiny_bond = false;
	user.moved = true;
	user.pokemon->move->execute = true;
	blockexecution (user, target, weather);
	if (user.pokemon->move->execute) {
		lower_pp (user, *target.pokemon);
//		if (ASSIST == user.pokemon->move->name or COPYCAT == user.pokemon->move->name or ME_FIRST == user.pokemon->move->name or METRONOME_MOVE == user.pokemon->move->name or MIRROR_MOVE == user.pokemon->move->name or SLEEP_TALK == user.pokemon->move->name)
//			usemove2 (user, target, move2, weather);		// ???
//		 (NATURE_POWER == user.pokemon->move->name)
//		else
		if (!user.miss)
			damage = usemove2 (user, target, weather, log_damage);
	}
	return damage;
}

int usemove2 (Team &user, Team &target, Weather &weather, int log_damage) {
	speed (user, weather);
	speed (target, weather);
	movepower (user, target, weather);
	int damage = 0;
	
	if (user.pokemon->move->basepower != 0) {
		if (BRICK_BREAK == user.pokemon->move->name) {
			target.reflect = 0;
			target.light_screen = 0;
		}
		else if (FLAME_WHEEL == user.pokemon->move->name or SACRED_FIRE == user.pokemon->move->name) {
			if (user.pokemon->status == FREEZE)
				user.pokemon->status = NO_STATUS;
		}
		if (log_damage == -1) {
			defense (user, target, weather);
			attack (user, weather);
			damage = damagecalculator (user, target, weather);
		}
		else {
			damage = log_damage;
		}
		if (damage != 0)
			do_damage (user, target, damage);
	}
	++user.pokemon->move->times_used;

	if (ACID_ARMOR == user.pokemon->move->name or BARRIER == user.pokemon->move->name or IRON_DEFENSE == user.pokemon->move->name)
		user.pokemon->def.boost (2);
	else if (AGILITY == user.pokemon->move->name or ROCK_POLISH == user.pokemon->move->name)
		user.pokemon->spe.boost (2);
	else if (AMNESIA == user.pokemon->move->name)
		user.pokemon->spd.boost (2);
	else if (AQUA_RING == user.pokemon->move->name)
		user.aqua_ring = true;
	else if (AROMATHERAPY == user.pokemon->move->name) {
		for (std::vector<Pokemon>::iterator it = user.pokemon.set.begin(); it != user.pokemon.set.end(); ++it)
			it->status = NO_STATUS;
	}
	else if (ATTRACT == user.pokemon->move->name) {
		if (user.pokemon->gender * target.pokemon->gender == -1)		// male * female == -1
			target.attract = true;
	}
	else if (BATON_PASS == user.pokemon->move->name and false) {
		user.pokemon.set [user.replacement].atk.stage = user.pokemon->atk.stage;
		user.pokemon.set [user.replacement].def.stage = user.pokemon->def.stage;
		user.pokemon.set [user.replacement].spa.stage = user.pokemon->spa.stage;
		user.pokemon.set [user.replacement].spd.stage = user.pokemon->spd.stage;
		user.pokemon.set [user.replacement].spe.stage = user.pokemon->spe.stage;
		
		// Change the active Pokemon to the one switching in.
		switchpokemon (user, target, weather);
	}
	else if (BELLY_DRUM == user.pokemon->move->name) {
		user.pokemon->atk.stage = 6;
		if (user.pokemon->hp.max <= 2)
			--user.pokemon->hp.stat;
		else
			user.pokemon->hp.stat -= user.pokemon->hp.max / 2;
	}
	else if (BIDE == user.pokemon->move->name) {
		if (user.bide == 0) {
			user.bide = 2;
			user.bide_damage = 0;
		}
		else {
			if (user.bide == 1)
				target.pokemon->hp.stat -= user.bide_damage * 2;
			--user.bide;
		}
}
	else if (BLAST_BURN == user.pokemon->move->name or FRENZY_PLANT == user.pokemon->move->name or GIGA_IMPACT == user.pokemon->move->name or HYDRO_CANNON == user.pokemon->move->name or HYPER_BEAM == user.pokemon->move->name or ROAR_OF_TIME == user.pokemon->move->name or ROCK_WRECKER == user.pokemon->move->name)
		user.recharging = true;
	else if (BLOCK == user.pokemon->move->name or MEAN_LOOK == user.pokemon->move->name or SPIDER_WEB == user.pokemon->move->name)
		target.trapped = true;
//	else if (BUG_BITE == user.pokemon->move->name or PLUCK == user.pokemon->move->name)
	else if (BULK_UP == user.pokemon->move->name) {
		user.pokemon->atk.boost (1);
		user.pokemon->def.boost (1);
	}
	else if (CALM_MIND == user.pokemon->move->name) {
		user.pokemon->spa.boost (1);
		user.pokemon->spd.boost (1);
	}
//	else if (CAMOUFLAGE == user.pokemon->move->name)
	else if (CAPTIVATE == user.pokemon->move->name) {
		if (user.pokemon->gender * target.pokemon->gender == -1)		// male * female == -1
			target.pokemon->spd.boost (-2);
	}
	else if (CHARGE == user.pokemon->move->name) {
		user.charge = true;
		user.pokemon->spd.boost (1);
	}
	else if (CHARM == user.pokemon->move->name or FEATHERDANCE == user.pokemon->move->name)
		target.pokemon->atk.boost (-2);
	else if (CLOSE_COMBAT == user.pokemon->move->name) {
		user.pokemon->atk.boost (-1);
		user.pokemon->def.boost (-1);
	}
	else if (COSMIC_POWER == user.pokemon->move->name or DEFEND_ORDER == user.pokemon->move->name) {
		user.pokemon->def.boost (1);
		user.pokemon->spd.boost (1);
	}
	else if (COTTON_SPORE == user.pokemon->move->name or SCARY_FACE == user.pokemon->move->name)
		target.pokemon->spe.boost (-2);
	else if (COUNTER == user.pokemon->move->name) {
			if (target.pokemon->move->physical) {
				target.pokemon->hp.stat -= user.damage * 2;
				if (target.pokemon->hp.stat < 0)
					target.pokemon->hp.stat = 0;
			}
	}
	else if (COVET == user.pokemon->move->name or THIEF == user.pokemon->move->name) {
		if (user.pokemon->item == NO_ITEM)
			user.pokemon->item = target.pokemon->item;
	}
	else if (CURSE == user.pokemon->move->name) {
		if (istype (user, GHOST) and user.pokemon->ability != MAGIC_GUARD) {
			if (!target.curse) {
				if (user.pokemon->hp.max <= 4)
					--user.pokemon->hp.stat;
				else
					user.pokemon->hp.stat -= user.pokemon->hp.max / 2;
				if (user.pokemon->hp.stat < 0)
					user.pokemon->hp.stat = 0;
				target.curse = true;
			}
		}
		else {
			user.pokemon->atk.boost (1);
			user.pokemon->def.boost (1);
			user.pokemon->spe.boost (-1);
		}
	}
	else if (DEFENSE_CURL == user.pokemon->move->name) {
		user.pokemon->def.boost (1);
		user.defense_curl = true;
	}
	else if (DEFOG == user.pokemon->move->name) {
		if (target.evasion > -6)
			-- target.evasion;
		weather.fog = false;
	}
	else if (DESTINY_BOND == user.pokemon->move->name)
		user.destiny_bond = true;
//	else if (DETECT == user.pokemon->move->name or PROTECT == user.pokemon->move->name)
//	else if (DISABLE == user.pokemon->move->name)
//	else if (DOOM_DESIRE == user.pokemon->move->name or FUTURE_SIGHT == user.pokemon->move->name)
	else if (DOUBLE_TEAM == user.pokemon->move->name or MINIMIZE == user.pokemon->move->name) {
		if (user.evasion < 6)
			++user.evasion;
	}
	else if (DRACO_METEOR == user.pokemon->move->name or LEAF_STORM == user.pokemon->move->name or OVERHEAT == user.pokemon->move->name or PSYCHO_BOOST == user.pokemon->move->name)
		user.pokemon->spa.boost (-2);
	else if (DRAGON_DANCE == user.pokemon->move->name) {
		user.pokemon->atk.boost (1);
		user.pokemon->spe.boost (1);
	}
	else if (EMBARGO == user.pokemon->move->name)
		target.embargo = 5;
	else if (ENCORE == user.pokemon->move->name) {
		if (target.encore == 0)
			target.encore = *user.pokemon->move->variable;
	}
	else if (ENDURE == user.pokemon->move->name)
		user.endure = true;
	else if (EXPLOSION == user.pokemon->move->name or SELFDESTRUCT == user.pokemon->move->name)
		user.pokemon->hp.stat = 0;
	else if (FAKE_TEARS == user.pokemon->move->name or METAL_SOUND == user.pokemon->move->name)
		target.pokemon->spd.boost (-2);
//	else if (FEINT == user.pokemon->move->name)
	else if (FLASH == user.pokemon->move->name or KINESIS == user.pokemon->move->name or MUD_SLAP == user.pokemon->move->name or SAND_ATTACK == user.pokemon->move->name or SMOKESCREEN == user.pokemon->move->name) {
		if (target.accuracy > -6)
			--target.accuracy;
	}
	else if (FLATTER == user.pokemon->move->name)
		target.pokemon->spa.boost (1);
	else if (FLING == user.pokemon->move->name)
		user.pokemon->item = NO_ITEM;
	else if (FOCUS_ENERGY == user.pokemon->move->name)
		user.focus_energy = true;
//	else if (FOCUS_PUNCH == user.pokemon->move->name)
//	else if (FOLLOW_ME == user.pokemon->move->name)
	else if (FORESIGHT == user.pokemon->move->name or ODOR_SLEUTH == user.pokemon->move->name)
		target.identified = true;
//	else if (GASTRO_ACID == user.pokemon->move->name)
	else if (GLARE == user.pokemon->move->name or STUN_SPORE == user.pokemon->move->name or THUNDER_WAVE == user.pokemon->move->name or ZAP_CANNON == user.pokemon->move->name)
		paralyze (*user.pokemon, *target.pokemon, weather);
	else if (GRAVITY == user.pokemon->move->name)
		weather.set_gravity();
	else if (GROWL == user.pokemon->move->name)
		target.pokemon->atk.boost (-1);
	else if (GROWTH == user.pokemon->move->name)
		user.pokemon->spa.boost (1);
//	else if (GRUDGE == user.pokemon->move->name)
	else if (GUARD_SWAP == user.pokemon->move->name) {
		std::swap (user.pokemon->def.stage, target.pokemon->def.stage);
		std::swap (user.pokemon->spd.stage, target.pokemon->spd.stage);
	}
	else if (HAIL == user.pokemon->move->name) {
		if (user.pokemon->item == ICY_ROCK)
			weather.set_hail (8);
		else
			weather.set_hail (5);
	}
	else if (HAMMER_ARM == user.pokemon->move->name)
		user.pokemon->spe.boost (-1);
	else if (HARDEN == user.pokemon->move->name or WITHDRAW == user.pokemon->move->name)
		user.pokemon->def.boost (1);
	else if (HAZE == user.pokemon->move->name) {
		user.pokemon->atk.stage = 0;
		user.pokemon->def.stage = 0;
		user.pokemon->spa.stage = 0;
		user.pokemon->spd.stage = 0;
		user.pokemon->spe.stage = 0;
		target.pokemon->atk.stage = 0;
		target.pokemon->def.stage = 0;
		target.pokemon->spa.stage = 0;
		target.pokemon->spd.stage = 0;
		target.pokemon->spe.stage = 0;
	}
	else if (HEAL_BELL == user.pokemon->move->name) {
		for (std::vector<Pokemon>::iterator it = user.pokemon.set.begin(); it != user.pokemon.set.end(); ++it) {
			if (it->ability != SOUNDPROOF)
				it->status = NO_STATUS;
		}
	}
	else if (HEAL_BLOCK == user.pokemon->move->name) {
		if (target.heal_block == 0)
			target.heal_block = 5;
	}
	else if (HEAL_ORDER == user.pokemon->move->name or MILK_DRINK == user.pokemon->move->name or RECOVER == user.pokemon->move->name or SLACK_OFF == user.pokemon->move->name or SOFTBOILED == user.pokemon->move->name)
		heal (*user.pokemon, 2);
//	else if (HEALING_WISH == user.pokemon->move->name)
	else if (HEART_SWAP == user.pokemon->move->name) {
		std::swap (user.pokemon->atk.stage, target.pokemon->atk.stage);
		std::swap (user.pokemon->def.stage, target.pokemon->def.stage);
		std::swap (user.pokemon->spa.stage, target.pokemon->spa.stage);
		std::swap (user.pokemon->spd.stage, target.pokemon->spd.stage);
		std::swap (user.pokemon->spe.stage, target.pokemon->spe.stage);
	}
//	else if (HI_JUMP_KICK == user.pokemon->move->name or JUMP_KICK == user.pokemon->move->name)
	else if (HOWL == user.pokemon->move->name or MEDITATE == user.pokemon->move->name or SHARPEN == user.pokemon->move->name)
		user.pokemon->atk.boost (1);
//	else if (ICE_BALL == user.pokemon->move->name or ROLLOUT == user.pokemon->move->name)
	else if (ICY_WIND == user.pokemon->move->name or MUD_SHOT == user.pokemon->move->name or ROCK_TOMB == user.pokemon->move->name or STRING_SHOT == user.pokemon->move->name)
		target.pokemon->spe.boost (-1);
	else if (IMPRISON == user.pokemon->move->name)
		user.imprison = true;
	else if (INGRAIN == user.pokemon->move->name)
		user.ingrain = true;
//	else if (KNOCK_OFF == user.pokemon->move->name)
	else if (LEECH_SEED == user.pokemon->move->name)
		target.leech_seed = true;
	else if (LEER == user.pokemon->move->name or TAIL_WHIP == user.pokemon->move->name)
		target.pokemon->def.boost (-1);
	else if (LIGHT_SCREEN == user.pokemon->move->name) {
		if (user.light_screen == 0) {
			if (user.pokemon->item == LIGHT_CLAY)
				user.light_screen = 8;
			else
				user.light_screen = 5;
		}
	}
	else if (LOCK_ON == user.pokemon->move->name or MIND_READER == user.pokemon->move->name)
		target.lock_on == true;
	else if (LUCKY_CHANT == user.pokemon->move->name) {
		if (user.lucky_chant == 0)
			user.lucky_chant = 5;
	}
//	else if (LUNAR_DANCE == user.pokemon->move->name)
//	else if (MAGIC_COAT == user.pokemon->move->name)
	else if (MAGNET_RISE == user.pokemon->move->name) {
		if (user.magnet_rise == 0)
			user.magnet_rise = 5;
	}
//	else if (ME_FIRST == user.pokemon->move->name)
	else if (MEMENTO == user.pokemon->move->name) {
		target.pokemon->atk.boost (-2);
		target.pokemon->spa.boost (-2);
		user.pokemon->hp.stat = 0;
	}
	else if (METAL_BURST == user.pokemon->move->name)
		target.pokemon->hp.stat -= user.damage * 3 / 2;
//	else if (MIMIC == user.pokemon->move->name)
//	else if (MIRACLE_EYE == user.pokemon->move->name)
	else if (MIRROR_COAT == user.pokemon->move->name) {
		if (!target.pokemon->move->physical) {
			target.pokemon->hp.stat -= user.damage * 2;
			if (target.pokemon->hp.stat < 0)
				target.pokemon->hp.stat = 0;
		}
	}
	else if (MIST == user.pokemon->move->name)
		user.mist = 5;
	else if (MOONLIGHT == user.pokemon->move->name or MORNING_SUN == user.pokemon->move->name or SYNTHESIS == user.pokemon->move->name) {
		if (weather.sun != 0)
			heal (*user.pokemon, 3, 2);
		else if (weather.hail != 0 or weather.rain != 0 or weather.sand != 0)
			heal (*user.pokemon, 4);
		else
			heal (*user.pokemon, 2);
	}
	else if (MUD_SPORT == user.pokemon->move->name)
		user.mud_sport = true;
	else if (NASTY_PLOT == user.pokemon->move->name or TAIL_GLOW == user.pokemon->move->name)
		user.pokemon->spa.boost (2);
	else if (NIGHTMARE == user.pokemon->move->name)
		target.nightmare = true;
	else if (OUTRAGE == user.pokemon->move->name or PETAL_DANCE == user.pokemon->move->name or THRASH == user.pokemon->move->name) {
		if (user.rampage == 0)
			user.rampage = *user.pokemon->move->variable;
	}
	else if (PAIN_SPLIT == user.pokemon->move->name) {
		user.pokemon->hp.stat = (user.pokemon->hp.stat + target.pokemon->hp.stat) / 2;
		target.pokemon->hp.stat = user.pokemon->hp.stat;
		if (user.pokemon->hp.stat > user.pokemon->hp.max)
			user.pokemon->hp.stat = user.pokemon->hp.max;
		if (target.pokemon->hp.stat > target.pokemon->hp.max)
			target.pokemon->hp.stat = target.pokemon->hp.max;
	}
	else if (PERISH_SONG == user.pokemon->move->name) {
		if (user.perish_song == 0)
			user.perish_song = 3;
		if (target.perish_song == 0)
			target.perish_song = 3;
	}
	else if (POISON_GAS == user.pokemon->move->name or POISONPOWDER == user.pokemon->move->name)
		poison_normal (user, target, weather);
	else if (POWER_SWAP == user.pokemon->move->name) {
		std::swap (user.pokemon->atk.stage, target.pokemon->atk.stage);
		std::swap (user.pokemon->spa.stage, target.pokemon->spa.stage);
	}
	else if (POWER_TRICK == user.pokemon->move->name) {
		if (user.power_trick)
			user.power_trick = false;
		else
			user.power_trick = true;
	}
	else if (PRESENT == user.pokemon->move->name) {
		if (*user.pokemon->move->variable == 0) {
			target.pokemon->hp.stat += 80;
			if (target.pokemon->hp.stat > target.pokemon->hp.max)
				target.pokemon->hp.stat = target.pokemon->hp.max;
		}
	}
	else if (PSYCH_UP == user.pokemon->move->name) {
		user.pokemon->atk.stage = target.pokemon->atk.stage;
		user.pokemon->def.stage = target.pokemon->def.stage;
		user.pokemon->spa.stage = target.pokemon->spa.stage;
		user.pokemon->spd.stage = target.pokemon->spd.stage;
		user.pokemon->spe.stage = target.pokemon->spe.stage;
	}
	else if (PSYCHO_SHIFT == user.pokemon->move->name) {
		if (target.pokemon->status == NO_STATUS) {
			if (user.pokemon->status == BURN)
				burn (user, target, weather);
			else if (user.pokemon->status == PARALYSIS)
				paralyze (*user.pokemon, *target.pokemon, weather);
			else if (user.pokemon->status == POISON_NORMAL)
				poison_normal (user, target, weather);
			else if (user.pokemon->status == POISON_TOXIC)
				poison_toxic (user, target, weather);
			else if (user.pokemon->status == SLEEP)
				sleep (*user.pokemon, *target.pokemon, weather);
			user.pokemon->status = NO_STATUS;
		}
	}
//	else if (RAGE == user.pokemon->move->name)
	else if (RAIN_DANCE == user.pokemon->move->name) {
		if (user.pokemon->item == DAMP_ROCK)
			weather.set_rain (8);
		else
			weather.set_rain (5);
	}
	else if (RAPID_SPIN == user.pokemon->move->name) {
		user.spikes = 0;
		user.stealth_rock = false;
		user.toxic_spikes = 0;
		user.leech_seed = false;
		user.partial_trap = false;
	}
//	else if (RAZOR_WIND == user.pokemon->move->name)
//	else if (RECYCLE == user.pokemon->move->name)
	else if (REFLECT == user.pokemon->move->name) {
		if (user.reflect == 0) {
			if (user.pokemon->item == LIGHT_CLAY)
				user.reflect = 8;
			else
				user.reflect = 5;
		}
	}
	else if (REFRESH == user.pokemon->move->name)
		user.pokemon->status = NO_STATUS;
	else if (REST == user.pokemon->move->name) {
		if (user.pokemon->hp.stat != user.pokemon->hp.max) {
			user.pokemon->hp.stat = user.pokemon->hp.max;
			user.pokemon->status = SLEEP;
			user.pokemon->sleep = 3;
		}
	}
//	else if (ROLE_PLAY == user.pokemon->move->name)
	else if (ROOST == user.pokemon->move->name) {
		user.roost = true;
		heal (*user.pokemon, 2);
	}
	else if (SAFEGUARD == user.pokemon->move->name) {
		if (user.safeguard == 0)
			user.safeguard = 5;
	}
	else if (SANDSTORM == user.pokemon->move->name) {
		if (user.pokemon->item == SMOOTH_ROCK)
			weather.set_sand (8);
		else
			weather.set_sand (5);
	}
	else if (SCREECH == user.pokemon->move->name)
		target.pokemon->def.boost (-2);
//	else if (SKETCH == user.pokemon->move->name)
//	else if (SKILL_SWAP == user.pokemon->move->name)
//	else if (SKULL_BASH == user.pokemon->move->name)
	else if (SMELLINGSALT == user.pokemon->move->name) {
		if (target.pokemon->status == PARALYSIS)
			target.pokemon->status = NO_STATUS;
	}
//	else if (SNATCH == user.pokemon->move->name)
//	else if (SOLARBEAM == user.pokemon->move->name)
	else if (SPIKES == user.pokemon->move->name and target.spikes < 3)
		++target.spikes;
//	else if (SPIT_UP == user.pokemon->move->name)
//	else if (SPITE == user.pokemon->move->name)
	else if (STEALTH_ROCK == user.pokemon->move->name)
		target.stealth_rock = true;
//	else if (STOCKPILE == user.pokemon->move->name)
	else if (STRUGGLE == user.pokemon->move->name) {
		user.pokemon->hp.stat -= user.pokemon->hp.max / 4;
		if (user.pokemon->hp.stat < 0)
			user.pokemon->hp.stat = 0;
	}
	else if (SUBSTITUTE == user.pokemon->move->name) {
		if (user.substitute == 0 and user.pokemon->hp.stat > user.pokemon->hp.max / 4) {
			user.substitute = user.pokemon->hp.max / 4;
			user.pokemon->hp.stat -= user.pokemon->hp.max / 4;
		}
	}
	else if (SUNNY_DAY == user.pokemon->move->name) {
		if (user.pokemon->item == HEAT_ROCK)
			weather.set_sun (8);
		else
			weather.set_sun (5);
	}
	else if (SUPERPOWER == user.pokemon->move->name) {
		user.pokemon->atk.boost (-1);
		user.pokemon->def.boost (-1);
	}
//	else if (SWAGGER == user.pokemon->move->name)
//	else if (SWALLOW == user.pokemon->move->name)
	else if (SWEET_SCENT == user.pokemon->move->name) {
		if (target.evasion > -6)
			--target.evasion;
	}
	else if (user.pokemon->move->is_switch()) {
		user.replacement = user.pokemon->move->name - SWITCH0;
		switchpokemon (user, target, weather);
	}
	else if (SWITCHEROO == user.pokemon->move->name or TRICK == user.pokemon->move->name)
		std::swap (user.pokemon->item, target.pokemon->item);
	else if (SWORDS_DANCE == user.pokemon->move->name)
		user.pokemon->atk.boost (2);
	else if (TAILWIND == user.pokemon->move->name) {
		if (user.tailwind == 0)
			user.tailwind = 3;
	}
	else if (TICKLE == user.pokemon->move->name) {
		target.pokemon->atk.boost (-1);
		target.pokemon->def.boost (-1);
	}
	else if (TORMENT == user.pokemon->move->name)
		target.torment = true;
	else if (TOXIC == user.pokemon->move->name)
		poison_toxic (user, target, weather);
	else if (TOXIC_SPIKES == user.pokemon->move->name) {
		if (target.toxic_spikes < 2)
			++target.toxic_spikes;
	}
//	else if (TRANSFORM == user.pokemon->move->name)
	else if (TRICK_ROOM == user.pokemon->move->name)
		weather.set_trick_room ();
//	else if (U_TURN == user.pokemon->move->name)
	else if (WAKE_UP_SLAP == user.pokemon->move->name) {
		if (target.pokemon->status == SLEEP)
			target.pokemon->status = NO_STATUS;
	}
	else if (WATER_SPORT == user.pokemon->move->name)
		user.water_sport = true;
	else if (WILL_O_WISP == user.pokemon->move->name)
		burn (user, target, weather);
	else if (WISH == user.pokemon->move->name) {
		if (user.wish == 0)
			user.wish = 2;
	}
//	else if (WORRY_SEED == user.pokemon->move->name)

	else if (BOUNCE == user.pokemon->move->name) {
		if (user.vanish == LANDED)
			user.vanish = BOUNCED;
		else
			user.vanish = LANDED;
	}
	else if (DIG == user.pokemon->move->name) {
		if (user.vanish == LANDED)
			user.vanish = DUG;
		else
			user.vanish = LANDED;
	}
	else if (DIVE == user.pokemon->move->name) {
		if (user.vanish == LANDED)
			user.vanish = DIVED;
		else
			user.vanish = LANDED;
	}
	else if (FLY == user.pokemon->move->name) {
		if (user.vanish == LANDED)
			user.vanish = FLOWN;
		else
			user.vanish = LANDED;
	}
	else if (SHADOW_FORCE == user.pokemon->move->name) {
		if (user.vanish == LANDED)
			user.vanish = SHADOW_FORCED;
		else
			user.vanish = LANDED;
	}
	
	
	else if (ACUPRESSURE == user.pokemon->move->name) {		// fix
		if (*user.pokemon->move->variable == 0)
			user.pokemon->atk.boost (2);
		else if (*user.pokemon->move->variable == 1)
			user.pokemon->def.boost (2);
		else if (*user.pokemon->move->variable == 2)
			user.pokemon->spa.boost (2);
		else if (*user.pokemon->move->variable == 3)
			user.pokemon->spd.boost (2);
		else
			user.pokemon->spe.boost (2);
	}
	else if (BIND == user.pokemon->move->name or CLAMP == user.pokemon->move->name or FIRE_SPIN == user.pokemon->move->name or MAGMA_STORM == user.pokemon->move->name or SAND_TOMB == user.pokemon->move->name or WHIRLPOOL == user.pokemon->move->name or WRAP == user.pokemon->move->name) {
		if (target.partial_trap == 0)
			target.partial_trap = *user.pokemon->move->variable;
	}
	 else if ((CONFUSE_RAY == user.pokemon->move->name or SUPERSONIC == user.pokemon->move->name or SWEET_KISS == user.pokemon->move->name or TEETER_DANCE == user.pokemon->move->name) and target.pokemon->ability != OWN_TEMPO) {
	 	if (target.confused == 0)
			target.confused = *user.pokemon->move->variable;
	}
//	else if (DARK_VOID == user.pokemon->move->name or GRASSWHISTLE == user.pokemon->move->name or HYPNOSIS == user.pokemon->move->name or LOVELY_KISS == user.pokemon->move->name or SING == user.pokemon->move->name or SLEEP_POWDER == user.pokemon->move->name or SPORE == user.pokemon->move->name)
//		sleep (*user.pokemon, *target.pokemon, weather);
	else if (ROAR == user.pokemon->move->name or WHIRLWIND == user.pokemon->move->name) {
		if ((target.pokemon->ability != SOUNDPROOF or user.pokemon->move->name != ROAR) and !target.ingrain and target.pokemon->ability != SUCTION_CUPS) {
			if (target.pokemon.set.size() > 1) {
				target.replacement = *user.pokemon->move->variable;
				switchpokemon (target, user, weather);
			}
		}
	}
	else if (TAUNT == user.pokemon->move->name) {
		if (target.taunt == 0)
			target.taunt = *user.pokemon->move->variable;
	}
	else if (UPROAR == user.pokemon->move->name) {
		user.uproar = *user.pokemon->move->variable;
		weather.set_uproar (user.uproar);
	}

	else if (user.pokemon->move->effect) {
		if (ANCIENTPOWER == user.pokemon->move->name or OMINOUS_WIND == user.pokemon->move->name or SILVER_WIND == user.pokemon->move->name) {
			user.pokemon->atk.boost (1);
			user.pokemon->def.boost (1);
			user.pokemon->spa.boost (1);
			user.pokemon->spd.boost (1);
			user.pokemon->spe.boost (1);
		}
		else if (METAL_CLAW == user.pokemon->move->name or METEOR_MASH == user.pokemon->move->name)
			user.pokemon->atk.boost (1);
		else if (STEEL_WING == user.pokemon->move->name)
			user.pokemon->def.boost (1);
		else if (CHARGE_BEAM == user.pokemon->move->name)
			user.pokemon->spa.boost (1);

		else if (AURORA_BEAM == user.pokemon->move->name)
			target.pokemon->atk.boost (-1);
		else if (CRUNCH == user.pokemon->move->name or CRUSH_CLAW == user.pokemon->move->name or IRON_TAIL == user.pokemon->move->name or ROCK_SMASH == user.pokemon->move->name)
			target.pokemon->def.boost (-1);
		else if (MIST_BALL == user.pokemon->move->name)
			target.pokemon->spa.boost (-1);
		else if (ACID == user.pokemon->move->name or BUG_BUZZ == user.pokemon->move->name or EARTH_POWER == user.pokemon->move->name or ENERGY_BALL == user.pokemon->move->name or FLASH_CANNON == user.pokemon->move->name or FOCUS_BLAST == user.pokemon->move->name or LUSTER_PURGE == user.pokemon->move->name or PSYCHIC_MOVE == user.pokemon->move->name or SHADOW_BALL == user.pokemon->move->name)
			target.pokemon->spd.boost (-1);
		else if (SEED_FLARE == user.pokemon->move->name)
			target.pokemon->spd.boost (-2);
		else if (BUBBLE == user.pokemon->move->name or BUBBLEBEAM == user.pokemon->move->name or CONSTRICT == user.pokemon->move->name)
			target.pokemon->spe.boost (-1);

		else if (AIR_SLASH == user.pokemon->move->name or ASTONISH == user.pokemon->move->name or BITE == user.pokemon->move->name or BONE_CLUB == user.pokemon->move->name or DARK_PULSE == user.pokemon->move->name or DRAGON_RUSH == user.pokemon->move->name or EXTRASENSORY == user.pokemon->move->name or FAKE_OUT == user.pokemon->move->name or HEADBUTT == user.pokemon->move->name or HYPER_FANG == user.pokemon->move->name or IRON_HEAD == user.pokemon->move->name or NEEDLE_ARM == user.pokemon->move->name or ROCK_SLIDE == user.pokemon->move->name or ROLLING_KICK == user.pokemon->move->name or SNORE == user.pokemon->move->name or STOMP == user.pokemon->move->name or TWISTER == user.pokemon->move->name or WATERFALL == user.pokemon->move->name or ZEN_HEADBUTT == user.pokemon->move->name)
			target.flinch = true;

		else if (BLAZE_KICK == user.pokemon->move->name or EMBER == user.pokemon->move->name or FIRE_BLAST == user.pokemon->move->name or FIRE_PUNCH == user.pokemon->move->name or FLAME_WHEEL == user.pokemon->move->name or FLAMETHROWER == user.pokemon->move->name or FLARE_BLITZ == user.pokemon->move->name or HEAT_WAVE == user.pokemon->move->name or LAVA_PLUME == user.pokemon->move->name or SACRED_FIRE == user.pokemon->move->name)
			burn (user, target, weather);
		else if (BLIZZARD == user.pokemon->move->name or ICE_BEAM == user.pokemon->move->name or ICE_PUNCH == user.pokemon->move->name or POWDER_SNOW == user.pokemon->move->name)
			freeze (*user.pokemon, target, weather);
		else if (BODY_SLAM == user.pokemon->move->name or DISCHARGE == user.pokemon->move->name or DRAGONBREATH == user.pokemon->move->name or FORCE_PALM == user.pokemon->move->name or LICK == user.pokemon->move->name or SECRET_POWER == user.pokemon->move->name or SPARK == user.pokemon->move->name or THUNDER == user.pokemon->move->name or THUNDERBOLT == user.pokemon->move->name or THUNDERPUNCH == user.pokemon->move->name or THUNDERSHOCK == user.pokemon->move->name or VOLT_TACKLE == user.pokemon->move->name)
			paralyze (*user.pokemon, *target.pokemon, weather);
		else if (CROSS_POISON == user.pokemon->move->name or GUNK_SHOT == user.pokemon->move->name or POISON_JAB == user.pokemon->move->name or POISON_STING == user.pokemon->move->name or POISON_TAIL == user.pokemon->move->name or SLUDGE == user.pokemon->move->name or SLUDGE_BOMB == user.pokemon->move->name or SMOG == user.pokemon->move->name)
			poison_normal (user, target, weather);
		else if (POISON_FANG == user.pokemon->move->name)
			poison_toxic (user, target, weather);
		else if (TRI_ATTACK == user.pokemon->move->name) {
			if (*user.pokemon->move->variable == 0)
				burn (user, target, weather);
			else if (*user.pokemon->move->variable == 1)
				freeze (*user.pokemon, target, weather);
			else if (*user.pokemon->move->variable == 2)
				paralyze (*user.pokemon, *target.pokemon, weather);
		}

		else if (CHATTER == user.pokemon->move->name) {
			if (user.pokemon->name == CHATOT and target.pokemon->ability != OWN_TEMPO and target.confused == 0)
				target.confused = *user.pokemon->move->variable;
		}
		else if (CONFUSION == user.pokemon->move->name or DYNAMICPUNCH == user.pokemon->move->name or PSYBEAM == user.pokemon->move->name or SIGNAL_BEAM == user.pokemon->move->name) {
			if (target.pokemon->ability != OWN_TEMPO and target.confused == 0 and false)
				target.confused = *user.pokemon->move->variable;
		}
	//	else if (CONVERSION == user.pokemon->move->name and false) {}
	//	else if (CONVERSION2 == user.pokemon->move->name and false) {}
	//	else if (DIZZY_PUNCH == user.pokemon->move->name or ROCK_CLIMB == user.pokemon->move->name or WATER_PULSE == user.pokemon->move->name) {}

		else if (FIRE_FANG == user.pokemon->move->name) {
			if (user.pokemon->move->effect != 2)
				burn (user, target, weather);
			if (user.pokemon->move->effect != 1)
				target.flinch = true;
		}
		else if (ICE_FANG == user.pokemon->move->name) {
			if (user.pokemon->move->effect != 2)
				freeze (*user.pokemon, target, weather);
			if (user.pokemon->move->effect != 1)
				target.flinch = true;
		}
		else if (THUNDER_FANG == user.pokemon->move->name) {
			if (user.pokemon->move->effect != 2)
				paralyze (*user.pokemon, *target.pokemon, weather);
			if (user.pokemon->move->effect != 1)
				target.flinch = true;
		}

		else if (MIRROR_SHOT == user.pokemon->move->name or MUD_BOMB == user.pokemon->move->name or MUDDY_WATER == user.pokemon->move->name or OCTAZOOKA == user.pokemon->move->name) {
			if (target.accuracy > -6)
				--target.accuracy;
		}
		else if (SKY_ATTACK == user.pokemon->move->name) {}
	}
//	else if (YAWN == user.pokemon->move->name) {
//		if (user.yawn == 0)
//			user.yawn = 2;
//	}

	return damage;
}

void do_damage (Team &user, Team &target, int damage) {
	target.pokemon->hp.stat -= damage;
	if (user.pokemon->item == LIFE_ORB)
		heal (*user.pokemon, -10);
	if (target.pokemon->hp.stat > 0) {
		if (target.bide != 0)
			target.bide_damage += damage;
	}
	if (ABSORB == user.pokemon->move->name or DRAIN_PUNCH == user.pokemon->move->name or GIGA_DRAIN == user.pokemon->move->name or LEECH_LIFE == user.pokemon->move->name or MEGA_DRAIN == user.pokemon->move->name) {
		if (LIQUID_OOZE == target.pokemon->ability) {
			if (damage / 2 > 0) {
				user.pokemon->hp.stat -= damage / 2;
				if (user.pokemon->hp.stat < 0)
					user.pokemon->hp.stat = 0;
			}
			else
				--user.pokemon->hp.stat;
		}
		else {
			if (damage / 2 > 0) {
				user.pokemon->hp.stat += damage / 2;
				if (user.pokemon->hp.stat > user.pokemon->hp.max)
					user.pokemon->hp.stat = user.pokemon->hp.max;
			}
			else
				++user.pokemon->hp.stat;
		}
	}
	else if (DREAM_EATER == user.pokemon->move->name) {
		if (target.pokemon->status == SLEEP) {
			user.pokemon->hp.stat += damage / 2;
			if (user.pokemon->hp.stat > user.pokemon->hp.max)
				user.pokemon->hp.stat = user.pokemon->hp.max;
		}
	}
	else if (BRAVE_BIRD == user.pokemon->move->name or DOUBLE_EDGE == user.pokemon->move->name or FLARE_BLITZ == user.pokemon->move->name or WOOD_HAMMER == user.pokemon->move->name or VOLT_TACKLE == user.pokemon->move->name)
		recoil (*user.pokemon, damage, 3);
	else if (HEAD_SMASH == user.pokemon->move->name)
		recoil (*user.pokemon, damage, 2);
	else if (SUBMISSION == user.pokemon->move->name or TAKE_DOWN == user.pokemon->move->name)
		recoil (*user.pokemon, damage, 4);
	if (user.pokemon->hp.stat < 0)
		user.pokemon->hp.stat = 0;
	if (target.pokemon->hp.stat < 0)
		target.pokemon->hp.stat = 0;
}

void lower_pp (Team &user, Pokemon const &target) {
	if (user.pokemon->move->pp != -1 and user.bide == 0) {
		if (target.ability == PRESSURE and 2 <= user.pokemon->move->pp)
			user.pokemon->move->pp -= 2;
		else
			--user.pokemon->move->pp;
	}
}


void set_move_map (std::map <std::string, moves_list> &moves_map) {
	moves_map["Absorb"] = ABSORB;
	moves_map["Acid"] = ACID;
	moves_map["Acid Armor"] = ACID_ARMOR;
	moves_map["Acupressure"] = ACUPRESSURE;
	moves_map["Aerial Ace"] = AERIAL_ACE;
	moves_map["Aeroblast"] = AEROBLAST;
	moves_map["Agility"] = AGILITY;
	moves_map["Air Cutter"] = AIR_CUTTER;
	moves_map["Air Slash"] = AIR_SLASH;
	moves_map["Amnesia"] = AMNESIA;
	moves_map["AncientPower"] = ANCIENTPOWER;
	moves_map["Ancientpower"] = ANCIENTPOWER;
	moves_map["Aqua Jet"] = AQUA_JET;
	moves_map["Aqua Ring"] = AQUA_RING;
	moves_map["Aqua Tail"] = AQUA_TAIL;
	moves_map["Arm Thrust"] = ARM_THRUST;
	moves_map["Aromatherapy"] = AROMATHERAPY;
	moves_map["Assist"] = ASSIST;
	moves_map["Assurance"] = ASSURANCE;
	moves_map["Astonish"] = ASTONISH;
	moves_map["Attack Order"] = ATTACK_ORDER;
	moves_map["Attract"] = ATTRACT;
	moves_map["Aura Sphere"] = AURA_SPHERE;
	moves_map["Aurora Beam"] = AURORA_BEAM;
	moves_map["Avalanche"] = AVALANCHE;
	moves_map["Barrage"] = BARRAGE;
	moves_map["Barrier"] = BARRIER;
	moves_map["Baton Pass"] = BATON_PASS;
	moves_map["Beat Up"] = BEAT_UP;
	moves_map["Belly Drum"] = BELLY_DRUM;
	moves_map["Bide"] = BIDE;
	moves_map["Bind"] = BIND;
	moves_map["Bite"] = BITE;
	moves_map["Blast Burn"] = BLAST_BURN;
	moves_map["Blaze Kick"] = BLAZE_KICK;
	moves_map["Blizzard"] = BLIZZARD;
	moves_map["Block"] = BLOCK;
	moves_map["Body Slam"] = BODY_SLAM;
	moves_map["Bone Club"] = BONE_CLUB;
	moves_map["Bone Rush"] = BONE_RUSH;
	moves_map["Bonemerang"] = BONEMERANG;
	moves_map["Bounce"] = BOUNCE;
	moves_map["Brave Bird"] = BRAVE_BIRD;
	moves_map["Brick Break"] = BRICK_BREAK;
	moves_map["Brine"] = BRINE;
	moves_map["Bubble"] = BUBBLE;
	moves_map["BubbleBeam"] = BUBBLEBEAM;
	moves_map["Bubblebeam"] = BUBBLEBEAM;
	moves_map["Bug Bite"] = BUG_BITE;
	moves_map["Bug Buzz"] = BUG_BUZZ;
	moves_map["Bulk Up"] = BULK_UP;
	moves_map["Bullet Punch"] = BULLET_PUNCH;
	moves_map["Bullet Seed"] = BULLET_SEED;
	moves_map["Calm Mind"] = CALM_MIND;
	moves_map["Camouflage"] = CAMOUFLAGE;
	moves_map["Captivate"] = CAPTIVATE;
	moves_map["Charge"] = CHARGE;
	moves_map["Charge Beam"] = CHARGE_BEAM;
	moves_map["Charm"] = CHARM;
	moves_map["Chatter"] = CHATTER;
	moves_map["Clamp"] = CLAMP;
	moves_map["Close Combat"] = CLOSE_COMBAT;
	moves_map["Comet Punch"] = COMET_PUNCH;
	moves_map["Confuse Ray"] = CONFUSE_RAY;
	moves_map["Confusion"] = CONFUSION;
	moves_map["Constrict"] = CONSTRICT;
	moves_map["Conversion"] = CONVERSION;
	moves_map["Conversion2"] = CONVERSION2;
	moves_map["Conversion 2"] = CONVERSION2;
	moves_map["Copycat"] = COPYCAT;
	moves_map["Cosmic Power"] = COSMIC_POWER;
	moves_map["Cotton Spore"] = COTTON_SPORE;
	moves_map["Counter"] = COUNTER;
	moves_map["Covet"] = COVET;
	moves_map["Crabhammer"] = CRABHAMMER;
	moves_map["Cross Chop"] = CROSS_CHOP;
	moves_map["Cross Poison"] = CROSS_POISON;
	moves_map["Crunch"] = CRUNCH;
	moves_map["Crush Claw"] = CRUSH_CLAW;
	moves_map["Crush Grip"] = CRUSH_GRIP;
	moves_map["Curse"] = CURSE;
	moves_map["Cut"] = CUT;
	moves_map["Dark Pulse"] = DARK_PULSE;
	moves_map["Dark Void"] = DARK_VOID;
	moves_map["Defend Order"] = DEFEND_ORDER;
	moves_map["Defense Curl"] = DEFENSE_CURL;
	moves_map["Defog"] = DEFOG;
	moves_map["Destiny Bond"] = DESTINY_BOND;
	moves_map["Detect"] = DETECT;
	moves_map["Dig"] = DIG;
	moves_map["Disable"] = DISABLE;
	moves_map["Discharge"] = DISCHARGE;
	moves_map["Dive"] = DIVE;
	moves_map["Dizzy Punch"] = DIZZY_PUNCH;
	moves_map["Doom Desire"] = DOOM_DESIRE;
	moves_map["Double Hit"] = DOUBLE_HIT;
	moves_map["Double Kick"] = DOUBLE_KICK;
	moves_map["Double Team"] = DOUBLE_TEAM;
	moves_map["Double-Edge"] = DOUBLE_EDGE;
	moves_map["Double-edge"] = DOUBLE_EDGE;
	moves_map["DoubleSlap"] = DOUBLESLAP;
	moves_map["Doubleslap"] = DOUBLESLAP;
	moves_map["Draco Meteor"] = DRACO_METEOR;
	moves_map["Dragon Claw"] = DRAGON_CLAW;
	moves_map["Dragon Dance"] = DRAGON_DANCE;
	moves_map["Dragon Pulse"] = DRAGON_PULSE;
	moves_map["Dragon Rage"] = DRAGON_RAGE;
	moves_map["Dragon Rush"] = DRAGON_RUSH;
	moves_map["DragonBreath"] = DRAGONBREATH;
	moves_map["Dragonbreath"] = DRAGONBREATH;
	moves_map["Drain Punch"] = DRAIN_PUNCH;
	moves_map["Dream Eater"] = DREAM_EATER;
	moves_map["Drill Peck"] = DRILL_PECK;
	moves_map["DynamicPunch"] = DYNAMICPUNCH;
	moves_map["Dynamicpunch"] = DYNAMICPUNCH;
	moves_map["Earth Power"] = EARTH_POWER;
	moves_map["Earthquake"] = EARTHQUAKE;
	moves_map["Egg Bomb"] = EGG_BOMB;
	moves_map["Embargo"] = EMBARGO;
	moves_map["Ember"] = EMBER;
	moves_map["Encore"] = ENCORE;
	moves_map["Endeavor"] = ENDEAVOR;
	moves_map["Endure"] = ENDURE;
	moves_map["Energy Ball"] = ENERGY_BALL;
	moves_map["Eruption"] = ERUPTION;
	moves_map["Explosion"] = EXPLOSION;
	moves_map["Extrasensory"] = EXTRASENSORY;
	moves_map["ExtremeSpeed"] = EXTREMESPEED;
	moves_map["Extremespeed"] = EXTREMESPEED;
	moves_map["Facade"] = FACADE;
	moves_map["Faint Attack"] = FAINT_ATTACK;
	moves_map["Fake Out"] = FAKE_OUT;
	moves_map["Fake Tears"] = FAKE_TEARS;
	moves_map["False Swipe"] = FALSE_SWIPE;
	moves_map["FeatherDance"] = FEATHERDANCE;
	moves_map["Featherdance"] = FEATHERDANCE;
	moves_map["Feint"] = FEINT;
	moves_map["Fire Blast"] = FIRE_BLAST;
	moves_map["Fire Fang"] = FIRE_FANG;
	moves_map["Fire Punch"] = FIRE_PUNCH;
	moves_map["Fire Spin"] = FIRE_SPIN;
	moves_map["Fissure"] = FISSURE;
	moves_map["Flail"] = FLAIL;
	moves_map["Flame Wheel"] = FLAME_WHEEL;
	moves_map["Flamethrower"] = FLAMETHROWER;
	moves_map["Flare Blitz"] = FLARE_BLITZ;
	moves_map["Flash"] = FLASH;
	moves_map["Flash Cannon"] = FLASH_CANNON;
	moves_map["Flatter"] = FLATTER;
	moves_map["Fling"] = FLING;
	moves_map["Fly"] = FLY;
	moves_map["Focus Blast"] = FOCUS_BLAST;
	moves_map["Focus Energy"] = FOCUS_ENERGY;
	moves_map["Focus Punch"] = FOCUS_PUNCH;
	moves_map["Follow Me"] = FOLLOW_ME;
	moves_map["Force Palm"] = FORCE_PALM;
	moves_map["Foresight"] = FORESIGHT;
	moves_map["Frenzy Plant"] = FRENZY_PLANT;
	moves_map["Frustration"] = FRUSTRATION;
	moves_map["Fury Attack"] = FURY_ATTACK;
	moves_map["Fury Cutter"] = FURY_CUTTER;
	moves_map["Fury Swipes"] = FURY_SWIPES;
	moves_map["Future Sight"] = FUTURE_SIGHT;
	moves_map["Gastro Acid"] = GASTRO_ACID;
	moves_map["Giga Drain"] = GIGA_DRAIN;
	moves_map["Giga Impact"] = GIGA_IMPACT;
	moves_map["Glare"] = GLARE;
	moves_map["Grass Knot"] = GRASS_KNOT;
	moves_map["GrassWhistle"] = GRASSWHISTLE;
	moves_map["Grasswhistle"] = GRASSWHISTLE;
	moves_map["Gravity"] = GRAVITY;
	moves_map["Growl"] = GROWL;
	moves_map["Growth"] = GROWTH;
	moves_map["Grudge"] = GRUDGE;
	moves_map["Guard Swap"] = GUARD_SWAP;
	moves_map["Guillotine"] = GUILLOTINE;
	moves_map["Gunk Shot"] = GUNK_SHOT;
	moves_map["Gust"] = GUST;
	moves_map["Gyro Ball"] = GYRO_BALL;
	moves_map["Hail"] = HAIL;
	moves_map["Hammer Arm"] = HAMMER_ARM;
	moves_map["Harden"] = HARDEN;
	moves_map["Haze"] = HAZE;
	moves_map["Head Smash"] = HEAD_SMASH;
	moves_map["Headbutt"] = HEADBUTT;
	moves_map["Heal Bell"] = HEAL_BELL;
	moves_map["Heal Block"] = HEAL_BLOCK;
	moves_map["Heal Order"] = HEAL_ORDER;
	moves_map["Healing Wish"] = HEALING_WISH;
	moves_map["Heart Swap"] = HEART_SWAP;
	moves_map["Heat Wave"] = HEAT_WAVE;
	moves_map["Helping Hand"] = HELPING_HAND;
	moves_map["Hi Jump Kick"] = HI_JUMP_KICK;
	moves_map["Hidden Power"] = HIDDEN_POWER;
	moves_map["Hidden Power Bug"] = HIDDEN_POWER;
	moves_map["Hidden Power Dark"] = HIDDEN_POWER;
	moves_map["Hidden Power Dragon"] = HIDDEN_POWER;
	moves_map["Hidden Power Electric"] = HIDDEN_POWER;
	moves_map["Hidden Power Fighting"] = HIDDEN_POWER;
	moves_map["Hidden Power Fire"] = HIDDEN_POWER;
	moves_map["Hidden Power Flying"] = HIDDEN_POWER;
	moves_map["Hidden Power Ghost"] = HIDDEN_POWER;
	moves_map["Hidden Power Grass"] = HIDDEN_POWER;
	moves_map["Hidden Power Ground"] = HIDDEN_POWER;
	moves_map["Hidden Power Ice"] = HIDDEN_POWER;
	moves_map["Hidden Power Poison"] = HIDDEN_POWER;
	moves_map["Hidden Power Psychic"] = HIDDEN_POWER;
	moves_map["Hidden Power Rock"] = HIDDEN_POWER;
	moves_map["Hidden Power Steel"] = HIDDEN_POWER;
	moves_map["Hidden Power Water"] = HIDDEN_POWER;
	moves_map["Horn Attack"] = HORN_ATTACK;
	moves_map["Horn Drill"] = HORN_DRILL;
	moves_map["Howl"] = HOWL;
	moves_map["Hydro Cannon"] = HYDRO_CANNON;
	moves_map["Hydro Pump"] = HYDRO_PUMP;
	moves_map["Hyper Beam"] = HYPER_BEAM;
	moves_map["Hyper Fang"] = HYPER_FANG;
	moves_map["Hyper Voice"] = HYPER_VOICE;
	moves_map["Hypnosis"] = HYPNOSIS;
	moves_map["Ice Ball"] = ICE_BALL;
	moves_map["Ice Beam"] = ICE_BEAM;
	moves_map["Ice Fang"] = ICE_FANG;
	moves_map["Ice Punch"] = ICE_PUNCH;
	moves_map["Ice Shard"] = ICE_SHARD;
	moves_map["Icicle Spear"] = ICICLE_SPEAR;
	moves_map["Icy Wind"] = ICY_WIND;
	moves_map["Imprison"] = IMPRISON;
	moves_map["Ingrain"] = INGRAIN;
	moves_map["Iron Defense"] = IRON_DEFENSE;
	moves_map["Iron Head"] = IRON_HEAD;
	moves_map["Iron Tail"] = IRON_TAIL;
	moves_map["Judgment"] = JUDGMENT;
	moves_map["Jump Kick"] = JUMP_KICK;
	moves_map["Karate Chop"] = KARATE_CHOP;
	moves_map["Kinesis"] = KINESIS;
	moves_map["Knock Off"] = KNOCK_OFF;
	moves_map["Last Resort"] = LAST_RESORT;
	moves_map["Lava Plume"] = LAVA_PLUME;
	moves_map["Leaf Blade"] = LEAF_BLADE;
	moves_map["Leaf Storm"] = LEAF_STORM;
	moves_map["Leech Life"] = LEECH_LIFE;
	moves_map["Leech Seed"] = LEECH_SEED;
	moves_map["Leer"] = LEER;
	moves_map["Lick"] = LICK;
	moves_map["Light Screen"] = LIGHT_SCREEN;
	moves_map["Lock-On"] = LOCK_ON;
	moves_map["Lock-on"] = LOCK_ON;
	moves_map["Lovely Kiss"] = LOVELY_KISS;
	moves_map["Low Kick"] = LOW_KICK;
	moves_map["Lucky Chant"] = LUCKY_CHANT;
	moves_map["Lunar Dance"] = LUNAR_DANCE;
	moves_map["Luster Purge"] = LUSTER_PURGE;
	moves_map["Mach Punch"] = MACH_PUNCH;
	moves_map["Magic Coat"] = MAGIC_COAT;
	moves_map["Magical Leaf"] = MAGICAL_LEAF;
	moves_map["Magma Storm"] = MAGMA_STORM;
	moves_map["Magnet Bomb"] = MAGNET_BOMB;
	moves_map["Magnet Rise"] = MAGNET_RISE;
	moves_map["Magnitude"] = MAGNITUDE;
	moves_map["Me First"] = ME_FIRST;
	moves_map["Mean Look"] = MEAN_LOOK;
	moves_map["Meditate"] = MEDITATE;
	moves_map["Mega Drain"] = MEGA_DRAIN;
	moves_map["Mega Kick"] = MEGA_KICK;
	moves_map["Mega Punch"] = MEGA_PUNCH;
	moves_map["Megahorn"] = MEGAHORN;
	moves_map["Memento"] = MEMENTO;
	moves_map["Metal Burst"] = METAL_BURST;
	moves_map["Metal Claw"] = METAL_CLAW;
	moves_map["Metal Sound"] = METAL_SOUND;
	moves_map["Meteor Mash"] = METEOR_MASH;
	moves_map["Metronome"] = METRONOME_MOVE;
	moves_map["Milk Drink"] = MILK_DRINK;
	moves_map["Mimic"] = MIMIC;
	moves_map["Mind Reader"] = MIND_READER;
	moves_map["Minimize"] = MINIMIZE;
	moves_map["Miracle Eye"] = MIRACLE_EYE;
	moves_map["Mirror Coat"] = MIRROR_COAT;
	moves_map["Mirror Move"] = MIRROR_MOVE;
	moves_map["Mirror Shot"] = MIRROR_SHOT;
	moves_map["Mist"] = MIST;
	moves_map["Mist Ball"] = MIST_BALL;
	moves_map["Moonlight"] = MOONLIGHT;
	moves_map["Morning Sun"] = MORNING_SUN;
	moves_map["Mud Bomb"] = MUD_BOMB;
	moves_map["Mud Shot"] = MUD_SHOT;
	moves_map["Mud Sport"] = MUD_SPORT;
	moves_map["Mud-Slap"] = MUD_SLAP;
	moves_map["Mud-slap"] = MUD_SLAP;
	moves_map["Muddy Water"] = MUDDY_WATER;
	moves_map["Nasty Plot"] = NASTY_PLOT;
	moves_map["Natural Gift"] = NATURAL_GIFT;
	moves_map["Nature Power"] = NATURE_POWER;
	moves_map["Needle Arm"] = NEEDLE_ARM;
	moves_map["Night Shade"] = NIGHT_SHADE;
	moves_map["Night Slash"] = NIGHT_SLASH;
	moves_map["Nightmare"] = NIGHTMARE;
	moves_map["Octazooka"] = OCTAZOOKA;
	moves_map["Odor Sleuth"] = ODOR_SLEUTH;
	moves_map["Ominous Wind"] = OMINOUS_WIND;
	moves_map["Outrage"] = OUTRAGE;
	moves_map["Overheat"] = OVERHEAT;
	moves_map["Pain Split"] = PAIN_SPLIT;
	moves_map["Pay Day"] = PAY_DAY;
	moves_map["Payback"] = PAYBACK;
	moves_map["Peck"] = PECK;
	moves_map["Perish Song"] = PERISH_SONG;
	moves_map["Petal Dance"] = PETAL_DANCE;
	moves_map["Pin Missile"] = PIN_MISSILE;
	moves_map["Pluck"] = PLUCK;
	moves_map["Poison Fang"] = POISON_FANG;
	moves_map["Poison Gas"] = POISON_GAS;
	moves_map["Poison Jab"] = POISON_JAB;
	moves_map["Poison Sting"] = POISON_STING;
	moves_map["Poison Tail"] = POISON_TAIL;
	moves_map["PoisonPowder"] = POISONPOWDER;
	moves_map["Poisonpowder"] = POISONPOWDER;
	moves_map["Pound"] = POUND;
	moves_map["Powder Snow"] = POWDER_SNOW;
	moves_map["Power Gem"] = POWER_GEM;
	moves_map["Power Swap"] = POWER_SWAP;
	moves_map["Power Trick"] = POWER_TRICK;
	moves_map["Power Whip"] = POWER_WHIP;
	moves_map["Present"] = PRESENT;
	moves_map["Protect"] = PROTECT;
	moves_map["Psybeam"] = PSYBEAM;
	moves_map["Psych Up"] = PSYCH_UP;
	moves_map["Psychic"] = PSYCHIC_MOVE;
	moves_map["Psycho Boost"] = PSYCHO_BOOST;
	moves_map["Psycho Cut"] = PSYCHO_CUT;
	moves_map["Psycho Shift"] = PSYCHO_SHIFT;
	moves_map["Psywave"] = PSYWAVE;
	moves_map["Punishment"] = PUNISHMENT;
	moves_map["Pursuit"] = PURSUIT;
	moves_map["Quick Attack"] = QUICK_ATTACK;
	moves_map["Rage"] = RAGE;
	moves_map["Rain Dance"] = RAIN_DANCE;
	moves_map["Rapid Spin"] = RAPID_SPIN;
	moves_map["Razor Leaf"] = RAZOR_LEAF;
	moves_map["Razor Wind"] = RAZOR_WIND;
	moves_map["Recover"] = RECOVER;
	moves_map["Recycle"] = RECYCLE;
	moves_map["Reflect"] = REFLECT;
	moves_map["Refresh"] = REFRESH;
	moves_map["Rest"] = REST;
	moves_map["Return"] = RETURN;
	moves_map["Revenge"] = REVENGE;
	moves_map["Reversal"] = REVERSAL;
	moves_map["Roar"] = ROAR;
	moves_map["Roar Of Time"] = ROAR_OF_TIME;
	moves_map["Rock Blast"] = ROCK_BLAST;
	moves_map["Rock Climb"] = ROCK_CLIMB;
	moves_map["Rock Polish"] = ROCK_POLISH;
	moves_map["Rock Slide"] = ROCK_SLIDE;
	moves_map["Rock Smash"] = ROCK_SMASH;
	moves_map["Rock Throw"] = ROCK_THROW;
	moves_map["Rock Tomb"] = ROCK_TOMB;
	moves_map["Rock Wrecker"] = ROCK_WRECKER;
	moves_map["Role Play"] = ROLE_PLAY;
	moves_map["Rolling Kick"] = ROLLING_KICK;
	moves_map["Rollout"] = ROLLOUT;
	moves_map["Roost"] = ROOST;
	moves_map["Sacred Fire"] = SACRED_FIRE;
	moves_map["Safeguard"] = SAFEGUARD;
	moves_map["Sand Tomb"] = SAND_TOMB;
	moves_map["Sand-Attack"] = SAND_ATTACK;
	moves_map["Sand-attack"] = SAND_ATTACK;
	moves_map["Sandstorm"] = SANDSTORM;
	moves_map["Scary Face"] = SCARY_FACE;
	moves_map["Scratch"] = SCRATCH;
	moves_map["Screech"] = SCREECH;
	moves_map["Secret Power"] = SECRET_POWER;
	moves_map["Seed Bomb"] = SEED_BOMB;
	moves_map["Seed Flare"] = SEED_FLARE;
	moves_map["Seismic Toss"] = SEISMIC_TOSS;
	moves_map["Selfdestruct"] = SELFDESTRUCT;
	moves_map["Shadow Ball"] = SHADOW_BALL;
	moves_map["Shadow Claw"] = SHADOW_CLAW;
	moves_map["Shadow Force"] = SHADOW_FORCE;
	moves_map["Shadow Punch"] = SHADOW_PUNCH;
	moves_map["Shadow Sneak"] = SHADOW_SNEAK;
	moves_map["Sharpen"] = SHARPEN;
	moves_map["Sheer Cold"] = SHEER_COLD;
	moves_map["Shock Wave"] = SHOCK_WAVE;
	moves_map["Signal Beam"] = SIGNAL_BEAM;
	moves_map["Silver Wind"] = SILVER_WIND;
	moves_map["Sing"] = SING;
	moves_map["Sketch"] = SKETCH;
	moves_map["Skill Swap"] = SKILL_SWAP;
	moves_map["Skull Bash"] = SKULL_BASH;
	moves_map["Sky Attack"] = SKY_ATTACK;
	moves_map["Sky Uppercut"] = SKY_UPPERCUT;
	moves_map["Slack Off"] = SLACK_OFF;
	moves_map["Slam"] = SLAM;
	moves_map["Slash"] = SLASH;
	moves_map["Sleep Powder"] = SLEEP_POWDER;
	moves_map["Sleep Talk"] = SLEEP_TALK;
	moves_map["Sludge"] = SLUDGE;
	moves_map["Sludge Bomb"] = SLUDGE_BOMB;
	moves_map["SmellingSalt"] = SMELLINGSALT;
	moves_map["Smellingsalt"] = SMELLINGSALT;
	moves_map["Smog"] = SMOG;
	moves_map["SmokeScreen"] = SMOKESCREEN;
	moves_map["Smokescreen"] = SMOKESCREEN;
	moves_map["Snatch"] = SNATCH;
	moves_map["Snore"] = SNORE;
	moves_map["Softboiled"] = SOFTBOILED;
	moves_map["SolarBeam"] = SOLARBEAM;
	moves_map["Solarbeam"] = SOLARBEAM;
	moves_map["SonicBoom"] = SONICBOOM;
	moves_map["Sonicboom"] = SONICBOOM;
	moves_map["Spacial Rend"] = SPACIAL_REND;
	moves_map["Spark"] = SPARK;
	moves_map["Spider Web"] = SPIDER_WEB;
	moves_map["Spike Cannon"] = SPIKE_CANNON;
	moves_map["Spikes"] = SPIKES;
	moves_map["Spit Up"] = SPIT_UP;
	moves_map["Spite"] = SPITE;
	moves_map["Splash"] = SPLASH;
	moves_map["Spore"] = SPORE;
	moves_map["Stealth Rock"] = STEALTH_ROCK;
	moves_map["Steel Wing"] = STEEL_WING;
	moves_map["Stockpile"] = STOCKPILE;
	moves_map["Stomp"] = STOMP;
	moves_map["Stone Edge"] = STONE_EDGE;
	moves_map["Strength"] = STRENGTH;
	moves_map["String Shot"] = STRING_SHOT;
	moves_map["Struggle"] = STRUGGLE;
	moves_map["Stun Spore"] = STUN_SPORE;
	moves_map["Submission"] = SUBMISSION;
	moves_map["Substitute"] = SUBSTITUTE;
	moves_map["Sucker Punch"] = SUCKER_PUNCH;
	moves_map["Sunny Day"] = SUNNY_DAY;
	moves_map["Super Fang"] = SUPER_FANG;
	moves_map["Superpower"] = SUPERPOWER;
	moves_map["Supersonic"] = SUPERSONIC;
	moves_map["Surf"] = SURF;
	moves_map["Swagger"] = SWAGGER;
	moves_map["Swallow"] = SWALLOW;
	moves_map["Sweet Kiss"] = SWEET_KISS;
	moves_map["Sweet Scent"] = SWEET_SCENT;
	moves_map["Swift"] = SWIFT;
	moves_map["Switcheroo"] = SWITCHEROO;
	moves_map["Swords Dance"] = SWORDS_DANCE;
	moves_map["Synthesis"] = SYNTHESIS;
	moves_map["Tackle"] = TACKLE;
	moves_map["Tail Glow"] = TAIL_GLOW;
	moves_map["Tail Whip"] = TAIL_WHIP;
	moves_map["Tailwind"] = TAILWIND;
	moves_map["Take Down"] = TAKE_DOWN;
	moves_map["Taunt"] = TAUNT;
	moves_map["Teeter Dance"] = TEETER_DANCE;
	moves_map["Teleport"] = TELEPORT;
	moves_map["Thief"] = THIEF;
	moves_map["Thrash"] = THRASH;
	moves_map["Thunder"] = THUNDER;
	moves_map["Thunder Fang"] = THUNDER_FANG;
	moves_map["Thunder Wave"] = THUNDER_WAVE;
	moves_map["Thunderbolt"] = THUNDERBOLT;
	moves_map["ThunderPunch"] = THUNDERPUNCH;
	moves_map["Thunderpunch"] = THUNDERPUNCH;
	moves_map["ThunderShock"] = THUNDERSHOCK;
	moves_map["Thundershock"] = THUNDERSHOCK;
	moves_map["Tickle"] = TICKLE;
	moves_map["Torment"] = TORMENT;
	moves_map["Toxic"] = TOXIC;
	moves_map["Toxic Spikes"] = TOXIC_SPIKES;
	moves_map["Transform"] = TRANSFORM;
	moves_map["Tri Attack"] = TRI_ATTACK;
	moves_map["Trick"] = TRICK;
	moves_map["Trick Room"] = TRICK_ROOM;
	moves_map["Triple Kick"] = TRIPLE_KICK;
	moves_map["Trump Card"] = TRUMP_CARD;
	moves_map["Twineedle"] = TWINEEDLE;
	moves_map["Twister"] = TWISTER;
	moves_map["U-turn"] = U_TURN;
	moves_map["Uproar"] = UPROAR;
	moves_map["Vacuum Wave"] = VACUUM_WAVE;
	moves_map["ViceGrip"] = VICEGRIP;
	moves_map["Vicegrip"] = VICEGRIP;
	moves_map["Vine Whip"] = VINE_WHIP;
	moves_map["Vital Throw"] = VITAL_THROW;
	moves_map["Volt Tackle"] = VOLT_TACKLE;
	moves_map["Wake-Up Slap"] = WAKE_UP_SLAP;
	moves_map["Wake-up Slap"] = WAKE_UP_SLAP;
	moves_map["Water Gun"] = WATER_GUN;
	moves_map["Water Pulse"] = WATER_PULSE;
	moves_map["Water Sport"] = WATER_SPORT;
	moves_map["Water Spout"] = WATER_SPOUT;
	moves_map["Waterfall"] = WATERFALL;
	moves_map["Weather Ball"] = WEATHER_BALL;
	moves_map["Whirlpool"] = WHIRLPOOL;
	moves_map["Whirlwind"] = WHIRLWIND;
	moves_map["Will-O-Wisp"] = WILL_O_WISP;
	moves_map["Will-o-Wisp"] = WILL_O_WISP;
	moves_map["Will-o-wisp"] = WILL_O_WISP;
	moves_map["Wing Attack"] = WING_ATTACK;
	moves_map["Wish"] = WISH;
	moves_map["Withdraw"] = WITHDRAW;
	moves_map["Wood Hammer"] = WOOD_HAMMER;
	moves_map["Worry Seed"] = WORRY_SEED;
	moves_map["Wrap"] = WRAP;
	moves_map["Wring Out"] = WRING_OUT;
	moves_map["X-Scissor"] = X_SCISSOR;
	moves_map["X-scissor"] = X_SCISSOR;
	moves_map["Yawn"] = YAWN;
	moves_map["Zap Cannon"] = ZAP_CANNON;
	moves_map["Zen Headbutt"] = ZEN_HEADBUTT;
	moves_map["End Move"] = END_MOVE;
}

}
