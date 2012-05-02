// Pokemon data structure
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

#ifndef POKEMON_HPP_
#define POKEMON_HPP_

#include <string>

#include "ability.hpp"
#include "move_collection.hpp"
#include "gender.hpp"
#include "item.hpp"
#include "move.hpp"
#include "nature.hpp"
#include "species.hpp"
#include "stat.hpp"
#include "status.hpp"
#include "type_collection.hpp"

namespace technicalmachine {
// #define TECHNICALMACHINE_POKEMON_USE_NICKNAMES

class Pokemon {
	private:
		#if defined TECHNICALMACHINE_POKEMON_USE_NICKNAMES
		std::string nickname;
		#endif
	public:
		MoveCollection move;
		TypeCollection type;

		Stat hp;
		Stat atk;
		Stat def;
		Stat spa;
		Stat spd;
		Stat spe;

		// 0 through 48 for foes, used to keep the HP learned from the log on track with reality
		uint16_t new_hp;

		Species name;
		Item item;
		Ability ability;
		Gender gender;
		Status status;
		Nature nature;
		bool fainted;
		bool hidden;
		uint8_t level;
		// wakes up when this number is 2 through 5
		uint8_t sleep;

		uint8_t happiness;
	
		Pokemon (Species species, unsigned size);
		void calculate_initial_hp ();
		uint64_t hash () const;
		// Returns whether the move is found. Modifies move.index
		bool find_move (Move::Moves move_name);
		uint8_t index_of_first_switch () const;
		void normalize_hp ();
		// power of Grass Knot / Low Kick, not the actual mass stat
		uint8_t mass () const;
		static std::string to_string (Species name);
		std::string to_string () const;
		std::string get_nickname () const;
		void set_nickname (std::string const & nick);
		static Species from_string (std::string const & str);
		static bool is_alternate_form (Species first, Species second);
		static bool is_deoxys (Species species);
		static bool is_giratina (Species species);
		static bool is_rotom (Species species);
		static bool is_shaymin (Species species);
		static bool is_wormadam (Species species);
		void set_hidden_power_type ();
		friend bool operator== (Pokemon const & lhs, Pokemon const & rhs);
		friend bool operator!= (Pokemon const & lhs, Pokemon const & rhs);
	private:
		Type::Types calculate_hidden_power_type () const;
};

}	// namespace technicalmachine
#endif	// POKEMON_HPP_
