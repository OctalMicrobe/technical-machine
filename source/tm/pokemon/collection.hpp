// Collection of Pokemon with index indicating current Pokemon
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

#include <tm/pokemon/max_pokemon_per_team.hpp>
#include <tm/pokemon/pokemon.hpp>
#include <tm/pokemon/pokemon_not_found.hpp>

#include <tm/compress.hpp>
#include <tm/operators.hpp>

#include <bounded/assert.hpp>
#include <bounded/integer.hpp>

#include <containers/algorithms/find.hpp>
#include <containers/common_container_functions.hpp>
#include <containers/index_type.hpp>
#include <containers/static_vector/static_vector.hpp>

#include <stdexcept>

namespace technicalmachine {
using namespace bounded::literal;
enum class Generation : std::uint8_t;

struct PokemonCollection {
	using Container = containers::static_vector<Pokemon, max_pokemon_per_team.value()>;
	using value_type = Container::value_type;
	using size_type = Container::size_type;
	using const_iterator = Container::const_iterator;

	explicit PokemonCollection(TeamSize const initial_size):
		m_real_size(initial_size)
	{
	}

	friend auto begin(PokemonCollection const & collection) {
		return begin(collection.m_container);
	}
	friend auto begin(PokemonCollection & collection) {
		return begin(collection.m_container);
	}
	friend auto end(PokemonCollection const & collection) {
		return end(collection.m_container);
	}
	friend auto end(PokemonCollection & collection) {
		return end(collection.m_container);
	}
	
	void set_index(containers::index_type<PokemonCollection> const new_index) {
		check_range(new_index);
		m_index = new_index;
	}
	void reset_index() {
		m_index = 0_bi;
	}
	constexpr auto index() const {
		return m_index;
	}

	constexpr decltype(auto) operator()(containers::index_type<PokemonCollection> const specified_index) const {
		check_range(specified_index);
		return m_container[specified_index];
	}
	constexpr decltype(auto) operator()(containers::index_type<PokemonCollection> const specified_index) {
		check_range(specified_index);
		return m_container[specified_index];
	}
	constexpr decltype(auto) operator()() const {
		return m_container[index()];
	}
	constexpr decltype(auto) operator()() {
		return m_container[index()];
	}

	auto real_size() const {
		return m_real_size;
	}

	Pokemon & add(Generation const generation, auto && ... args) {
		check_not_full();
		return containers::lazy_push_back(m_container, [&] {
			return Pokemon(generation, m_real_size, OPERATORS_FORWARD(args)...);
		});
	}
	Pokemon & add(Pokemon pokemon) {
		check_not_full();
		return containers::push_back(m_container, std::move(pokemon));
	}

	void remove_active(containers::index_type<PokemonCollection> index_of_replacement);

	friend auto operator==(PokemonCollection const &, PokemonCollection const &) -> bool = default;
	friend auto compress(PokemonCollection const & value) {
		static_assert(bounded::max_value<decltype(size(value.m_container))> == 6_bi);
		auto const p0 = size(value.m_container) >= 1_bi ? compress(value.m_container[0_bi]) : 0_bi;
		auto const p1 = size(value.m_container) >= 2_bi ? compress(value.m_container[1_bi]) : 0_bi;
		auto const p2 = size(value.m_container) >= 3_bi ? compress(value.m_container[2_bi]) : 0_bi;
		auto const p3 = size(value.m_container) >= 4_bi ? compress(value.m_container[3_bi]) : 0_bi;
		auto const p4 = size(value.m_container) >= 5_bi ? compress(value.m_container[4_bi]) : 0_bi;
		auto const p5 = size(value.m_container) >= 6_bi ? compress(value.m_container[5_bi]) : 0_bi;
		return bounded::tuple(
			compress_combine(p0, p1),
			compress_combine(p2, p3),
			compress_combine(p4, p5, value.m_index, value.m_real_size)
		);
	}
private:
	void check_not_full() {
		if (size(m_container) == m_real_size) {
			throw std::runtime_error("Tried to add too many Pokemon");
		}
	}
	constexpr void check_range(containers::index_type<PokemonCollection> const new_index [[maybe_unused]]) const {
		BOUNDED_ASSERT(new_index < containers::size(m_container));
	}

	Container m_container;
	containers::index_type<PokemonCollection> m_index = 0_bi;
	// The actual size of the foe's team, not just the Pokemon I've seen
	TeamSize m_real_size;
};

CONTAINERS_COMMON_USING_DECLARATIONS

inline auto find_index(PokemonCollection const & collection, Species const species) {
	using index_type = containers::index_type<PokemonCollection>;
	return static_cast<index_type>(containers::find_if(collection, [=](Pokemon const pokemon) { return pokemon.species() == species; }) - begin(collection));
}

inline auto find_present_index(PokemonCollection const & collection, Species const species) {
	auto const index = find_index(collection, species);
	if (index == containers::size(collection)) {
		throw PokemonNotFound(species);
	}
	return index;
}

} // namespace technicalmachine
