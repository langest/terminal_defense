#include "virusloader.hpp"

namespace termd {
	VirusLoader::VirusLoader() {
		std::ifstream loadfile;
		loadfile.open("info/virus.info");
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
				Virus v(hp, sta_inc, rew, fx);
				loadedvir.insert(std::pair<int, Virus>(id, v));
			}
			loadfile.close();
		}
	}

	Virus* VirusLoader::get(int id) {
		auto ptr(loadedvir.find(id));
		if(ptr == loadedvir.end()) {
			throw std::invalid_argument ("No such virus");
		}
		return &(ptr->second);
	}
}
