#ifndef termd_tower_loader
#define termd_tower_loader

#include <string>
#include <stdexcept>
#include <fstream>
#include <memory>
#include <map>
#include <vector>

#include "towerbase.hpp"
#include "tower.hpp"

namespace termd {
	class Tower_loader {
	private:
		std::map<int, std::unique_ptr<tower_base> > loadedtow;
	public:
		Tower_loader();

		tower_base* get(int);
		std::vector<int> id_list();
	};
}

#endif
