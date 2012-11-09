// Class to abstract UI of getting EVs for the team builder
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

#ifndef TEAM_PREDICTOR__UI__EV_INPUTS_HPP_
#define TEAM_PREDICTOR__UI__EV_INPUTS_HPP_

#include <FL/Fl_Int_Input.H>

namespace technicalmachine {

class EVInput {
	public:
		explicit EVInput(int button_number, int ev, char const * label = "");
		unsigned value() const;
	private:
		Fl_Int_Input input;
};

class EVInputs {
	public:
		explicit EVInputs(int button_number);
		EVInput hp;
		EVInput atk;
		EVInput def;
		EVInput spa;
		EVInput spd;
		EVInput spe;
};

}	// namespace technicalmachine
#endif	// TEAM_PREDICTOR__UI__EV_INPUTS_HPP_