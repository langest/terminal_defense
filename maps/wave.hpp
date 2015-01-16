#ifndef termd_wave
#define termd_wave

#include "../coord.hpp"
#include "../virus/virus.hpp"
#include "../virus/virusmanager.hpp"

namespace termd {

	class Wave {
		private:
		VirusLoader virus_loader;
		VirusManager& vman;
		//TODO definition of waves
		public:
			Wave(VirusManager&);
			void spawn();
	};

}

#endif
