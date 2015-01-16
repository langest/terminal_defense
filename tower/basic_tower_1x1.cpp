#include "basic_tower_1x1.hpp"

namespace termd {
		
	BasicTower_1x1::BasicTower_1x1(Coord coord, attacking_tower_base atb, const VirusManager& v, ProjectileManager& pm) : 
	Tower(coord, atb), 
	pman(pm), 
	vman(v), 
	recharge_rate(atb.recharge_rate), 
	recharge(0),
	proj_id(atb.projectile_id) {
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
			Homing_projectile_base* hp = static_cast<Homing_projectile_base*>(pman.get_projectile_base(proj_id));
			proj_ptr p(new HomingProjectile(*hp, pos, *closest));
			pman.add_projectile(std::move(p));
		}
	}

}
