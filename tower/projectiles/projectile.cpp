#include "projectile.hpp"

bool Projectile::draw(GUI& g) {
	return g.draw(pos, gfx);
}
