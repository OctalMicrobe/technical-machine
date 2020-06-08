// Optimize offensive EVs and nature to remove waste
// Copyright (C) 2018 David Stone
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

#include <tm/pokemon/level.hpp>

#include <tm/stat/base_stats.hpp>
#include <tm/stat/calculate.hpp>
#include <tm/stat/ev.hpp>
#include <tm/stat/iv.hpp>
#include <tm/stat/nature.hpp>

#include <bounded/integer.hpp>

#include <containers/static_vector/static_vector.hpp>

namespace technicalmachine {
using namespace bounded::literal;

struct OffensiveStats {
	Nature nature;
	EV attack;
	EV special_attack;
};

struct OffensiveEVs {
	struct Input {
		IV iv;
		initial_stat_type stat;
		bool include_evs;
	};
	OffensiveEVs(BaseStats, Level, Input attack, Input special_attack);

	auto find(Nature const nature) const -> OffensiveStats const *;
private:
	containers::static_vector<OffensiveStats, size(containers::enum_range<Nature>()).value()> m_container;
};

}	// namespace technicalmachine
