#ifndef termd_basictower_1x1
#define termd_basictower_1x1

#include <limits>

#include "towerbase.hpp"
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
			int proj_id;
		protected:

		public:
			BasicTower_1x1(Coord c, attacking_tower_base, const VirusManager&, ProjectileManager&);

			void shoot();

			virtual bool update();
	};
}
#endif //terd_basictower_1x1
