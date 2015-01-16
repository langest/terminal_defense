#ifndef termd_projectile_loader
#define termd_projectile_loader

#ifndef termd_exception
#define termd_exception
#include <exception>
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

#include "../../definitions"
#include "projectilebase.hpp"

namespace termd {
	class Projectile_loader {
		private:
			std::map<int, std::unique_ptr<Projectile_base> > loaded_proj;
		public:
			Projectile_loader();

			//Throws exception if id is not defined
			Projectile_base* get_id(int) const;
	};
}

#endif
