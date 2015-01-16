#include "towerloader.hpp"

namespace termd {
	Tower_loader::Tower_loader() {
		std::ifstream loadfile;
		loadfile.open("tower.info");
		if(loadfile.is_open()) {
			int id;
			char fx;
			int cost;
			int sell_val;
			float sell_dec;
			int type;
			bool is_attacking;
			int recharge_rate;
			int projectile_id;

			int noTypes;
			loadfile >> noTypes;
			for(int i = 0; i < noTypes; ++i) {
				loadfile >> id;
				loadfile >> fx;
				loadfile >> cost;
				loadfile >> sell_val;
				loadfile >> sell_dec;
				loadfile >> type;
				loadfile >> is_attacking;
				if(is_attacking) {
					loadfile >> recharge_rate;
					loadfile >> projectile_id;
					loadedtow.insert(
						std::pair<int, std::unique_ptr<tower_base> >(id, std::unique_ptr<tower_base>(new attacking_tower_base(id, fx, cost, sell_val, sell_dec, type, recharge_rate, projectile_id))));
				} else {
					loadedtow.insert(
						std::pair<int, std::unique_ptr<tower_base> >(id, std::unique_ptr<tower_base>(new tower_base(
						id, fx, cost, sell_val, sell_dec, type))));

				}
			}
		}
	}

	tower_base* Tower_loader::get(int id) {
		auto ptr(loadedtow.find(id));
		if(ptr == loadedtow.end()) {
			throw std::invalid_argument ("No such tower");
		}
		return ptr->second.get();
	}
}