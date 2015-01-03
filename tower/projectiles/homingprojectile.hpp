#ifndef termd_homing_projectile
#define termd_homing_projectile

#include "projectile.hpp"

namespace termd {
	
	class HomingProjectile : public Projectile {
		private:
			Virus& target;
			int speed_increment;
			int speed_curr;

			bool hit() const;
			bool step();
			void move();

		protected:

		public:
			HomingProjectile(Coord, Virus &);
			HomingProjectile(const HomingProjectile &) = delete;
			virtual ~HomingProjectile();
			HomingProjectile& operator=(const HomingProjectile &) = delete;

			virtual bool update();
	};
}
#endif //termd_HomingProjectile
