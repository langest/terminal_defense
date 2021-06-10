#include <tower/projectile/HomingProjectile.h>

namespace termd {

HomingProjectile::HomingProjectile(const Homing_projectile_base & hp, Coordinate s, Virus& t) :
	Projectile(hp, s),
	target(t),
	speed_increment(hp.speed_increment),
	speed_curr(0) {
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
	if (speed_curr < ProjStepCost) return false; // We cannot move and are done

	Coordinate delta = target.get_pos() - pos;

	int row_dist = std::abs(delta.get_row());
	int col_dist = std::abs(delta.get_col());
	int diag_dist = std::min(row_dist, col_dist);

	if (std::max(row_dist, col_dist) - diag_dist >= diag_dist) { // We want to move horizonally or vertically
		if (row_dist < col_dist) { // Check if we have most rows or cols left
			if (diag_dist <= col_dist) {// We should step in col
				// Remove speed since we are going to step
				speed_curr -= ProjStepCost;
				if (delta.get_col() < 0) { // Check which dir we should step
					pos.add_col(-1);
					return true;
				}
				pos.add_col(1);
				return true;
			}
		} else { // col_dist < row_dist
			if (diag_dist <= row_dist) {
				// Remove speed since we are going to step
				speed_curr -= ProjStepCost;
				if (delta.get_row() < 0) {// Check which dir we should step
					pos.add_row(-1);
					return true;
				}
				pos.add_row(1);
				return true;
			}
		}
	}
	if (speed_curr < ProjStepCostDiagonal) return false; // We cannot diagonally and are done
	//Remove speed since we are goind to step
	speed_curr -= ProjStepCostDiagonal;

	if (delta.get_row() < 0) {
		pos.add_row(-1);
	} else { //delta.get_row >= 0
		pos.add_row(1);
	}
	if (delta.get_col() < 0) {
		pos.add_col(-1);
	} else {
		pos.add_col(1);
	}

	return true;
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
