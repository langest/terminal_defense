#include "homingprojectile.hpp"

namespace termd {
	
	HomingProjectile::HomingProjectile(char gfx, Coord s, Virus& t, int spd, int dmg) :
		Projectile(gfx, s),
		target(t),
		speed_increment(spd),
		speed_curr(0),
		damage(dmg)	{
	}

	HomingProjectile::~HomingProjectile() {
		//TODO keep track if needed
	}

	void HomingProjectile::move() {
		while (step());
	}

	bool HomingProjectile::hit() const {
		return pos == target.get_pos();
	}

	bool HomingProjectile::step() {
		if (hit()) return false; //We already reached the target

		Coord delta = target.get_pos() - pos;

		double angle = atan2(delta.get_row(), delta.get_col()) * -180 / PI;
		angle = (angle > 0 ? angle : (360.0 + angle));

		if (angle < 45.0f/2.0f) { //go right
			if (speed_curr >= PROJ_STEPCOST) {
				speed_curr -= PROJ_STEPCOST;
				pos.add_col(1);
				return true;
			}
		} else if (angle < 45.0f+45.0f/2.0f) { //go up right
			if (speed_curr >= PROJ_STEPCOSTDIAGONAL) {
				speed_curr -= PROJ_STEPCOSTDIAGONAL;
				pos.add_col(1);
				pos.add_row(-1);
				return true;
			}
		} else if (angle < 2*45.0f+45.0f/2.0f) { //go up
			if (speed_curr >= PROJ_STEPCOST) {
				speed_curr -= PROJ_STEPCOST;
				pos.add_row(-1);
				return true;
			}
		} else if (angle < 3*45.0f+45.0f/2.0f) { //go up left
			if (speed_curr >= PROJ_STEPCOSTDIAGONAL) {
				speed_curr -= PROJ_STEPCOSTDIAGONAL;
				pos.add_col(-1);
				pos.add_row(-1);
				return true;
			}
		} else if (angle < 4*45.0f+45.0f/2.0f) { //go left
			if (speed_curr >= PROJ_STEPCOST) {
				speed_curr -= PROJ_STEPCOST;
				pos.add_col(-1);
				return true;
			}
		} else if (angle < 5*45.0f+45.0f/2.0f) { //go down left
			if (speed_curr >= PROJ_STEPCOSTDIAGONAL) {
				speed_curr -= PROJ_STEPCOSTDIAGONAL;
				pos.add_col(-1);
				pos.add_row(1);
				return true;
			}
		} else if (angle < 6*45.0f+45.0f/2.0f) { //go down
			if (speed_curr >= PROJ_STEPCOST) {
				speed_curr -= PROJ_STEPCOST;
				pos.add_row(1);
				return true;
			}
		} else if (angle < 7*45.0f+45.0f/2.0f) { //go down right
			if (speed_curr >= PROJ_STEPCOSTDIAGONAL) {
				speed_curr -= PROJ_STEPCOSTDIAGONAL;
				pos.add_col(1);
				pos.add_row(1);
				return true;
			}
		} else { //go right
			if (speed_curr >= PROJ_STEPCOST) {
				speed_curr -= PROJ_STEPCOST;
				pos.add_col(1);
				return true;
			}
		}
		return false;
	}

	bool HomingProjectile::update() {
		speed_curr += speed_increment;
		move();
		if(hit()){
			//hit target!
			//deal damage!
			target.take_damage(damage);
			return false; 
		}
		return true;
	}
}
