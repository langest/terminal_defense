#include "direction_tower_1x1.hpp"

namespace termd {
	
	DirectionTower_1x1::DirectionTower_1x1(Coord coord, attacking_tower_base atb, const VirusManager& v, ProjectileManager& pm) : 
			Tower(coord, atb), 
			pman(pm), 
			vman(v), 
			recharge_rate(atb.recharge_rate), 
			recharge(0)
			proj_id(atb.projectile_id) {
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
		Direction_projectile_base* dp = static_cast<Direction_projectile_base*>(pm.get_projectile_base(proj_id));
		proj_ptr proj(new DirectionProjectile(*dp, pos, vman.get_viruses()));
		pman.add_projectile(std::move(proj));
	}

}
