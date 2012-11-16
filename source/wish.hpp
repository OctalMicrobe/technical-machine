// Wish data structure
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

#ifndef WISH_HPP_
#define WISH_HPP_

#include <cstdint>

namespace technicalmachine {
class Pokemon;

class Wish {
	public:
		Wish();
		void activate();
		void decrement(Pokemon & pokemon);
		typedef uint64_t hash_type;
		hash_type hash() const;
		static hash_type max_hash();
		friend bool operator== (Wish lhs, Wish rhs);
	private:
		bool is_active() const;
		uint8_t counter;
		friend class Evaluate;
};

bool operator!= (Wish lhs, Wish rhs);

}	// namespace technicalmachine
#endif	// WISH_HPP_
