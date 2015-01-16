#include "virusloader.hpp"

namespace termd {
	VirusLoader::VirusLoader() {
		std::ifstream loadfile;
		loadfile.open("virus.info");
		if(loadfile.is_open()) {
			int id;
			int hp;
			int sta_inc;
			int rew;
			char fx;

			int noTypes;
			loadfile >> noTypes;
			for(int i = 0; i < noTypes; ++i) {
				loadfile >> id;
				loadfile >> hp;
				loadfile >> sta_inc;
				loadfile >> rew;
				loadfile >> fx;
				loadedvir.insert(std::pair<int, Virus>(id, Virus(hp, sta_inc, rew, fx)));
			}
		}
	}

	Virus VirusLoader::get(int id) {
		return loadedvir[id];
	}
}