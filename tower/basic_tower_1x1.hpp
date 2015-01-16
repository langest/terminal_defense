#ifndef termd_basictower_1x1
#define termd_basictower_1x1

#ifndef termd_limits
#define termd_limits
#include <limits>
#endif

#include "tower_base.hpp"
#include "tower.hpp"
#include "../definitions"
#include "../virus/virusmanager.hpp"
#include "projectiles/projectile.hpp"
#include "projectiles/homingprojectile.hpp"
#include "projectiles/projectilemanager.hpp"

namespace termd {

	class BasicTower_1x1 : public Tower {
		private:
			ProjectileManager& pman;
			const VirusManager& vman;

			int recharge_rate;
			int recharge;
		protected:

		public:
			BasicTower_1x1(Coord c, attacking_tower_base, const VirusManager&, ProjectileManager&);

			void shoot();

			virtual bool update();
	};
}
#endif //terd_basictower_1x1
