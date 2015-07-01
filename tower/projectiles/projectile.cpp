#include "projectile.hpp"

namespace termd {
		
	Projectile::Projectile(const Projectile_base & pb, Coord p) : 
	gfx(pb.gfx), 
	damage(pb.damage), 
	pos(p) {
	}

	Projectile::~Projectile(){}

	const Coord& Projectile::get_pos() const {
		return pos;
	}

	bool Projectile::draw() const {
		return GUI::draw_gfx(pos, gfx);
	}

}
