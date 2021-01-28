#pragma once

#include <cstdlib>
#include <tower/projectile/ProjectileBase.h>
#include <tower/projectile/Projectile.h>

namespace termd {

class HomingProjectile : public Projectile {
	private:
		Virus& target;
		int speed_increment;
		int speed_curr;

		bool hit() const;
		bool step(); // returns true iff projectile steped
		void move();

	protected:

	public:
		HomingProjectile(const Homing_projectile_base &, Coordinate start, Virus& target);
		HomingProjectile(const HomingProjectile &) = delete;
		virtual ~HomingProjectile();
		HomingProjectile& operator=(const HomingProjectile &) = delete;

		virtual bool update();
};

}
