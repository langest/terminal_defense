#include "homingprojectile.hpp"

HomingProjectile::HomingProjectile(Coord s, Virus& t) : pos(s), target(t), speed_curr(0), speed_increment(100), gfx('·') {
}

HomingProjectile::~HomingProjectile() {
	//TODO keep track if needed
}

HomingProjectile::HomingProjectile(const HomingProjectile & src) : pos(src.pos), target(src.target), speed_curr(src.speed_curr), speed_increment(src.speed_increment), gfx(src.gfx) {
}

HomingProjectile& HomingProjectile::operator=(const HomingProjectile & src) {
	pos = src.pos;
	target = src.target;
	speed_curr = src.speed_curr;
	speed_increment = src.speed_increment;
	gfx = src.gfx;
	return *this;
}

bool HomingProjectile::update() {
	if(pos == target.get_pos()){
		//hit target!
		//deal damage!
		return false; 
	}
	speed_curr += speed_increment;
	return true;
}
