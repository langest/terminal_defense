#ifndef termd_basictower_1x1
#define termd_basictower_1x1

#ifndef termd_limits
#define termd_limits
#include <limits>
#endif

#include "tower.hpp"
#include "../definitions"
#include "../virus/virusmanager.hpp"
#include "projectiles/projectile.hpp"
#include "projectiles/homingprojectile.hpp"
#include "projectiles/projectilemanager.hpp"

class BasicTower_1x1 : public Tower {
	private:
		ProjectileManager& pman;
		VirusManager& vman;

		int recharge_rate;
		int recharge;
	protected:

	public:
		BasicTower_1x1(Coord, VirusManager&, ProjectileManager&);

		void shoot();

		virtual bool update();
		virtual bool end_of_wave_update();
};

#endif //terd_basictower_1x1
