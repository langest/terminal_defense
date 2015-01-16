#ifndef termd_projectile_base
#define termd_projectile_base

namespave termd {
	struct proj_base {
		char gfx;
	};

	struct homing_proj_base : proj_base {
		int speed_increment;
		int damage;
	};
}

#endif
