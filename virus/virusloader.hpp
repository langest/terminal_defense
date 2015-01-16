#ifndef termd_virus_loader
#define termd_virus_loader

#ifndef termd_string
#define termd_string
#include <string>
#endif

#ifndef termd_exception
#define termd_exception
#include <stdexcept>
#endif

#ifndef termd_fstream
#define termd_fstream
#include <fstream>
#endif

#ifndef termd_map
#define termd_map
#include <map>
#endif

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
