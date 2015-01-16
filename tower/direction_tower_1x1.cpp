#include "direction_tower_1x1.hpp"

namespace termd {
	
	DirectionTower_1x1::DirectionTower_1x1(Coord coord, attacking_tower_base atb, const VirusManager& v, ProjectileManager& pm) : 
			Tower(coord, atb), 
			pman(pm), 
			vman(v), 
			recharge_rate(atb.recharge_rate), 
			recharge(0) {
	}

	bool DirectionTower_1x1::update() {
		shoot();
		return true;
	}

	void DirectionTower_1x1::shoot() {
		if (recharge > 0) {
			--recharge;
			return;
		}
		recharge = recharge_rate;
		proj_ptr proj(new DirectionProjectile(pos, vman.get_viruses(), 1, 0));
		pman.add_projectile(std::move(proj));
	}

}
