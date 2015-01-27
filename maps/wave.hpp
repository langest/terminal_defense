#ifndef termd_wave
#define termd_wave

#ifndef termd_vector
#define termd_vector
#include <vector>
#endif

#include "../coord.hpp"
#include "../virus/virus.hpp"
#include "../virus/virusloader.hpp"
#include "../virus/virusmanager.hpp"

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
