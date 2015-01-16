#ifndef termd_attacking_tower
#define termd_attacking_tower

namespace termd {
	struct tower_base {
		char gfx;
		int cost;
		int sell_value;
		int sell_decrease;
	};

	struct attacking_tower_base : public tower_base {
		int damage;
		int recharge_rate;
		int projectile_id;
	};
}
#endif