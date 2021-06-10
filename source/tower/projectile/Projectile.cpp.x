#include <tower/projectile/Projectile.h>

namespace termd {

Projectile::Projectile(const Projectile_base & pb, Coordinate p) :
gfx(pb.gfx),
damage(pb.damage),
pos(p) {
}

Projectile::~Projectile(){}

const Coordinate& Projectile::get_pos() const {
	return pos;
}

bool Projectile::draw() const {
	return GUI::draw_gfx(pos, gfx);
}

}
