#pragma once

#include <queue>
#include <string>
#include <fstream>

#include "WaveInfo.h"

namespace termd {

class WaveLoader {
	private:
		std::size_t current_wave;
		std::queue<WaveInfo> loaded_waves;
	public:
		WaveLoader(std::string info_file);

		bool next_wave(); //advances to the nextwae and returns true if such exists
		WaveInfo& get_current_wave(); //gets the current wave
		const WaveInfo& get_current_wave() const; //gets the current wave
};

}
