#include "projectile.hpp"

Projectile::Projectile(Coord s, Coort t) : pos(s), target(t), speed_curr(0), speed_increment(100), gfx('·') {
}

Projectile::~Projectile() {
	//TODO keep track if needed
}

Projectile::Projectile(const Projectile & src) : pos(src.pos), target(src.target), speed_curr(src.speed_curr), speed_increment(src.speed_increment), gfx(src.gfx) {
}

Projectile& Projectile::operator=(const Projectile & src) {
	pos = src.pos;
	target = src.target;
	speed_curr = src.speed_curr;
	speed_increment = src.speed_increment;
	gfx = src.gfx;
	return *this;
}

bool Projectile::update() {
	if(pos == target){
		return false; //hit target!
	}
	speed_curr += speed_increment;
	return true;
}

bool Projectile::draw(GUI& g) {
	return g.draw(pos, gfx);
}