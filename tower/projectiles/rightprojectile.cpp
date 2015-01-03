#include "rightprojectile.hpp"

namespace termd {
		
	RightProjectile::RightProjectile(Coord s, const std::vector<Virus*>& t) : Projectile(')', s), viruses(t) {
	}

	RightProjectile::~RightProjectile() {
	}

	void RightProjectile::move() {
		pos.add_col(1);
	}

	Virus* RightProjectile::hit() {
		int vr, vc;
		for (Virus* vir : viruses) {
			vr = vir->get_pos().get_row();
			vc = vir->get_pos().get_col();
			if (vr == pos.get_row()) {
				if (vc == pos.get_col()) {
					return vir;
				}
			}
		}
		return nullptr;
	}

	bool RightProjectile::update() {
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

}
