#ifndef termd_wave_loader
#define termd_wave_loader

#include <vector>
#include <string>
#include <fstream>

#include "waveinfo.hpp"

namespace termd {
	class WaveLoader {
		private:
			std::size_t current_wave;
			std::vector<WaveInfo> loaded_waves;
		public:
			WaveLoader(std::string info_file);

			bool next_wave();
			const WaveInfo& get_current_wave() const; //gets the current wave 
	};
}

#endif
