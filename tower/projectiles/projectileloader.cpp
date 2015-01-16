#include "projectileloader.hpp"

namespace termd {

	Projectile_loader::Projectile_loader() {
		std::ifstream loadfile;
		loadfile.open("tower/projectiles/projectile.info");
		if (loadfile.is_open()) {
			char gfx;
			int damage;

			for (int i = 0; i < 2; ++i) {
				loadfile >> gfx;
				loadfile >> damage;
			}
		}
	}

	Projectile_base* Projectile_loader::get_id(int id) const {
		auto it loaded_proj.find(id);
		if (it == loaded_proj.end()) {
			throw std::invalid_argument("No such projectile");
		}
		return loaded_proj;
	}

}
