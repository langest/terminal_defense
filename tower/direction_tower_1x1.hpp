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
#include "projectiles/directionprojectile.hpp"
#include "projectiles/projectilemanager.hpp"

namespace termd {

	class DirectionTower_1x1 : public Tower {
		private:
			//Direction to shoot:
			const int col_spd;
			const int row_spd;
			ProjectileManager& pman;
			const VirusManager& vman;

			int recharge_rate;
			int recharge;
		protected:

		public:
			DirectionTower_1x1(Coord, const VirusManager&, ProjectileManager&, int, int);

			void shoot();

			virtual bool update();
			virtual int get_id() const { return RIGHT_TOWER_1x1_ID;};
	};

}

#endif //termd_righttower_1x1
