#ifndef termd_projectile_loader
#define termd_projectile_loader

#include <exception>
#include <fstream>
#include <memory>
#include <map>

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
