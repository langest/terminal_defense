#include "projectile.hpp"

namespace termd {
		
	Projectile::Projectile(char g, Coord p) : gfx(g), pos(p) {
	}

	Projectile::~Projectile(){}

	bool Projectile::draw() const {
		return GUI::draw_gfx(pos, gfx);
	}

}
