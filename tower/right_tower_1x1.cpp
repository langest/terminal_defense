#include "right_tower_1x1.hpp"

RightTower_1x1::RightTower_1x1(Coord coord, VirusManager& v, ProjectileManager& pm) : Tower(coord, 1, 1, RIGHT_TOWER_1x1_SELL, RIGHT_TOWER_1x1_SELL_DECREASE), pman(pm), vman(v), recharge_rate(RIGHT_TOWER_1x1_RECHARGE_RATE), recharge(RIGHT_TOWER_1x1_RECHARGE_RATE) {
	blocking.resize(num_rows);
	blocking[0].resize(num_cols);
	blocking = {{true}};
	gfx.resize(num_rows);
	gfx[0].resize(num_cols);
	gfx = {{'D'}};
}

bool RightTower_1x1::update() {
	shoot();
	return true;
}

bool RightTower_1x1::end_of_wave_update() {
	sell_value *= sell_decrease;
	return true;
}

void RightTower_1x1::shoot() {
	if (recharge > 0) {
		--recharge;
		return;
	}
	recharge = recharge_rate;
	Virus* closest = nullptr;
	int min_dist = INT_MAX;
	int cur_dist;

	for (Virus* vir : vman.get_viruses()) {
		if(vir->get_pos().get_row() == pos.get_row() && vir->get_pos().get_col() > pos.get_col(){
			//If same row and to the right:
			cur_dist = vir->get_pos().get_col() - pos.get_col();
			if (cur_dist < min_dist) {
				//Get closest virus:
				min_dist = cur_dist;
				closest = vir;
			}
		}
	}
	if (closest != nullptr) {
		Projectile* proj = new HomingProjectile(pos, *closest);
		pman.add_projectile(proj);
	}
}
