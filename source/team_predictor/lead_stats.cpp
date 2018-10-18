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

#include "lead_stats.hpp"
#include "usage_stats.hpp"

#include <containers/array/make_array.hpp>

namespace technicalmachine {

auto LeadStats::get(UsageStats const & usage_stats) const -> containers::array<float, number_of_species> const & {
	static constexpr auto unused_lead = containers::make_array_n(bounded::constant<number_of_species>, 1.0F);
	return m_use_lead_stats ? usage_stats.lead() : unused_lead;
}

} // namespace technicalmachine
