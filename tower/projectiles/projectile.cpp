#include "projectile.hpp"

namespace termd {
		
	Projectile::Projectile(char g, Coord p) : gfx(g), pos(p) {
	}

	Projectile::~Projectile(){}

	bool Projectile::draw(const GUI& g) {
		return g.draw_gfx(pos, gfx);
	}

}
