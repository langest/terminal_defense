#include "waveloader.hpp"

namespace termd {

	Wave_loader::Wave_loader(std::string info_file) : current_wave(0) {
		std::ifstream loadfile;
		loadfile.open(info_file);
		if (loadfile.is_open()) {
			int number_of_waves;
			loadfile >> number_of_waves;

			int number_of_spawns;
			int spawn_length;
			int virus_id;
			for (int i = 0; i < number_of_waves; ++i) {
				loadfile >> number_of_spawns;
				Wave_info wi(number_of_spawns);

				for (int j = 0; j < number_of_spawns; ++j) {
					loadfile >> spawn_length;
					for (int k = 0; k < spawn_length; ++k) {
						loadfile >> virus_id;
						wi[i].push_back(virus_id);
					}
				}
				loaded_waves.push_back(wi);
			}
		}
	}

	bool Wave_loader::has_next() const {
		return current_wave < loaded_waves.size();
	}

	const Wave_info& Wave_loader::get_next_wave() {
		return loaded_waves[current_wave++];
	}

}
