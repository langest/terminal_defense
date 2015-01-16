#ifndef termd_righttower_1x1
#define termd_righttower_1x1

#ifndef termd_limits
#define termd_limits
#include <limits>
#endif

#include "towerbase.hpp"
#include "tower.hpp"
#include "../definitions"
#include "../virus/virusmanager.hpp"
#include "projectiles/projectile.hpp"
#include "projectiles/directionprojectile.hpp"
#include "projectiles/projectilemanager.hpp"

namespace termd {

	class DirectionTower_1x1 : public Tower {
		private:
			//Direction to shoot:
			ProjectileManager& pman;
			const VirusManager& vman;

			int recharge_rate;
			int recharge;
		protected:

		public:
			DirectionTower_1x1(Coord, attacking_tower_base, const VirusManager&, ProjectileManager&);

			void shoot();

			virtual bool update();
	};

}

#endif //termd_righttower_1x1
