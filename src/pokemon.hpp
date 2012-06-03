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
#include "gender.hpp"
#include "item.hpp"
#include "nature.hpp"
#include "seen_pokemon.hpp"
#include "species.hpp"
#include "stat.hpp"
#include "status.hpp"
#include "type_collection.hpp"

#include "move/collection.hpp"

namespace technicalmachine {
class SharedMoves;
// #define TECHNICALMACHINE_POKEMON_USE_NICKNAMES

class Pokemon {
	public:
		Pokemon (Species species, uint8_t set_level, SharedMoves & shared, uint8_t set_happiness = 255);
		void switch_in();
		void switch_out();
		void calculate_initial_hp ();
		uint8_t index_of_first_switch () const;
		void normalize_hp ();
		uint8_t power_of_mass_based_moves() const;
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
		unsigned level() const;
		unsigned happiness() const;
		bool has_been_seen() const;
		// This function should be used instead of checking if hp == 0 to handle
		// messages being sent about multiple Pokemon fainting in one turn.
		// Using this function will allow TM to correctly update an entire turn
		// from a message.
		bool will_be_replaced() const;
		void faint();
		typedef uint64_t hash_type;
		hash_type hash () const;
		hash_type max_hash() const;
		friend bool operator== (Pokemon const & lhs, Pokemon const & rhs);

		MoveCollection move;
		TypeCollection type;
	private:
		#if defined TECHNICALMACHINE_POKEMON_USE_NICKNAMES
		std::string nickname;
		#endif
	public:

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
	private:
		bool m_will_be_replaced;
		Seen seen;
		uint8_t m_level;
		uint8_t m_happiness;
		Type::Types calculate_hidden_power_type () const;
		friend class Score;
};

bool operator!= (Pokemon const & lhs, Pokemon const & rhs);

}	// namespace technicalmachine
#endif	// POKEMON_HPP_
