// Flags for the active Pokemon
// Copyright (C) 2013 David Stone
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

#include "active_pokemon.hpp"

#include "pokemon.hpp"

#include "../ability.hpp"
#include "../damage.hpp"
#include "../rational.hpp"

#include "../move/move.hpp"
#include "../move/moves.hpp"

namespace technicalmachine {

PokemonCollection const & ActivePokemon::all_pokemon() const {
	return m_all_pokemon;
}
PokemonCollection & ActivePokemon::all_pokemon() {
	return m_all_pokemon;
}

ActivePokemon::operator Pokemon const & () const {
	return all_pokemon()();
}

ActivePokemon::operator Pokemon & () {
	return all_pokemon()();
}

ActivePokemon::operator Species() const {
	return static_cast<Species>(static_cast<Pokemon const &>(*this));
}

MoveCollection const & ActivePokemon::all_moves() const {
	auto const & self = static_cast<Pokemon const &>(*this);
	return self.move;
}

MoveCollection & ActivePokemon::all_moves() {
	auto & self = static_cast<Pokemon &>(*this);
	return self.move;
}

bool ActivePokemon::was_used_last(Moves const move_name) const {
	return last_used_move.was_used_last(*all_moves().index(move_name));
}


void ActivePokemon::reset_end_of_turn() {
	damage_done_to_active = 0;
	enduring = false;
	flinched_this_turn = false;
	has_moved = false;
	me_first = false;
	loaf = !loaf;
	protecting = false;
}

void ActivePokemon::reset_switch() {
	// TODO: remove some of these when the foe switches, too
	if (!is_baton_passing()) {
		aqua_ring = false;
		confusion.reset();
		cursed = false;
		embargo.reset();
		focusing_energy = false;
		gastro_acid = false;
		ingrain_active = false;
		leech_seed = false;
		lock_on = false;
		magnet_rise.reset();
		perish_song.reset();
		power_trick = false;
		stage.reset();
		active_substitute.destroy();
	}
	attracted = false;
	charged = false;
	used_defense_curl = false;
	destiny_bond = false;
	m_disable.reset();
	encore.reset();
	flash_fire = false;
	flinched_this_turn = false;
	fully_trapped = false;
	heal_block.reset();
	identified = false;
	used_imprison = false;
	last_used_move.reset();
	// Do I set to true or false? true makes it wrong when a fainted Pokemon is
	// replaced; false makes it wrong otherwise
	loaf = false;
	minimize = false;
	me_first = false;
	mud_sport = false;
	nightmares = false;
	partial_trap.reset();
	pass = false;
	rampage.reset();
	roosting = false;
	slow_start.reset();
	stockpile.reset();
	is_tormented = false;
	u_turning = false;
	water_sport = false;
	bide.reset();
	damage_done_to_active = 0;
	m_taunt.reset();
	toxic.reset();
	uproar.reset();
	// Whirlwind can hit Flying Pokemon, so it's possible to switch while
	// vanished. Therefore, we need to reset it.
	vanish.reset();
	yawn.reset();
	m_will_be_replaced = false;
}

void ActivePokemon::reset_between_turns() {
	ch = false;
	fully_paralyzed = false;
	confusion.end_of_turn_reset();
	miss = false;
}

void ActivePokemon::clear_field() {
	clear_leech_seed();
	partial_trap.reset();
}

void ActivePokemon::update_before_move() {
	destiny_bond = false;
	lock_on = false;
	has_moved = true;
}

void ActivePokemon::clear_leech_seed() {
	leech_seed = false;
}

bool ActivePokemon::aqua_ring_is_active() const {
	return aqua_ring;
}

void ActivePokemon::activate_aqua_ring() {
	aqua_ring = true;
}

void ActivePokemon::attract() {
	attracted = true;
}

void ActivePokemon::awaken(bool const value) {
	awakening = value;
}

Rational ActivePokemon::awaken_probability() const {
	auto const & status = get_status(*this);
	auto const & ability = get_ability(*this);
	return status.awaken_probability(ability, awakening);
}

bool ActivePokemon::is_baton_passing() const {
	return pass;
}

void ActivePokemon::baton_pass() {
	pass = true;
}

bool ActivePokemon::cannot_be_koed() const {
	return enduring;
}

bool ActivePokemon::charge_boosted() const {
	return charged and Type(move(), *this) == Type::Electric;
}

void ActivePokemon::charge() {
	charged = true;
}

bool ActivePokemon::is_confused() const {
	return confusion.is_active();
}

void ActivePokemon::confuse() {
	if (!get_ability(*this).blocks_confusion())
		confusion.activate();
}

void ActivePokemon::handle_confusion() {
	confusion.do_turn(*this);
}

bool ActivePokemon::critical_hit() const {
	return ch;
}

void ActivePokemon::set_critical_hit(bool const value) {
	ch = value;
}

void ActivePokemon::curse() {
	cursed = true;
}

bool ActivePokemon::is_cursed() const {
	return cursed;
}

void ActivePokemon::defense_curl() {
	used_defense_curl = true;
}

void ActivePokemon::use_destiny_bond() {
	destiny_bond = true;
}

bool ActivePokemon::defense_curled() const {
	return used_defense_curl;
}

bool ActivePokemon::is_disabled(Moves const move_name) const {
	return m_disable.move_is_disabled(*all_moves().index(move_name));
}

void ActivePokemon::disable() {
	m_disable.activate(all_moves().index());
}

void ActivePokemon::advance_disable() {
	m_disable.advance_one_turn();
}

void ActivePokemon::activate_embargo() {
	embargo.activate();
}

void ActivePokemon::decrement_embargo() {
	embargo.decrement();
}

bool ActivePokemon::is_encored() const {
	return encore.is_active();
}

void ActivePokemon::activate_encore() {
	encore.activate();
}

void ActivePokemon::increment_encore() {
	encore.increment();
}

void ActivePokemon::endure() {
	enduring = true;
}

bool ActivePokemon::is_fainted() const {
	return m_will_be_replaced;
}

void ActivePokemon::faint() {
	get_stat(*this, StatNames::HP).stat = 0;
	m_will_be_replaced = true;
}

bool ActivePokemon::flash_fire_is_active() const {
	return flash_fire;
}

void ActivePokemon::activate_flash_fire() {
	flash_fire = true;
}

bool ActivePokemon::flinched() const {
	return flinched_this_turn;
}

void ActivePokemon::flinch() {
	flinched_this_turn = true;
}

void ActivePokemon::focus_energy() {
	focusing_energy = true;
}

void ActivePokemon::fully_trap() {
	fully_trapped = true;
}

void ActivePokemon::identify() {
	identified = true;
}

bool ActivePokemon::imprisoned() const {
	return used_imprison;
}

void ActivePokemon::imprison() {
	used_imprison = true;
}

PokemonCollection::index_type ActivePokemon::index() const {
	return all_pokemon().index();
}

bool ActivePokemon::ingrained() const {
	return ingrain_active;
}

void ActivePokemon::ingrain() {
	ingrain_active = true;
}

bool ActivePokemon::heal_block_is_active() const {
	return heal_block.is_active();
}

void ActivePokemon::activate_heal_block() {
	heal_block.activate();
}

void ActivePokemon::decrement_heal_block() {
	heal_block.decrement();
}

bool ActivePokemon::is_fully_paralyzed() const {
	return fully_paralyzed;
}

bool ActivePokemon::leech_seeded() const {
	return leech_seed;
}

void ActivePokemon::hit_with_leech_seed() {
	leech_seed = true;
}

bool ActivePokemon::is_loafing() const {
	return get_ability(*this).is_loafing(loaf);
}

void ActivePokemon::decrement_lock_in() {
	// Cannot be locked into Rampage and Uproar at the same time
	if (rampage.decrement())
		confuse();
	else
		uproar.increment();
}

bool ActivePokemon::locked_on() const {
	return lock_on;
}

void ActivePokemon::lock_on_to() {
	lock_on = true;
}

namespace {

bool is_regular(Moves const move) {
	return move != Moves::Struggle and !is_switch(move);
}

}	// namespace

void ActivePokemon::lower_pp(Ability const & target) {
	if (is_regular(move()) and !is_locked_in_to_bide())
		regular_move().pp.decrement(target);
}

bool ActivePokemon::magnet_rise_is_active() const {
	return magnet_rise.is_active();
}

void ActivePokemon::activate_magnet_rise() {
	magnet_rise.activate();
}

void ActivePokemon::decrement_magnet_rise() {
	magnet_rise.decrement();
}

bool ActivePokemon::me_first_is_active() const {
	return me_first;
}

unsigned ActivePokemon::fury_cutter_power() const {
	return last_used_move.fury_cutter_power();
}
unsigned ActivePokemon::momentum_move_power() const {
	return last_used_move.momentum_move_power();
}
unsigned ActivePokemon::triple_kick_power() const {
	return last_used_move.triple_kick_power();
}

Rational ActivePokemon::metronome_boost() const {
	return last_used_move.metronome_boost();
}

bool ActivePokemon::minimized() const {
	return minimize;
}

bool ActivePokemon::missed() const {
	return miss;
}

void ActivePokemon::set_miss(bool const value) {
	miss = value;
}

void ActivePokemon::set_moved(bool const value) {
	has_moved = value;
}

bool ActivePokemon::moved() const {
	return has_moved;
}

bool ActivePokemon::moved_since_switch() const {
	return last_used_move.has_moved();
}

void ActivePokemon::activate_mud_sport() {
	mud_sport = true;
}

bool ActivePokemon::nightmare() const {
	return nightmares;
}

void ActivePokemon::give_nightmares() {
	nightmares = true;
}

void ActivePokemon::partially_trap(bool const extended) {
	partial_trap.activate(extended);
}

void ActivePokemon::partial_trap_damage() {
	partial_trap.damage(*this);
}

void ActivePokemon::activate_perish_song() {
	perish_song.activate();
}

void ActivePokemon::perish_song_turn() {
	bool const faints_this_turn = perish_song.next_turn();
	if (faints_this_turn) {
		faint();
	}
}

bool ActivePokemon::can_be_phazed() const {
	return !ingrained() and !get_ability(*this).blocks_phazing() and all_pokemon().size() > 1;
}

bool ActivePokemon::power_trick_is_active() const {
	return power_trick;
}

void ActivePokemon::activate_power_trick() {
	power_trick = !power_trick;
}

void ActivePokemon::protect() {
	protecting = true;
}

void ActivePokemon::break_protect() {
	protecting = false;
}

void ActivePokemon::activate_rampage() {
	rampage.activate();
}

bool ActivePokemon::recharging() const {
	return recharge_lock_in;
}

bool ActivePokemon::recharge() {
	bool const return_value = recharging();
	recharge_lock_in = false;
	return return_value;
}

void ActivePokemon::use_recharge_move() {
	recharge_lock_in = true;
}

bool ActivePokemon::is_roosting() const {
	return roosting;
}

void ActivePokemon::roost() {
	roosting = true;
}

bool ActivePokemon::shed_skin_activated() const {
	return shedding_skin;
}

void ActivePokemon::shed_skin(bool const value) {
	shedding_skin = value;
}

Rational ActivePokemon::shed_skin_probability() const {
	auto const & status = get_status(*this);
	if (!get_ability(*this).can_clear_status(status)) {
		return Rational(shed_skin_activated() ? 0 : 1, 1);
	}
	Rational const result(3, 10);
	return shed_skin_activated() ? result : complement(result);
}

void ActivePokemon::increase_sleep_counter() {
	auto & status = get_status(*this);
	auto const & ability = get_ability(*this);
	status.increase_sleep_counter(ability, awakening);
}

bool ActivePokemon::slow_start_is_active() const {
	return slow_start.is_active();
}

bool ActivePokemon::sport_is_active(Move const & foe_move) const {
	Type const move_type(foe_move, *this);
	if (move_type == Type::Electric) {
		return mud_sport;
	}
	else if (move_type == Type::Fire) {
		return water_sport;
	}
	else {
		return false;
	}
}

Stage::value_type ActivePokemon::current_stage(StatNames const stat_index) const {
	return stage.m_stages[stat_index];
}

void ActivePokemon::stat_boost(StatNames const stat_index, Stage::boost_type const number_of_stages) {
	stage.boost(stat_index, number_of_stages);
}

void ActivePokemon::stat_boost_physical(Stage::boost_type const number_of_stages) {
	stage.boost_physical(number_of_stages);
}

void ActivePokemon::stat_boost_special(Stage::boost_type const number_of_stages) {
	stage.boost_special(number_of_stages);
}

void ActivePokemon::stat_boost_regular(Stage::boost_type const number_of_stages) {
	stage.boost_regular(number_of_stages);
}

void ActivePokemon::stat_boost_defensive(Stage::boost_type const number_of_stages) {
	stage.boost_defensive(number_of_stages);
}

void ActivePokemon::stat_boost_offensive(Stage::boost_type const number_of_stages) {
	stage.boost_offensive(number_of_stages);
}

void ActivePokemon::reset_stats() {
	stage.reset();
}

void ActivePokemon::copy_stat_boosts(ActivePokemon const & other) {
	stage = other.stage;
}

void ActivePokemon::swap_defensive_stages(ActivePokemon & lhs, ActivePokemon & rhs) {
	Stage::swap_defensive(lhs.stage, rhs.stage);
}

void ActivePokemon::swap_offensive_stages(ActivePokemon & lhs, ActivePokemon & rhs) {
	Stage::swap_offensive(lhs.stage, rhs.stage);
}

void ActivePokemon::swap_stat_boosts(ActivePokemon & lhs, ActivePokemon & rhs) {
	using std::swap;
	swap(lhs.stage, rhs.stage);
}

bounded_integer::native_integer<0, Stockpile::max * 100> ActivePokemon::spit_up_power() const {
	return stockpile.spit_up_power();
}

void ActivePokemon::increment_stockpile() {
	bool const increased = stockpile.increment();
	if (increased)
		stat_boost_defensive(1_bi);
}

bounded_integer::native_integer<0, Stockpile::max> ActivePokemon::release_stockpile() {
	auto const stages = stockpile.release();
	stat_boost_defensive(-stages);
	return stages;
}

bool ActivePokemon::is_switching_to_self () const {
	return all_pokemon().is_switching_to_self();
}

bool ActivePokemon::is_switching_to_self(Moves const switch_move) const {
	return all_pokemon().is_switching_to_self(switch_move);
}

bool ActivePokemon::has_switched() const {
	return moved() and is_switch(move());
}

bool ActivePokemon::switch_decision_required() const {
	return pass or u_turning or will_be_replaced();
}

void switch_pokemon(ActivePokemon & pokemon) {
	if (get_ability(pokemon).clears_status_on_switch()) {
		get_status(pokemon).clear();
	}
	pokemon.all_pokemon().set_index(pokemon.all_pokemon().replacement());
}

bool ActivePokemon::trapped() const {
	return fully_trapped or ingrained() or partial_trap;
}

bool ActivePokemon::tormented() const {
	return is_tormented;
}

void ActivePokemon::torment() {
	is_tormented = true;
}

void ActivePokemon::taunt() {
	m_taunt.activate();
}

bool ActivePokemon::is_taunted() const {
	return m_taunt.is_active();
}

void ActivePokemon::increment_taunt() {
	m_taunt.increment();
}

Rational ActivePokemon::toxic_ratio() const {
	return toxic.ratio_drained();
}

void ActivePokemon::increment_toxic() {
	toxic.increment();
}

void ActivePokemon::u_turn() {
	u_turning = true;
}

void ActivePokemon::use_uproar() {
	uproar.increment();
}

bool ActivePokemon::vanish_doubles_power(Moves const move_name) const {
	return vanish.doubles_move_power(move_name);
}

void ActivePokemon::activate_water_sport() {
	water_sport = true;
}

bool ActivePokemon::decrement_yawn() {
	return yawn.decrement();
}

void ActivePokemon::hit_with_yawn() {
	yawn.activate();
}

bool ActivePokemon::bounce() {
	return vanish.bounce();
}
bool ActivePokemon::dig() {
	return vanish.dig();
}
bool ActivePokemon::dive() {
	return vanish.dive();
}
bool ActivePokemon::fly() {
	return vanish.fly();
}
bool ActivePokemon::shadow_force() {
	return vanish.shadow_force();
}

void ActivePokemon::use_bide(Pokemon & target) {
	if (!bide.is_active()) {
		bide.activate();
	}
	else {
		unsigned const bide_damage = bide.decrement();
		if (bide_damage != 0)
			apply_damage(target, bide_damage * 2);
	}
}

namespace {

bool can_use_substitute(Pokemon const & pokemon) {
	auto const & hp = get_stat(pokemon, StatNames::HP);
	return hp.stat > hp.max / 4;
}

}	// namespace

void ActivePokemon::use_substitute() {
	if (!can_use_substitute(*this))
		return;
	auto const & max_hp = get_stat(*this, StatNames::HP).max;
	bool const created = active_substitute.create(static_cast<unsigned>(max_hp));
	if (created) {
		indirect_damage(static_cast<unsigned>(max_hp) / 4);
	}
}

bool ActivePokemon::is_locked_in_to_bide() const {
	return bide.is_active();
}

unsigned ActivePokemon::damaged() const {
	return damage_done_to_active;
}

Rational ActivePokemon::random_damage_multiplier() const {
	return random_damage();
}

void ActivePokemon::direct_damage(unsigned damage) {
	damage = apply_damage(*this, damage);
	damage_done_to_active = damage;
	bide.add_damage(damage);
}

void ActivePokemon::indirect_damage(unsigned const damage) {
	apply_damage(*this, damage);
}

void ActivePokemon::register_damage(unsigned const damage) {
	damage_done_to_active = damage;
}

void ActivePokemon::increment_move_use_counter() {
	last_used_move.increment(all_moves().index(), all_moves().number_of_regular_moves());
}

void ActivePokemon::update_chance_to_hit(ActivePokemon const & target, Weather const & weather, bool target_moved) {
	cached_chance_to_hit.update(*this, target, weather, target_moved);
}

Rational ActivePokemon::accuracy_probability() const {
	return miss ? complement(cached_chance_to_hit()) : cached_chance_to_hit();
}

bool ActivePokemon::will_be_replaced() const {
	return m_will_be_replaced;
}

void ActivePokemon::normalize_hp(bool fainted) {
	auto & hp = get_stat(*this, StatNames::HP).stat;
	if (fainted) {
		faint();
	}
	else if (hp == 0) {
		hp = 1;
	}
}

ActivePokemon::hash_type ActivePokemon::hash() const {
	hash_type current_hash = 0;
	current_hash *= m_all_pokemon.max_hash();
	current_hash += m_all_pokemon.hash();
	current_hash *= active_substitute.max_hash();
	current_hash += active_substitute.hash();
	current_hash *= bide.max_hash();
	current_hash += bide.hash();
	current_hash *= confusion.max_hash();
	current_hash += confusion.hash();
	current_hash *= m_disable.max_hash();
	current_hash += m_disable.hash();
	current_hash *= embargo.max_hash();
	current_hash += embargo.hash();
	current_hash *= encore.max_hash();
	current_hash += encore.hash();
	current_hash *= heal_block.max_hash();
	current_hash += heal_block.hash();
	current_hash *= last_used_move.max_hash();
	current_hash += last_used_move.hash();
	current_hash *= magnet_rise.max_hash();
	current_hash += magnet_rise.hash();
	current_hash *= partial_trap.max_hash();
	current_hash += partial_trap.hash();
	current_hash *= perish_song.max_hash();
	current_hash += perish_song.hash();
	current_hash *= rampage.max_hash();
	current_hash += rampage.hash();
	current_hash *= slow_start.max_hash();
	current_hash += slow_start.hash();
	current_hash *= stage.max_hash();
	current_hash += stage.hash();
	current_hash *= stockpile.max_hash();
	current_hash += stockpile.hash();
	current_hash *= m_taunt.max_hash();
	current_hash += m_taunt.hash();
	current_hash *= toxic.max_hash();
	current_hash += toxic.hash();
	current_hash *= uproar.max_hash();
	current_hash += uproar.hash();
	current_hash *= vanish.max_hash();
	current_hash += vanish.hash();
	current_hash *= yawn.max_hash();
	current_hash += yawn.hash();
	current_hash *= 2;
	current_hash += aqua_ring;
	current_hash *= 2;
	current_hash += attracted;
	current_hash *= 2;
	current_hash += charged;
	current_hash *= 2;
	current_hash += cursed;
	current_hash *= 2;
	current_hash += used_defense_curl;
	current_hash *= 2;
	current_hash += destiny_bond;
	current_hash *= 2;
	current_hash += flash_fire;
	current_hash *= 2;
	current_hash += focusing_energy;
	current_hash *= 2;
	current_hash += fully_trapped;
	current_hash *= 2;
	current_hash += gastro_acid;
	current_hash *= 2;
	current_hash += identified;
	current_hash *= 2;
	current_hash += used_imprison;
	current_hash *= 2;
	current_hash += ingrain_active;
	current_hash *= 2;
	current_hash += leech_seed;
	current_hash *= 2;
	current_hash += loaf;
	current_hash *= 2;
	current_hash += lock_on;
	current_hash *= 2;
	current_hash += minimize;
	current_hash *= 2;
	current_hash += mud_sport;
	current_hash *= 2;
	current_hash += nightmares;
	current_hash *= 2;
	current_hash += power_trick;
	current_hash *= 2;
	current_hash += recharge_lock_in;
	current_hash *= 2;
	current_hash += is_tormented;
	current_hash *= 2;
	current_hash += water_sport;
	return current_hash;
}

ActivePokemon::hash_type ActivePokemon::max_hash() const {
	hash_type current_hash = m_all_pokemon.max_hash();
	current_hash *= active_substitute.max_hash();
	current_hash *= bide.max_hash();
	current_hash *= confusion.max_hash();
	current_hash *= m_disable.max_hash();
	current_hash *= embargo.max_hash();
	current_hash *= encore.max_hash();
	current_hash *= heal_block.max_hash();
	current_hash *= last_used_move.max_hash();
	current_hash *= magnet_rise.max_hash();
	current_hash *= partial_trap.max_hash();
	current_hash *= perish_song.max_hash();
	current_hash *= rampage.max_hash();
	current_hash *= slow_start.max_hash();
	current_hash *= stage.max_hash();
	current_hash *= stockpile.max_hash();
	current_hash *= m_taunt.max_hash();
	current_hash *= toxic.max_hash();
	current_hash *= uproar.max_hash();
	current_hash *= vanish.max_hash();
	current_hash *= yawn.max_hash();
	current_hash *= 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2;
	return current_hash;
}

bool operator== (ActivePokemon const & lhs, ActivePokemon const & rhs) {
	return
			lhs.m_all_pokemon == rhs.m_all_pokemon and
			lhs.aqua_ring == rhs.aqua_ring and
			lhs.attracted == rhs.attracted and
			lhs.bide == rhs.bide and
			lhs.charged == rhs.charged and
			lhs.confusion == rhs.confusion and
			lhs.cursed == rhs.cursed and
			lhs.used_defense_curl == rhs.used_defense_curl and
			lhs.destiny_bond == rhs.destiny_bond and
			lhs.m_disable == rhs.m_disable and
			lhs.embargo == rhs.embargo and
			lhs.encore == rhs.encore and
			lhs.flash_fire == rhs.flash_fire and
			lhs.focusing_energy == rhs.focusing_energy and
			lhs.fully_trapped == rhs.fully_trapped and
			lhs.heal_block == rhs.heal_block and
			lhs.identified == rhs.identified and
			lhs.used_imprison == rhs.used_imprison and
			lhs.ingrain_active == rhs.ingrain_active and
			lhs.last_used_move == rhs.last_used_move and
			lhs.leech_seed == rhs.leech_seed and
			lhs.loaf == rhs.loaf and
			lhs.lock_on == rhs.lock_on and
			lhs.magnet_rise == rhs.magnet_rise and
			lhs.minimize == rhs.minimize and
			lhs.mud_sport == rhs.mud_sport and
			lhs.nightmares == rhs.nightmares and
			lhs.partial_trap == rhs.partial_trap and
			lhs.perish_song == rhs.perish_song and
			lhs.rampage == rhs.rampage and
			lhs.slow_start == rhs.slow_start and
			lhs.stage == rhs.stage and
			lhs.stockpile == rhs.stockpile and
			lhs.m_taunt == rhs.m_taunt and
			lhs.is_tormented == rhs.is_tormented and
			lhs.toxic == rhs.toxic and
			lhs.uproar == rhs.uproar and
			lhs.vanish == rhs.vanish and
			lhs.water_sport == rhs.water_sport and
			lhs.yawn == rhs.yawn;
}

bool operator!= (ActivePokemon const & lhs, ActivePokemon const & rhs) {
	return !(lhs == rhs);
}

}	// namespace technicalmachine
