#include "directionprojectile.hpp"

namespace termd {
	//Default value: cs = 1, rs = 0;
	DirectionProjectile::DirectionProjectile(const Direction_projectile_base& dp, Coord s, const std::vector<virus_ptr>& t, int cs, int rs) :
		Projectile(dp, s),
		col_spd(dp.col_spd),
		row_spd(dp.row_spd),
		viruses(t) {}

	DirectionProjectile::~DirectionProjectile() {
	}

	void DirectionProjectile::move() {
		pos.add_col(col_spd);
		pos.add_row(row_spd);
	}

	Virus* DirectionProjectile::hit() const {
		int vr, vc;
		for (auto it = viruses.begin(); it != viruses.end(); ++it) {
			vr = (*it)->get_pos().get_row();
			vc = (*it)->get_pos().get_col();
			if (vr == pos.get_row()) {
				if (vc == pos.get_col()) {
					return (*it).get();
				}
			}
		}
		return nullptr;
	}

	bool DirectionProjectile::update() {
		Virus* target = hit();
		if(target != nullptr){
			//hit target!
			//deal damage!
			target->take_damage(damage);
			return false; 
		}
		move();
		target = hit();
		if(target != nullptr){
			//hit target!
			//deal damage!
			target->take_damage(damage);
			return false; 
		}
		return true;
	}

}
