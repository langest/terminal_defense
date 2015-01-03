#ifndef termd_righttower_1x1
#define termd_righttower_1x1

#ifndef termd_limits
#define termd_limits
#include <limits>
#endif

#include "tower.hpp"
#include "../definitions"
#include "../virus/virusmanager.hpp"
#include "projectiles/projectile.hpp"
#include "projectiles/rightprojectile.hpp"
#include "projectiles/projectilemanager.hpp"

namespace termd {

	class RightTower_1x1 : public Tower {
		private:
			ProjectileManager& pman;
			VirusManager& vman;

			int recharge_rate;
			int recharge;
		protected:

		public:
			RightTower_1x1(Coord, VirusManager&, ProjectileManager&);

			void shoot();

			virtual bool update();
	};

}

#endif //termd_righttower_1x1
