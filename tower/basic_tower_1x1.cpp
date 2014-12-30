#include "basic_tower_1x1.hpp"

BasicTower::BasicTower(Coord coord, std::vector<Virus*>& v, ProjectileManager& pm) : projectileManager(pm), viruses(v), num_rows(1), num_cols(1), pos(coord), sell_value(BASICTOWER_1x1_SELL), sell_decrease(BASICTOWER_1x1_SELL_DECREASE) {
	blocking.resize(num_rows);
	blocking[0].resize(num_cols);
	blocking = {{true}};
	gfx.resize(num_rows);
	gfx[0].resize(num_cols);
	gfx = {{'i'}};
}

bool BasicTower::update() {
	shoot();
	return true;
}

bool BasicTower::end_of_wave_update() {
		sell_value *= sell_decrease;
		true;
}

void BasicTower::shoot() {
	Virus* closest = nullptr;
	float min_dist = std::numeric_limits<float>::max();
	float cur_dist;

	for (Virus* vir : viruses) {
		cur_dist = (vir->get_pos() - pos).length();
		if (cur_dist < min_dist) {
			min_dist = cur_dist;
			closest = vir;
		}
	}
	if (closest != nullptr) {
		Projectile* proj = new HomingProjectile(pos, *closest);
		projectileManager.add_projectile(proj);
	}
}
