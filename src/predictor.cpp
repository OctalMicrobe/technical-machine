// Predict foe's team
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

#include <random>
#include <string>
#include <vector>

#include "string_conversions/invalid_string_conversion.hpp"
#include "load_stats.hpp"
#include "pokemon.hpp"
#include "team.hpp"
#include "teampredictor.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Output.H>

using namespace technicalmachine;

// A GUI version of the team predictor.

class Data {
	public:
		std::vector<Fl_Input *> input;
		Fl_Multiline_Output * output;
		int detailed [Species::END][7];
		std::mt19937 random_engine;
};

void function (Fl_Widget * w, void * d) {
	Data & data = *reinterpret_cast <Data *> (d);
	
	constexpr bool is_me = false;
	Team team (is_me, 6, data.random_engine);
	bool using_lead;
	for (Fl_Input * in : data.input) {
		Species species;
		try {
			species = Pokemon::from_string (in->value());
		}
		catch (InvalidFromStringConversion const & ex) {
			species = Species::END;
		}
		if (in == data.input.front ()) {
			using_lead = (species != Species::END);
		}
		if (species != Species::END) {
			Pokemon member (species, team.size);
			team.pokemon.set.push_back (member);
		}
	}
	
	if (team.pokemon.set.size() > 0) {
		predict_team (data.detailed, team, using_lead);
		data.output->value (team.to_string().c_str());
	}
	else
		data.output->value ("");
}

int main () {
	Fl_Window win (520, 730, "Team Predictor");
		Fl_Input input0 (50, 10, 120, 30, "Input");
		Fl_Input input1 (50, 50, 120, 30);
		Fl_Input input2 (50, 90, 120, 30);
		Fl_Input input3 (50, 130, 120, 30);
		Fl_Input input4 (50, 170, 120, 30);
		Fl_Input input5 (50, 210, 120, 30);
		Fl_Return_Button calculate (50, 250, 120, 30, "Calculate");
		Fl_Multiline_Output output (250, 10, 260, 710, "Output");
	win.end();

	Data data;
	detailed_stats (data.detailed);
	
	data.input.push_back (&input0);
	data.input.push_back (&input1);
	data.input.push_back (&input2);
	data.input.push_back (&input3);
	data.input.push_back (&input4);
	data.input.push_back (&input5);
	data.output = &output;

	calculate.callback (function, &data);
	win.show();

	return Fl::run();
}
