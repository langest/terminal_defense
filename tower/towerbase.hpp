#ifndef termd_tower_base
#define termd_tower_base

namespace termd {
	struct tower_base {
		int id;
		char gfx;
		int cost;
		int sell_value;
		float sell_decrease;
		int type;

		tower_base(int i, char gf, int c, int sv, float sd, int t) : 
		id(i),
		gfx(gf),
		cost(c),
		sell_value(sv),
		sell_decrease(sd), 
		type(t) {}
	};

	struct attacking_tower_base : public tower_base {
		int recharge_rate;
		int projectile_id;

		attacking_tower_base(int i, char gf, int c, int sv, float sd, int type, int rr, int pid) : 
		tower_base(i, gf, c, sv, sd, type),
		recharge_rate(rr),
		projectile_id(pid) {}

		attacking_tower_base(const attacking_tower_base & src) : 
		tower_base(src.id, src.gfx, src.cost, src.sell_value, src.sell_decrease, src.type),
		recharge_rate(src.recharge_rate),
		projectile_id(src.projectile_id)
		{}
	};
}
#endif