#include "basic_tower_1x1.hpp"

namespace termd {
		
	BasicTower_1x1::BasicTower_1x1(Coord coord, const VirusManager& v, ProjectileManager& pm) : Tower(coord, 1, 1, BASIC_TOWER_1x1_SELL, BASIC_TOWER_1x1_SELL_DECREASE), pman(pm), vman(v), recharge_rate(BASIC_TOWER_1x1_RECHARGE_RATE), recharge(BASIC_TOWER_1x1_RECHARGE_RATE) {
		blocking.resize(num_rows);
		blocking[0].resize(num_cols);
		blocking = {{true}};
		gfx.resize(num_rows);
		gfx[0].resize(num_cols);
		gfx = {{'i'}};
	}

	bool BasicTower_1x1::update() {
		shoot();
		return true;
	}

	void BasicTower_1x1::shoot() {
		if (recharge > 0) {
			--recharge;
			return;
		}
		recharge = recharge_rate;
		Virus* closest = nullptr;
		float min_dist = std::numeric_limits<float>::max();
		float cur_dist;

		std::vector<virus_ptr>::const_iterator vir;
		for (vir = vman.get_viruses().begin(); vir != vman.get_viruses().end(); ++vir) {
			cur_dist = ((*vir)->get_pos() - pos).length();
			if (cur_dist < min_dist) {
				min_dist = cur_dist;
				closest = (*vir).get();
			}
		}

		if (closest != nullptr) {
			proj_ptr p(new HomingProjectile('\'', pos, *closest, 1500, 1));
			pman.add_projectile(std::move(p));
		}
	}

}
