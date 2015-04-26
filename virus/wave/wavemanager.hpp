#ifndef termd_wave
#define termd_wave

#include <vector>
#include <string>
#include <algorithm>

#include "waveloader.hpp"
#include "../../definitions"
#include "../../coord.hpp"
#include "../virus.hpp"
#include "../virusloader.hpp"
#include "../virusmanager.hpp"

namespace termd {

	class WaveManager {
		private:
			WaveLoader wave_loader;
			VirusLoader virus_loader;
			VirusManager& vman;

			int size_r;
			int size_c;
			const std::vector<std::vector<bool> > & towers;
			unsigned int timer;
		public:
			WaveManager(int sizer, int sizec, const std::vector<std::vector<bool> >& towers, std::string wave_info_file, VirusManager&);

			//Starts a new wave if one is available
			//returns true if a wave is available
			//else false
			bool spawn();
			bool update();
	};
}

#endif
