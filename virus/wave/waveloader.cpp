#include "waveloader.hpp"

#include "../../gui.hpp" //TODO remove line
#include <sstream>
namespace termd {

	WaveLoader::WaveLoader(std::string info_file) : current_wave(0) {
		std::ifstream loadfile;
		loadfile.open(info_file);
		if (loadfile.is_open()) {
			int number_of_waves;
			loadfile >> number_of_waves;

			int number_of_spawns;
			int spawn_length;
			int virus_id;
			for (int i = 0; i < number_of_waves; ++i) {
				GUI::print_intel(std::string("loop Start"));
				GUI::get_input();

				loadfile >> number_of_spawns;

				GUI::print_intel(std::string("Pause 1   "));
				GUI::get_input();

				std::string s = std::to_string(loaded_waves.size());
				GUI::print_intel(std::string(s));
				GUI::get_input();
				loaded_waves.push_back(WaveInfo(number_of_spawns));
				s = std::to_string(loaded_waves.size());
				GUI::print_intel(std::string(s));
				GUI::get_input();

				GUI::print_intel(std::string("Pause 2   "));
				GUI::get_input();

				for (int j = 0; j < number_of_spawns; ++j) {
					loadfile >> spawn_length;

					for (int k = 0; k < spawn_length; ++k) {
						loadfile >> virus_id;
						loaded_waves.back()[i].push_back(virus_id);
					}
				}
				GUI::print_intel(std::string("loop End  "));
				GUI::get_input();
			}
				GUI::print_intel(std::string("Finished loop"));
				GUI::get_input();
		}
				//TODO remove debugging
		/*
				std::ostringstream s;
				s << virus_id;
				const std::string i_as_string(s.str());
				GUI::print_intel(std::string(i_as_string));
				GUI::get_input();
				*/

	}

	bool WaveLoader::next_wave() {
		if (current_wave < loaded_waves.size()) {
			++current_wave;
			return true;
		}
		return false;
	}

	const WaveInfo& WaveLoader::get_current_wave() const {
		return loaded_waves[current_wave];
	}

}
