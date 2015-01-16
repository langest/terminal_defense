#include "projectileloader.hpp"

namespace termd {

	Projectile_loader::Projectile_loader() {
		std::ifstream loadfile;
		loadfile.open("tower/projectiles/projectile.info");
		if (loadfile.is_open()) {
			int id;
			char gfx;
			int damage;
			int type;

			int noProjs;
			loadfile >> noProjs;
			for (int i = 0; i < noProjs; ++i) {
				loadfile >> id;
				loadfile >> gfx;
				loadfile >> damage;
				loadfile >> type;
				if(type == HOMING) {
					int speed;
					loadfile >> speed;
					loaded_proj.insert(
						std::pair<int, std::unique_ptr<Projectile_base> >(id, 
							std::unique_ptr<Projectile_base>(new Homing_projectile_base(gfx, damage, type, speed))));
				} else if (type == DIRECTION) {
					int col_spd;
					int row_spd;
					loadfile >> col_spd;
					loadfile >> row_spd;
					loaded_proj.insert(
						std::pair<int, std::unique_ptr<Projectile_base> >(id, 
							std::unique_ptr<Projectile_base>(new Direction_projectile_base(gfx, damage, type, col_spd, row_spd))));
				} else {
					//??
				}
			}
		}
	}

	Projectile_base* Projectile_loader::get_id(int id) const {
		auto it = loaded_proj.find(id);
		if (it == loaded_proj.end()) {
			throw std::invalid_argument("No such projectile");
		}
		return (it->second).get();
	}

}
