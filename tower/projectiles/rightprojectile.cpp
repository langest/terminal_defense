#include "rightprojectile.hpp"

RightProjectile::RightProjectile(Coord s, Virus& t) : Projectile(')', s) {
}

RightProjectile::~RightProjectile() {
}

void RightProjectile::move() {
	position.add_col(1);
}

Virus* RightProjectile::hit() {
	int vr, vc;
	for (Virus* vir : viruses) {
		vr = vir->get_pos().get_row();
		vc = vir->get_pos().get_col();
		if (vr == pos.get_row()) {
			if (vc == pos.get_col()) {
				return vir
			}
		}
	}
	return nullptr;
}

RightProjectile& RightProjectile::operator=(const RightProjectile & src) {
	pos = src.pos;
	target = src.target;
	speed_curr = src.speed_curr;
	speed_increment = src.speed_increment;
	gfx = src.gfx;
	return *this;
}

bool RightProjectile::update() {
	speed_curr += speed_increment;
	Virus* target = hit();
	if(target != nullptr){
		//hit target!
		//deal damage!
		target->take_damage(3);
		return false; 
	}
	move();
	target = hit();
	if(target != nullptr){
		//hit target!
		//deal damage!
		target->take_damage(3);
		return false; 
	}
	return true;
}
