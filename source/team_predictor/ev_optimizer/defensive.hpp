// Optimize defensive EVs and nature to remove waste
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

#ifndef TEAM_PREDICTOR__EV_OPTIMIZER__DEFENSIVE_HPP_
#define TEAM_PREDICTOR__EV_OPTIMIZER__DEFENSIVE_HPP_

#include <map>
#include <string>
#include <vector>

#include "../../stat/nature.hpp"

namespace technicalmachine {
class Pokemon;

class DefensiveEVs {
	public:
		DefensiveEVs(Pokemon pokemon);
	private:
		class DataPoint {
			public:
				DataPoint(unsigned hp_ev, unsigned defense_ev, unsigned special_defense_ev, Nature const a_nature);
				std::string to_string() const;
				unsigned sum() const;
			private:
				unsigned hp;
				unsigned defense;
				unsigned special_defense;
				Nature nature;
		};
		class SingleClassificationEVs;
		typedef std::vector<DataPoint> Estimates;
		typedef std::map<Nature::Natures, Estimates> Container;
		typedef std::vector<SingleClassificationEVs> Single;
		void combine_results(Single const & physical, Single const & special, unsigned max_evs);
		void filter_to_minimum_evs();
		static void minimum_evs_per_nature(Estimates & original);
		Container container;
};

}	// namespace technicalmachine
#endif	// TEAM_PREDICTOR__EV_OPTIMIZER__DEFENSIVE_HPP_