#pragma once

namespace termd {

struct Projectile_base {
	char gfx;
	int damage;
	int type;

	Projectile_base(char gf, int d, int t) :
	gfx(gf),
	damage(d),
	type(t) {}
};

struct Homing_projectile_base : public Projectile_base {
	int speed_increment;

	Homing_projectile_base(char gf, int d, int t, int speed) :
	Projectile_base(gf, d, t),
	speed_increment(speed) {}
};

struct Direction_projectile_base : public Projectile_base {
	int row_spd;
	int col_spd;

	int range; //Euclidian distance that the projectile can travel

	Direction_projectile_base(char gf, int d, int t, int rs, int cs, int rng) :
	Projectile_base(gf, d, t),
	row_spd(rs),
	col_spd(cs),
	range(rng) {}
};

}
