#include "right_tower_1x1.hpp"

namespace termd {
	
	DirectionTower_1x1::DirectionTower_1x1(Coord coord, const VirusManager& v, ProjectileManager& pm, int cs, int rs) : 
			Tower(coord, 1, 1, RIGHT_TOWER_1x1_SELL, RIGHT_TOWER_1x1_SELL_DECREASE), 
			col_spd(cs), 
			row_spd(rs), 
			pman(pm), 
			vman(v), 
			recharge_rate(RIGHT_TOWER_1x1_RECHARGE_RATE), 
			recharge(RIGHT_TOWER_1x1_RECHARGE_RATE) {
		blocking.resize(num_rows);
		blocking[0].resize(num_cols);
		blocking = {{true}};
		gfx.resize(num_rows);
		gfx[0].resize(num_cols);
		gfx = {{'D'}};
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
		Projectile* proj = new DirectionProjectile(pos, vman.get_viruses(), col_spd, row_spd);
		pman.add_projectile(proj);
	}

}
