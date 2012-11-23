// Team data structure
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

#ifndef TEAM_HPP_
#define TEAM_HPP_

#include <cstdint>
#include <random>
#include <string>

#include "entry_hazards.hpp"
#include "screens.hpp"
#include "wish.hpp"

#include "move/shared.hpp"

#include "pokemon/active_pokemon.hpp"
#include "pokemon/collection.hpp"
#include "pokemon/species_forward.hpp"

namespace technicalmachine {
class Ability;
class Pokemon;
class Weather;

class Team {
	public:
		Team ();
		Team(std::mt19937 & random_engine, std::string const & team_file_name);
		Team (Team const & other);
		Team (Team && other);
		Team & operator= (Team const & other);
		Team & operator= (Team && other);
		
		ActivePokemon const & pokemon() const;
		ActivePokemon & pokemon();
		Pokemon const & pokemon(PokemonCollection::index_type index) const;
		Pokemon & pokemon(PokemonCollection::index_type index);
		Pokemon const & replacement() const;
		Pokemon & replacement();
		template<typename... Args>
		void add_pokemon(Args&&... args) {
			m_all_pokemon.add(shared_moves, std::forward<Args>(args)...);
		}
		void remove_pokemon ();
		PokemonCollection const & all_pokemon() const;
		PokemonCollection & all_pokemon();
		
		unsigned number_of_seen_pokemon() const;
		unsigned size() const;
		
		bool is_me() const;
		std::string who() const;
		// Not for variables that give a message at the end of the turn, this is
		// just for some book-keeping variables.
		void reset_between_turns();
		void clear_field();
		void move(bool value = true);

		void update_chance_to_hit(Team const & target, Weather const & weather, bool target_moved);
		
		bool switch_decision_required() const;

		typedef uint64_t hash_type;
		hash_type hash () const;
		std::string to_string(bool include_owner = true) const;
		friend bool operator== (Team const & lhs, Team const & rhs);

	private:
		friend class Evaluate;
		void load(std::string const & name);

		PokemonCollection m_all_pokemon;
		SharedMoves shared_moves;
		ActivePokemon active_pokemon;
	public:
		Screens screens;
		Wish wish;
		EntryHazards entry_hazards;
	private:
		bool me;
};
bool operator!= (Team const & lhs, Team const & rhs);

}	// namespace technicalmachine
#endif	// TEAM_HPP_
