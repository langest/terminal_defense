#ifndef termd_virus_loader
#define termd_virus_loader

#include <string>
#include <stdexcept>
#include <fstream>
#include <map>

#include "virus.hpp"

namespace termd {
	class VirusLoader {
	private:
		std::map<int, Virus> loadedvir;
	public:
		VirusLoader();

		Virus* get(int);
	};
}

#endif
