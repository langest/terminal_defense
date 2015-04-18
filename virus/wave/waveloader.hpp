#ifndef termd_wave_loader
#define termd_wave_loader

#include <vector>
#include <string>
#include <fstream>

#include "waveinfo.hpp"

namespace termd {
	class Wave_loader {
		private:
			size_t current_wave;
			std::vector<Wave_info> loaded_waves;
		public:
			Wave_loader(std::string info_file);

			bool has_next() const;
			const Wave_info& get_next_wave(); //gets the next wave and increments current wave
	};
}

#endif
