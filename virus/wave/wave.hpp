#ifndef termd_wave
#define termd_wave

#ifndef termd_vector
#define termd_vector
#include <vector>
#endif

#ifndef termd_random
#define termd_random
#include <random>
#endif

#include "../../coord.hpp"
#include "../virus.hpp"
#include "../virusloader.hpp"
#include "../virusmanager.hpp"

namespace termd {

	class Wave {
		private:
		VirusLoader virus_loader;
		VirusManager& vman;
		//TODO definition of waves
		public:
			Wave(VirusManager&);
			void spawn(int wave, int size_r, int size_c, const std::vector<std::vector<bool> > & towers);
	};

}

#endif