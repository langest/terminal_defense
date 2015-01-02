#include "basic_tower_1x1.hpp"

BasicTower_1x1::BasicTower_1x1(Coord coord, VirusManager& v, ProjectileManager& pm) : Tower(coord, 1, 1, BASIC_TOWER_1x1_SELL, BASIC_TOWER_1x1_SELL_DECREASE), pman(pm), vman(v), recharge_rate(BASIC_TOWER_1x1_RECHARGE_RATE), recharge(BASIC_TOWER_1x1_RECHARGE_RATE) {
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

bool BasicTower_1x1::end_of_wave_update() {
	sell_value *= sell_decrease;
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

	for (Virus* vir : vman.get_viruses()) {
		cur_dist = (vir->get_pos() - pos).length();
		if (cur_dist < min_dist) {
			min_dist = cur_dist;
			closest = vir;
		}
	}
	if (closest != nullptr) {
		Projectile* proj = new HomingProjectile(pos, *closest);
		pman.add_projectile(proj);
	}
}
