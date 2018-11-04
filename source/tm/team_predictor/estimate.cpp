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

#include <tm/team_predictor/estimate.hpp>

#include <tm/team_predictor/usage_stats.hpp>

#include <tm/team.hpp>

#include <containers/algorithms/accumulate.hpp>
#include <containers/algorithms/find.hpp>
#include <containers/integer_range.hpp>

#include <algorithm>
#include <cstddef>
#include <random>

namespace technicalmachine {

Estimate::Estimate(UsageStats const & usage_stats, LeadStats const lead_stats) {
	auto const & overall = usage_stats.overall();
	auto const & lead = lead_stats.get(usage_stats);
	auto const total = containers::accumulate(overall);
	for (auto const species : containers::enum_range<Species>()) {
		estimate[species] = lead[species] * static_cast<value_type>(overall[species]) / static_cast<value_type>(total);
	}
}

void Estimate::update(Multiplier const & multiplier, Team const & team) {
	for (auto const & pokemon : team.all_pokemon()) {
		update(multiplier, get_species(pokemon));
	}
}

void Estimate::update(Multiplier const & multiplier, Species const seen) {
	for (auto const predicted : containers::enum_range<Species>()) {
		estimate[predicted] *= multiplier(seen, predicted);
	}
}

Species Estimate::most_likely() const {
	auto const it = std::max_element(begin(estimate), end(estimate));
	// Estimate is indexed by Species ID. The Species ID is therefore the
	// distance between the found element and the beginning.
	return static_cast<Species>(it - begin(estimate));
}

Species Estimate::random(std::mt19937 & random_engine) const {
	auto const total = containers::accumulate(estimate);
	auto distribution = std::uniform_real_distribution<float>(0.0F, total);
	auto usage_threshold = distribution(random_engine);
	
	auto const it = containers::find_if(estimate, [=](auto const value) mutable {
		usage_threshold -= value;
		return usage_threshold <= 0.0F;
	});
	assert(it != end(estimate));
	return static_cast<Species>(it - begin(estimate));
}

}	// namespace technicalmachine