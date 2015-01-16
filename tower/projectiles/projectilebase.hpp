#ifndef termd_projectile_base
#define termd_projectile_base

namespave termd {
	struct Projectile_base {
		char gfx;
		int damage;
	};

	struct homing_projectile_base : projectile_base {
		int speed_increment;
	};

	struct direction_projectile_base : projectile_base {
		int col_spd;
		int row_spd;
	};
}

#endif
