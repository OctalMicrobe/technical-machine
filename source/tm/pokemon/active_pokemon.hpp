// Copyright (C) 2019 David Stone
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

#include <tm/pokemon/active_status.hpp>
#include <tm/pokemon/confusion.hpp>
#include <tm/pokemon/disable.hpp>
#include <tm/pokemon/embargo.hpp>
#include <tm/pokemon/encore.hpp>
#include <tm/pokemon/heal_block.hpp>
#include <tm/pokemon/last_used_move.hpp>
#include <tm/pokemon/magnet_rise.hpp>
#include <tm/pokemon/partial_trap.hpp>
#include <tm/pokemon/perish_song.hpp>
#include <tm/pokemon/pokemon.hpp>
#include <tm/pokemon/slow_start.hpp>
#include <tm/pokemon/stockpile.hpp>
#include <tm/pokemon/substitute.hpp>
#include <tm/pokemon/taunt.hpp>
#include <tm/pokemon/yawn.hpp>

#include <tm/move/calculate_damage.hpp>
#include <tm/move/move.hpp>
#include <tm/move/moves.hpp>
#include <tm/move/is_switch.hpp>

#include <tm/stat/calculate.hpp>
#include <tm/stat/stage.hpp>

#include <tm/type/pokemon_types.hpp>

#include <tm/compress.hpp>
#include <tm/generation.hpp>
#include <tm/heal.hpp>
#include <tm/operators.hpp>
#include <tm/rational.hpp>
#include <tm/weather.hpp>

#include <bounded/assert.hpp>
#include <bounded/integer.hpp>
#include <bounded/optional.hpp>

#include <containers/algorithms/all_any_none.hpp>

namespace technicalmachine {
template<Generation generation>
struct ActivePokemon;

template<Generation generation>
struct MutableActivePokemon;

template<Generation generation>
struct ActivePokemonFlags {
	auto reset_start_of_turn() & {
		last_used_move.reset_start_of_turn();
		damaged = false;
		direct_damage_received = 0_bi;
		flinched = false;
		me_first_is_active = false;
		is_loafing_turn = !is_loafing_turn;
	}

	friend auto operator==(ActivePokemonFlags const &, ActivePokemonFlags const &) -> bool = default;
	friend auto compress(ActivePokemonFlags const value) {
		return bounded::tuple(
			compress_combine(
				value.ability,
				value.confusion,
				value.disable
			),
			compress_combine(
				value.embargo,
				value.encore,
				value.heal_block,
				value.last_used_move,
				value.magnet_rise,
				value.substitute,
				value.partial_trap,
				value.perish_song,
				value.stage,
				value.status,
				value.slow_start,
				value.stockpile,
				value.taunt,
				value.types,
				value.yawn,
				value.direct_damage_received,
				value.aqua_ring,
				value.attracted,
				value.charged,
				value.is_cursed,
				value.defense_curled,
				value.flash_fire,
				value.has_focused_energy,
				value.fully_trapped,
				value.gastro_acid,
				value.identified,
				value.used_imprison,
				value.ingrained,
				value.leech_seeded,
				value.is_loafing_turn,
				value.minimized,
				value.mud_sport,
				value.power_trick_is_active,
				value.is_tormented,
				value.unburdened,
				value.water_sport
			)
		);
	}
private:
	template<Generation, bool>
	friend struct ActivePokemonImpl;
	template<Generation>
	friend struct MutableActivePokemon;
	
	Ability ability{};
	Confusion confusion;
	Disable disable;
	EmbargoCounter embargo;
	EncoreCounter encore;
	HealBlock heal_block;
	LastUsedMove last_used_move;
	MagnetRise magnet_rise;
	Substitute substitute;
	PartialTrap partial_trap;
	PerishSong perish_song;
	Stage stage;
	ActiveStatus status;
	SlowStart slow_start;
	Stockpile stockpile;
	TauntCounter taunt;
	PokemonTypes types{Type::Typeless};
	YawnCounter yawn;
	HP::current_type direct_damage_received = 0_bi;
	bool aqua_ring = false;
	bool attracted = false;
	bool charged = false;
	bool is_cursed = false;
	bool damaged = false;
	bool defense_curled = false;
	bool flash_fire = false;
	bool flinched = false;
	bool has_focused_energy = false;
	// Block, Mean Look, Spider Web
	bool fully_trapped = false;
	bool gastro_acid = false;
	bool identified = false;
	bool used_imprison = false;
	bool ingrained = false;
	bool leech_seeded = false;
	bool is_loafing_turn = false;
	bool me_first_is_active = false;
	bool minimized = false;
	bool mud_sport = false;
	bool power_trick_is_active = false;
	bool is_tormented = false;
	bool unburdened = false;
	bool water_sport = false;
};

// TODO: Implement both ActivePokemon and MutableActivePokemon as typedefs once
// we get requires clauses.
template<Generation generation, bool is_const>
struct ActivePokemonImpl {
private:
	using PokemonRef = std::conditional_t<is_const, Pokemon<generation> const &, Pokemon<generation> &>;
	using FlagsRef = std::conditional_t<is_const, ActivePokemonFlags<generation> const &, ActivePokemonFlags<generation> &>;
public:
	ActivePokemonImpl(PokemonRef pokemon, FlagsRef flags):
		m_pokemon(pokemon),
		m_flags(flags)
	{
	}
	ActivePokemonImpl(ActivePokemonImpl const & other) = default;
	ActivePokemonImpl(ActivePokemonImpl && other) = default;
	ActivePokemonImpl & operator=(ActivePokemonImpl const & other) = delete;
	ActivePokemonImpl & operator=(ActivePokemonImpl && other) = delete;

	auto regular_moves() const -> RegularMoves const & {
		return m_pokemon.regular_moves();
	}

	auto hp() const {
		return m_pokemon.hp();
	}
	auto stat(RegularStat const stat_name) const {
		return m_pokemon.stat(stat_name);
	}

	auto last_used_move() const -> LastUsedMove {
		return m_flags.last_used_move;
	}
	auto substitute() const -> Substitute const & {
		return m_flags.substitute;
	}

	auto ability() const {
		return m_flags.ability;
	}

	auto aqua_ring_is_active() const -> bool {
		return m_flags.aqua_ring;
	}

	auto charge_boosted(Type const move_type) const -> bool {
		return m_flags.charged and move_type == Type::Electric;
	}

	auto is_charging_up() const -> bool {
		return m_flags.last_used_move.is_charging_up();
	}

	auto is_confused() const -> bool {
		return m_flags.confusion.is_active();
	}

	auto is_cursed() const -> bool {
		return m_flags.is_cursed;
	}

	auto defense_curled() const -> bool {
		return m_flags.defense_curled;
	}

	auto damaged() const -> bool {
		return m_flags.damaged;
	}

	auto direct_damage_received() const -> HP::current_type {
		return m_flags.direct_damage_received;
	}

	// Requires that move is actually one of this Pokemon's moves
	auto is_disabled(Moves const move_name) const -> bool {
		return m_flags.disable.move_is_disabled(move_name);
	}

	auto is_encored() const -> bool {
		return m_flags.encore.is_active();
	}

	auto flash_fire_is_active() const -> bool {
		return m_flags.flash_fire;
	}

	auto flinched() const -> bool {
		return m_flags.flinched;
	}

	auto has_focused_energy() const -> bool {
		return m_flags.has_focused_energy;
	}

	auto gender() const -> Gender {
		return m_pokemon.gender();
	}

	auto happiness() const -> Happiness {
		return m_pokemon.happiness();
	}

	auto heal_block_is_active() const -> bool {
		return m_flags.heal_block.is_active();
	}

	auto hidden_power() const -> bounded::optional<HiddenPower> {
		return m_pokemon.hidden_power();
	}

	auto used_imprison() const -> bool {
		return m_flags.used_imprison;
	}

	auto ingrained() const -> bool {
		return m_flags.ingrained;
	}

	auto item(Weather const weather) const -> Item {
		return m_pokemon.item(m_flags.embargo.is_active(), weather.magic_room());
	}
	auto unrestricted_item() const -> Item {
		return m_pokemon.item(false, false);
	}

	auto leech_seeded() const -> bool {
		return m_flags.leech_seeded;
	}

	auto level() const -> Level {
		return m_pokemon.level();
	}

	auto is_loafing() const -> bool {
		return ability() == Ability::Truant and m_flags.is_loafing_turn;
	}

	auto locked_on() const -> bool {
		return m_flags.last_used_move.locked_on();
	}

	auto magnet_rise() const -> MagnetRise const & {
		return m_flags.magnet_rise;
	}

	auto me_first_is_active() const -> bool {
		return m_flags.me_first_is_active;
	}

	auto minimized() const -> bool {
		return m_flags.minimized;
	}

	auto moved() const -> bool {
		return m_flags.last_used_move.moved_this_turn();
	}

	auto power_trick_is_active() const -> bool {
		return m_flags.power_trick_is_active;
	}
	
	auto is_protecting() const {
		return m_flags.last_used_move.is_protecting();
	}

	auto is_locked_in_by_move() const -> bool {
		return m_flags.last_used_move.is_locked_in_by_move();
	}

	auto is_roosting() const -> bool {
		return m_flags.last_used_move.is_roosting();
	}

	auto slow_start_is_active() const -> bool {
		return m_flags.slow_start.is_active();
	}

	auto species() const -> Species {
		return m_pokemon.species();
	}

	auto sport_is_active(Type const move_type) const -> bool {
		switch (move_type) {
			case Type::Electric: return m_flags.mud_sport;
			case Type::Fire: return m_flags.water_sport;
			default: return false;
		}
	}

	auto stage() const -> Stage const & {
		return m_flags.stage;
	}

	auto spit_up_power() const {
		return m_flags.stockpile.spit_up_power();
	}

	auto status() const -> Status {
		return m_pokemon.status();
	}

	auto switch_decision_required() const -> bool {
		return m_pokemon.hp() == 0_bi or m_flags.last_used_move.switch_decision_required();
	}
	auto switched_in_this_turn() const -> bool {
		return m_flags.last_used_move.switched_in_this_turn();
	}

	auto fully_trapped() const -> bool {
		return m_flags.fully_trapped;
	}

	auto trapped() const -> bool {
		return m_flags.fully_trapped or ingrained() or m_flags.partial_trap.is_active();
	}

	auto is_tormented() const -> bool {
		return m_flags.is_tormented;
	}

	auto is_taunted() const -> bool {
		return m_flags.taunt.is_active();
	}

	auto types() const {
		return m_flags.types;
	}

	auto is_unburdened() const {
		return m_flags.unburdened;
	}

	auto is_uproaring() const -> bool {
		return m_flags.last_used_move.is_uproaring();
	}

	auto vanish_doubles_power(Moves const move_name) const -> bool {
		return m_flags.last_used_move.vanish_doubles_power(generation, move_name);
	}

protected:
	PokemonRef m_pokemon;
	FlagsRef m_flags;
};

template<Generation generation>
auto apply_own_mental_herb(MutableActivePokemon<generation> const pokemon, Weather const weather) -> void {
	if (pokemon.item(weather) == Item::Mental_Herb) {
		apply_mental_herb(pokemon);
		pokemon.remove_item();
	}
}

// A reference to the currently active Pokemon
template<Generation generation>
struct ActivePokemon : ActivePokemonImpl<generation, true> {
	ActivePokemon(Pokemon<generation> const & pokemon, ActivePokemonFlags<generation> const & flags):
		ActivePokemonImpl<generation, true>(pokemon, flags)
	{
	}
};

template<Generation generation>
inline auto is_type(ActivePokemon<generation> const pokemon, Type const type) -> bool {
	return
		(type != Type::Flying or !pokemon.is_roosting()) and
		containers::any_equal(pokemon.types(), type);
}

template<Generation generation>
auto grounded(ActivePokemon<generation> const pokemon, Weather const weather) -> bool {
	auto item_grounds = [=] {
		auto const item = generation <= Generation::four ?
			pokemon.unrestricted_item() :
			pokemon.item(weather);
		return item == Item::Iron_Ball;
	};

	return
		!(
			is_type(pokemon, Type::Flying) or
			is_immune_to_ground(pokemon.ability()) or
			pokemon.magnet_rise().is_active() or
			pokemon.item(weather) == Item::Air_Balloon
		) or
		weather.gravity() or
		item_grounds() or
		pokemon.ingrained();
}

template<Generation generation>
auto apply_status_to_self(Statuses const status_name, MutableActivePokemon<generation> target, Weather const weather, bool const uproar = false) -> void {
	target.apply_status(status_name, target, weather, uproar);
}

template<Generation generation>
auto activate_berserk_gene(MutableActivePokemon<generation> pokemon, Weather const weather) -> void {
	pokemon.stage()[BoostableStat::atk] += 2_bi;
	// TODO: Berserk Gene causes 256-turn confusion, unless the Pokemon
	// switching out was confused.
	pokemon.confuse(weather);
	pokemon.remove_item();
}

constexpr auto reflected_status(Generation const generation, Statuses const status) -> bounded::optional<Statuses> {
	switch (status) {
	case Statuses::burn:
	case Statuses::paralysis:
	case Statuses::poison:
		return status;
	case Statuses::toxic:
		return generation <= Generation::four ? Statuses::poison : Statuses::toxic;
	case Statuses::clear:
	case Statuses::freeze:
	case Statuses::sleep:
	case Statuses::rest:
		return bounded::none;
	}
}

constexpr bool cannot_ko(Moves const move) {
	return move == Moves::False_Swipe;
}

template<Generation generation>
auto status_can_apply(Statuses const status, ActivePokemon<generation> const user, ActivePokemon<generation> const target, Weather const weather, bool const uproar) {
	return
		is_clear(target.status()) and
		!blocks_status(target.ability(), user.ability(), status, weather) and
		!containers::any(target.types(), [=](Type const type) { return blocks_status(type, status); }) and
		(!uproar or (status != Statuses::sleep and status != Statuses::rest));
}

template<Generation>
struct MutableActivePokemon;

template<Generation generation>
auto as_const(MutableActivePokemon<generation> pokemon) {
	return ActivePokemon<generation>(pokemon);
}

// A mutable reference to the currently active Pokemon
template<Generation generation>
struct MutableActivePokemon : ActivePokemonImpl<generation, false> {
	MutableActivePokemon(Pokemon<generation> & pokemon, ActivePokemonFlags<generation> & flags):
		ActivePokemonImpl<generation, false>(pokemon, flags)
	{
	}
	
	operator ActivePokemon<generation>() const {
		return ActivePokemon<generation>(this->m_pokemon, this->m_flags);
	}

	auto regular_moves() const -> RegularMoves & {
		return this->m_pokemon.regular_moves();
	}

	auto stage() const -> Stage & {
		return this->m_flags.stage;
	}

	auto clear_field() const {
		this->m_flags.leech_seeded = false;
		this->m_flags.partial_trap = {};
	}

	auto set_ability(Ability const ability) const {
		this->m_flags.ability = ability;
	}
	auto set_base_ability(Ability const ability) const {
		this->m_pokemon.set_initial_ability(ability);
		set_ability(ability);
	}
	auto set_ability_to_base_ability() const {
		set_ability(this->m_pokemon.initial_ability());
	}

	auto activate_aqua_ring() const {
		this->m_flags.aqua_ring = true;
	}
	auto attract(MutableActivePokemon<generation> other, Weather const weather) const -> void {
		auto handle_item = [&] {
			switch (this->item(weather)) {
				case Item::Mental_Herb:
					apply_own_mental_herb(*this, weather);
					break;
				case Item::Destiny_Knot:
					remove_item();
					other.attract(*this, weather);
					break;
				default:
					break;
			}
		};
		auto const ability_cures_attract = this->ability() == Ability::Oblivious;
		if (generation <= Generation::four) {
			if (!ability_cures_attract) {
				this->m_flags.attracted = true;
				handle_item();
			}
		} else {
			this->m_flags.attracted = true;
			handle_item();
			if (ability_cures_attract) {
				this->m_flags.attracted = false;
			}
		}
	}

	auto charge() const {
		this->m_flags.charged = true;
	}
	auto use_charge_up_move() const -> void {
		this->m_flags.last_used_move.use_charge_up_move();
	}
	auto confuse(Weather const weather) const -> void {
		if (blocks_confusion(this->ability())) {
			return;
		}
		if (clears_confusion(this->item(weather))) {
			remove_item();
		} else {
			this->m_flags.confusion.activate();
		}
	}
	auto handle_confusion() const {
		this->m_flags.confusion.do_turn();
	}
	auto curse() const {
		this->m_flags.is_cursed = true;
	}
	auto defense_curl() const {
		this->m_flags.defense_curled = true;
	}
	auto disable(Moves const move, Weather const weather) const {
		this->m_flags.disable.activate(move);
		apply_own_mental_herb(*this, weather);
	}
	auto advance_disable() const {
		this->m_flags.disable.advance_one_turn();
	}
	auto activate_embargo() const {
		this->m_flags.embargo.activate();
	}
	auto advance_embargo() const {
		this->m_flags.embargo.advance_one_turn();
	}
	auto activate_encore(Weather const weather) const {
		this->m_flags.encore.activate();
		apply_own_mental_herb(*this, weather);
	}
	auto advance_encore() const {
		this->m_flags.encore.advance_one_turn();
	}
	auto activate_flash_fire() const {
		this->m_flags.flash_fire = true;
	}
	auto flinch() const {
		this->m_flags.flinched = true;
	}
	auto focus_energy() const {
		this->m_flags.has_focused_energy = true;
	}
	auto fully_trap() const {
		this->m_flags.fully_trapped = true;
	}
	auto activate_heal_block() const {
		this->m_flags.heal_block.activate();
	}
	auto advance_heal_block() const {
		this->m_flags.heal_block.advance_one_turn();
	}
	auto identify() const {
		this->m_flags.identified = true;
	}
	auto use_imprison() const {
		this->m_flags.used_imprison = true;
	}
	auto ingrain() const {
		this->m_flags.ingrained = true;
	}

	auto remove_item() const -> bounded::optional<Item> {
		auto result = this->m_pokemon.remove_item();
		if (result) {
			this->m_flags.unburdened = true;
		}
		return result;
	}
	auto destroy_item() const -> bool {
		auto result = this->m_pokemon.destroy_item();
		if (result) {
			this->m_flags.unburdened = true;
		}
		return result;
	}
	auto recycle_item() const -> void {
		this->m_pokemon.recycle_item();
	}
	auto steal_item(MutableActivePokemon<generation> other) const -> void {
		if (this->unrestricted_item() != Item::None) {
			return;
		}
		if (auto const other_item = other.remove_item()) {
			this->m_pokemon.set_item(*other_item);
		}
	}
	friend auto swap_items(MutableActivePokemon<generation> user, MutableActivePokemon<generation> other) -> void {
		auto const user_item = user.unrestricted_item();
		auto const other_item = other.unrestricted_item();
		if (!cannot_be_lost(user_item) and !cannot_be_lost(other_item)) {
			user.m_pokemon.set_item(other_item);
			other.m_pokemon.set_item(user_item);
		}
	}



	auto hit_with_leech_seed() const {
		this->m_flags.leech_seeded = true;
	}
	auto advance_lock_in(bool const ending, Weather const weather) const {
		auto const confused = this->m_flags.last_used_move.advance_lock_in(ending);
		if (confused) {
			confuse(weather);
		}
	}
	auto activate_magnet_rise() const {
		this->m_flags.magnet_rise.activate();
	}
	auto advance_magnet_rise() const {
		this->m_flags.magnet_rise.advance_one_turn();
	}
	friend auto apply_mental_herb(MutableActivePokemon<generation> const pokemon) {
		pokemon.m_flags.attracted = false;
		if (generation >= Generation::five) {
			pokemon.m_flags.disable = {};
			pokemon.m_flags.encore = {};
			pokemon.m_flags.taunt = {};
			pokemon.m_flags.is_tormented = false;
		}
	}
	auto minimize() const {
		this->m_flags.minimized = true;
		stage()[BoostableStat::eva] += BOUNDED_CONDITIONAL(generation <= Generation::four, 1_bi, 2_bi);
	}
	auto activate_mud_sport() const {
		this->m_flags.mud_sport = true;
	}
	auto try_to_give_nightmares() const {
		if (is_sleeping(this->status())) {
			this->m_flags.status.give_nightmares();
		}
	}
	auto partially_trap() const {
		this->m_flags.partial_trap.activate();
	}
	auto partial_trap_damage(Weather const weather) const {
		this->m_flags.partial_trap.damage(*this, weather);
	}
	auto try_activate_perish_song() const {
		if (!blocks_sound_moves(this->ability())) {
			this->m_flags.perish_song.activate();
		}
	}
	auto perish_song_turn() const -> void {
		bool const faints_this_turn = this->m_flags.perish_song.advance_one_turn();
		if (faints_this_turn) {
			this->m_pokemon.set_hp(0_bi);
		}
	}
	auto activate_power_trick() const {
		this->m_flags.power_trick_is_active = !this->m_flags.power_trick_is_active;
	}
	auto protect() const {
		this->m_flags.last_used_move.protect();
	}
	auto break_protect() const {
		this->m_flags.last_used_move.break_protect();
	}
	auto activate_rampage() const {
		this->m_flags.last_used_move.activate_rampage();
	}
	auto recharge() const -> bool {
		return this->m_flags.last_used_move.recharge();
	}
	auto use_recharge_move() const {
		this->m_flags.last_used_move.use_recharge_move();
	}

	auto apply_status(Statuses const status, MutableActivePokemon<generation> user, Weather const weather, bool const uproar = false) const -> void {
		BOUNDED_ASSERT_OR_ASSUME(status != Statuses::clear);
		BOUNDED_ASSERT_OR_ASSUME(status != Statuses::rest);
		if (!status_can_apply(status, as_const(user), as_const(*this), weather, uproar)) {
			return;
		}
		set_status(status, weather);
		auto const reflected = reflected_status(generation, status);
		if (reflected and reflects_status(this->ability())) {
			user.apply_status(*reflected, *this, weather, uproar);
		}
	}

	auto rest(Weather const weather, bool const other_is_uproaring) const -> void {
		if (other_is_uproaring) {
			return;
		}
		if (generation >= Generation::three and is_sleeping(this->m_pokemon.status())) {
			return;
		}
		if (blocks_status(this->ability(), this->ability(), Statuses::rest, weather)) {
			return;
		}
		auto const active_hp = this->hp();
		if (active_hp.current() == active_hp.max() or healing_move_fails_in_generation_1(active_hp)) {
			return;
		}
		this->m_pokemon.set_hp(active_hp.max());
		set_status(Statuses::rest, weather);
	}

	auto status_and_leech_seed_effects(MutableActivePokemon<generation> const other, Weather const weather, bool const uproar = false) const {
		this->m_flags.status.status_and_leech_seed_effects(*this, other, weather, uproar);
	}
	auto clear_status() const -> void {
		this->m_pokemon.set_status(Statuses::clear);
		this->m_flags.status.set(Statuses::clear);
	}
	auto advance_status_from_move(bool const clear_status) & {
		this->m_pokemon.advance_status_from_move(this->ability(), clear_status);
	}

	
	auto increment_stockpile() const -> void {
		bool const increased = this->m_flags.stockpile.increment();
		if (increased) {
			boost_defensive(stage(), 1_bi);
		}
	}
	auto release_stockpile() const -> bounded::integer<0, Stockpile::max> {
		auto const stages = this->m_flags.stockpile.release();
		boost_defensive(stage(), -stages);
		return stages;
	}

	auto use_substitute(Weather const weather) const -> void {
		auto const can_use_substitute = this->hp().current() > this->hp().max() / 4_bi;
		if (!can_use_substitute) {
			return;
		}
		indirect_damage(weather, this->m_flags.substitute.create(this->hp().max()));
	}

	auto switch_in(Weather const weather) const {
		this->m_pokemon.mark_as_seen();
		this->m_flags.ability = this->m_pokemon.initial_ability();
		// The exact switch is irrelevant
		this->m_flags.last_used_move.successful_move(Moves::Switch0);
		this->m_flags.types = PokemonTypes(generation, this->m_pokemon.species());
		if (generation <= Generation::two and this->m_pokemon.status().name() == Statuses::toxic) {
			this->m_pokemon.set_status(Statuses::poison);
		}
		this->m_flags.status.set(this->m_pokemon.status().name());
		if (this->item(weather) == Item::Berserk_Gene) {
			activate_berserk_gene(*this, weather);
		}
	}

	auto switch_out() const -> void {
		if (clears_status_on_switch(this->ability())) {
			clear_status();
		}
		// TODO: remove some of these when the foe switches, too
		if (!this->m_flags.last_used_move.is_baton_passing()) {
			this->m_flags.aqua_ring = false;
			this->m_flags.confusion = {};
			this->m_flags.is_cursed = false;
			this->m_flags.embargo = {};
			this->m_flags.has_focused_energy = false;
			this->m_flags.gastro_acid = false;
			this->m_flags.ingrained = false;
			this->m_flags.leech_seeded = false;
			this->m_flags.magnet_rise = {};
			this->m_flags.perish_song = {};
			this->m_flags.power_trick_is_active = false;
			this->m_flags.stage = {};
			this->m_flags.substitute = {};
		}
		this->m_flags.attracted = false;
		this->m_flags.charged = false;
		this->m_flags.defense_curled = false;
		this->m_flags.disable = Disable{};
		this->m_flags.encore = {};
		this->m_flags.flash_fire = false;
		this->m_flags.flinched = false;
		this->m_flags.fully_trapped = false;
		this->m_flags.heal_block = {};
		this->m_flags.identified = false;
		this->m_flags.used_imprison = false;
		this->m_flags.last_used_move = {};
		this->m_flags.is_loafing_turn = true;
		this->m_flags.minimized = false;
		this->m_flags.me_first_is_active = false;
		this->m_flags.mud_sport = false;
		this->m_flags.partial_trap = {};
		this->m_flags.slow_start = {};
		this->m_flags.stockpile = {};
		this->m_flags.is_tormented = false;
		this->m_flags.unburdened = false;
		this->m_flags.water_sport = false;
		this->m_flags.taunt = {};
		this->m_flags.yawn = {};
	}


	auto taunt(Weather const weather) const {
		this->m_flags.taunt.activate();
		apply_own_mental_herb(*this, weather);
	}
	auto advance_taunt() const {
		this->m_flags.taunt.advance_one_turn();
	}
	auto torment(Weather const weather) const {
		this->m_flags.is_tormented = true;
		apply_own_mental_herb(*this, weather);
	}
	auto set_type(Type const type) const {
		this->m_flags.types = PokemonTypes(type);
	}
	auto use_uproar() const -> void {
		this->m_flags.last_used_move.use_uproar();
	}
	auto activate_water_sport() const {
		this->m_flags.water_sport = true;
	}
	auto hit_with_yawn() const {
		this->m_flags.yawn.activate();
	}
	auto try_to_activate_yawn(Weather const weather, bool const either_is_uproaring) const -> void {
		bool const put_to_sleep = this->m_flags.yawn.advance_one_turn();
		if (put_to_sleep) {
			apply_status_to_self(Statuses::sleep, *this, weather, either_is_uproaring);
		}
	}

	// Returns whether the move hits
	auto use_vanish_move(Weather const weather) const -> bool {
		auto result = this->m_flags.last_used_move.use_vanish_move(this->item(weather));
		switch (result) {
			case VanishOutcome::vanishes: return false;
			case VanishOutcome::attacks: return true;
			case VanishOutcome::consumes_item: remove_item(); return true;
		}
	}

	auto use_bide(MutableActivePokemon<generation> target, Weather const weather) const -> void {
		if (auto const damage = this->m_flags.last_used_move.use_bide()) {
			change_hp(target, weather, -*damage * 2_bi);
		}
	}

	auto set_hp(Weather const weather, auto const hp) const -> void {
		this->m_pokemon.set_hp(hp);
		activate_pinch_item(weather);
	}
	auto indirect_damage(Weather const weather, HP::current_type const damage) const -> void {
		change_hp(*this, weather, -damage);
		this->m_flags.damaged = true;
	}

	auto direct_damage(Moves const move, MutableActivePokemon<generation> user, Weather const weather, damage_type const damage) const -> HP::current_type {
		auto const interaction = substitute_interaction(generation, move);
		BOUNDED_ASSERT(!this->m_flags.substitute or interaction != Substitute::causes_failure);
		if (this->m_flags.substitute and interaction == Substitute::absorbs) {
			return this->m_flags.substitute.damage(damage);
		}
		auto const original_hp = this->hp().current();
		auto const block_ko = original_hp <= damage and handle_ko(move, weather);
		auto const applied_damage = block_ko ?
			static_cast<HP::current_type>(original_hp - 1_bi) :
			bounded::min(damage, original_hp);

		indirect_damage(weather, applied_damage);
		this->m_flags.direct_damage_received = applied_damage;
		this->m_flags.last_used_move.direct_damage(applied_damage);

		// TODO: Resolve ties properly
		if (this->m_flags.last_used_move.is_destiny_bonded() and applied_damage == original_hp) {
			user.set_hp(weather, 0_bi);
		}
		return applied_damage;
	}

	auto successfully_use_move(Moves const move) const {
		this->m_flags.last_used_move.successful_move(move);
	}
	auto unsuccessfully_use_move(Moves const move) const {
		this->m_flags.last_used_move.unsuccessful_move(move);
	}

private:
	auto handle_ko(Moves const move, Weather const weather) const {
		if (cannot_ko(move) or this->m_flags.last_used_move.is_enduring()) {
			return true;
		}
		auto const hp = this->hp();
		if (hp.current() != hp.max()) {
			return false;
		}
		if (generation >= Generation::five and this->ability() == Ability::Sturdy) {
			return true;
		}
		if (this->item(weather) == Item::Focus_Sash) {
			remove_item();
			return true;
		}
		return false;
	}

	auto activate_pinch_item(Weather const weather) const -> void {
		// TODO: Confusion damage does not activate healing berries in Generation 5+
		auto consume = [&] { remove_item(); };

		auto const current_hp = hp_ratio(this->m_pokemon);

		auto quarter_threshold = [&] {
			return BOUNDED_CONDITIONAL(this->ability() == Ability::Gluttony, rational(1_bi, 2_bi), rational(1_bi, 4_bi));
		};

		auto healing_berry = [&](auto const threshold, auto const amount) {
			if (current_hp > threshold) {
				return false;
			}
			consume();
			this->m_pokemon.set_hp(this->hp().current() + amount);
			return true;
		};

		auto confusion_berry = [&](RegularStat const stat) {
			auto const amount = this->hp().max() / BOUNDED_CONDITIONAL(generation <= Generation::six, 8_bi, 2_bi);
			auto const threshold = generation <= Generation::six ? rational(1_bi, 2_bi) : quarter_threshold();
			auto const activated = healing_berry(threshold, amount);
			if (activated and lowers_stat(this->m_pokemon.nature(), stat)) {
				confuse(weather);
			}
		};

		auto stat_boost_berry = [&](BoostableStat const stat) {
			if (current_hp > quarter_threshold()) {
				return;
			}
			consume();
			stage()[stat] += 1_bi;
		};

		switch (this->item(weather)) {
			case Item::Aguav_Berry:
				confusion_berry(RegularStat::spd);
				break;
			case Item::Apicot_Berry:
				stat_boost_berry(BoostableStat::spd);
				break;
			case Item::Berry:
			case Item::Oran_Berry:
				healing_berry(rational(1_bi, 2_bi), 10_bi);
				break;
			case Item::Berry_Juice:
				healing_berry(rational(1_bi, 2_bi), 20_bi);
				break;
			case Item::Custap_Berry:
				consume();
				break;
			case Item::Figy_Berry:
				confusion_berry(RegularStat::atk);
				break;
			case Item::Ganlon_Berry:
				stat_boost_berry(BoostableStat::def);
				break;
			case Item::Gold_Berry:
				healing_berry(rational(1_bi, 2_bi), 30_bi);
				break;
			case Item::Iapapa_Berry:
				confusion_berry(RegularStat::def);
				break;
			case Item::Lansat_Berry:
				consume();
				break;
			case Item::Liechi_Berry:
				stat_boost_berry(BoostableStat::atk);
				break;
			case Item::Mago_Berry:
				confusion_berry(RegularStat::spe);
				break;
			case Item::Micle_Berry:
				consume();
				break;
			case Item::Petaya_Berry:
				stat_boost_berry(BoostableStat::spa);
				break;
			case Item::Salac_Berry:
				stat_boost_berry(BoostableStat::spe);
				break;
			case Item::Sitrus_Berry:
				healing_berry(
					rational(1_bi, 2_bi),
					BOUNDED_CONDITIONAL(generation <= Generation::three, 30_bi, this->hp().max() / 4_bi)
				);
				break;
			case Item::Starf_Berry:
				// TODO: Raise Atk, Def, SpA, SpD, or Spe +2
				consume();
				break;
			case Item::Wiki_Berry:
				confusion_berry(RegularStat::spa);
				break;
			default:
				break;
		}
	}

	auto set_status(Statuses const status_name, Weather const weather) const -> void {
		if (clears_status(this->item(weather), status_name)) {
			remove_item();
		} else {
			this->m_pokemon.set_status(status_name);
			this->m_flags.status.set(status_name);
		}
	}
};

template<Generation generation>
auto all_moves(ActivePokemon<generation> const pokemon, TeamSize const team_size) {
	return MoveContainer<generation>(pokemon.regular_moves(), team_size);
}

template<Generation generation>
auto change_hp(MutableActivePokemon<generation> pokemon, Weather const weather, auto const change) {
	pokemon.set_hp(weather, pokemon.hp().current() + change);
}

template<Generation generation>
auto shift_status(MutableActivePokemon<generation> user, MutableActivePokemon<generation> target, Weather const weather) -> void {
	auto const status_name = user.status().name();
	switch (status_name) {
		case Statuses::burn:
		case Statuses::paralysis:
		case Statuses::poison:
		case Statuses::toxic:
			target.apply_status(status_name, user, weather);
			break;
		case Statuses::sleep: // TODO: Sleep Clause
		case Statuses::rest: // TODO: How does Rest shift?
			target.apply_status(Statuses::sleep, user, weather);
			break;
		default:
			break;
	}
	user.clear_status();
}

template<Generation generation>
auto apply_white_herb(MutableActivePokemon<generation> const pokemon) {
	for (auto & stage : pokemon.stage()) {
		if (stage < 0_bi) {
			stage = 0_bi;
		}
	}
}

template<Generation generation>
auto apply_own_white_herb(MutableActivePokemon<generation> const pokemon, Weather const weather) {
	if (pokemon.item(weather) == Item::White_Herb) {
		apply_white_herb(pokemon);
		pokemon.remove_item();
	}
}

template<Generation generation>
bool blocks_switching(Ability const ability, ActivePokemon<generation> const switcher, Weather const weather) {
	auto ghost_immunity = [&]{
		return generation >= Generation::six and is_type(switcher, Type::Ghost);
	};
	switch (ability) {
		case Ability::Shadow_Tag:
			return (generation <= Generation::three or switcher.ability() != Ability::Shadow_Tag) and !ghost_immunity();
		case Ability::Arena_Trap:
			return grounded(switcher, weather) and !ghost_immunity();
		case Ability::Magnet_Pull:
			return is_type(switcher, Type::Steel) and !ghost_immunity();
		default:
			return false;
	}
}

template<Generation generation>
void activate_ability_on_switch(MutableActivePokemon<generation> switcher, MutableActivePokemon<generation> other, Weather & weather) {
	auto const switcher_ability = switcher.ability();
	switch (switcher_ability) {
		case Ability::Download: {
			// Move is irrelevant here
			constexpr auto move = Moves::Switch0;
			// TODO: Should not take into account items, abilities, or Wonder Room
			auto const defense = calculate_defense(as_const(other), move, weather);
			auto const special_defense = calculate_special_defense(as_const(other), switcher_ability, weather);
			switcher.stage()[defense >= special_defense ? BoostableStat::spa : BoostableStat::atk] += 1_bi;
			break;
		}
		case Ability::Drizzle:
			weather.activate_rain_from_ability(generation, extends_rain(switcher.item(weather)));
			break;
		case Ability::Drought:
			weather.activate_sun_from_ability(generation, extends_sun(switcher.item(weather)));
			break;
		case Ability::Forecast:
			break;
		case Ability::Intimidate: {
			if (blocks_intimidate(generation, other.ability())) {
				break;
			}
			auto & attack = other.stage()[BoostableStat::atk];
			if (attack == bounded::min_value<Stage::value_type>) {
				break;
			}
			attack -= 1_bi;
			auto & speed = other.stage()[BoostableStat::spe];
			if (other.item(weather) == Item::Adrenaline_Orb and speed != bounded::max_value<Stage::value_type>) {
				speed += 1_bi;
				other.remove_item();
			}
			break;
		}
		case Ability::Sand_Stream:
			weather.activate_sand_from_ability(generation, extends_sand(switcher.item(weather)));
			break;
		case Ability::Snow_Warning:
			weather.activate_hail_from_ability(generation, extends_hail(switcher.item(weather)));
			break;
		case Ability::Trace: {
			auto const other_ability = other.ability();
			if (traceable(generation, other_ability)) {
				switcher.set_ability(other_ability);
			}
			break;
		}
		default:
			break;
	}
}

} // namespace technicalmachine
