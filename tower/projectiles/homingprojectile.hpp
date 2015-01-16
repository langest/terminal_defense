#ifndef termd_homing_projectile
#define termd_homing_projectile

#include "projectile.hpp"

namespace termd {
	
	class HomingProjectile : public Projectile {
		private:
			Virus& target;
			int speed_increment;
			int speed_curr;
			int damage;

			bool hit() const;
			bool step();
			void move();

		protected:

		public:
			HomingProjectile(char gfx, Coord start, Virus& target, int speed, int damage);
			HomingProjectile(const HomingProjectile &) = delete;
			virtual ~HomingProjectile();
			HomingProjectile& operator=(const HomingProjectile &) = delete;

			virtual bool update();
	};
}
#endif //termd_HomingProjectile
