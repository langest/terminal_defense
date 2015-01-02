#include "projectile.hpp"

Projectile::Projectile(char g, Coord p) : gfx(g), pos(p) {

}

bool Projectile::draw(GUI& g) {
	return g.draw(pos, gfx);
}
