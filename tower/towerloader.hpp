#ifndef termd_tower_loader
#define termd_tower_loader

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

#ifndef termd_memory
#define termd_memory
#include <memory>
#endif

#ifndef termd_map
#define termd_map
#include <map>
#endif

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
