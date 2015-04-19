#include "waveloader.hpp"

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

				loadfile >> number_of_spawns;
				loaded_waves.push(WaveInfo(number_of_spawns));

				for (int j = 0; j < number_of_spawns; ++j) {
					loadfile >> spawn_length;

					for (int k = 0; k < spawn_length; ++k) {
						loadfile >> virus_id;
						loaded_waves.back().push_to(j, virus_id);
					}
				}
			}
		}

	}

	bool WaveLoader::next_wave() {
		loaded_waves.pop();
		return loaded_waves.size() > 0;
	}

	WaveInfo& WaveLoader::get_current_wave() {
		return loaded_waves.front();
	}

	const WaveInfo& WaveLoader::get_current_wave() const {
		return loaded_waves.front();
	}

}
