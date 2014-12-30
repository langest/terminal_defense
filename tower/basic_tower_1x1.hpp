#ifndef termd_basictower_1x1
#define termd_basictower_1x1

#ifndef termd_limits
#define termd_limits
#include <limits>
#endif

#include "tower.hpp"
#include "../definitions"
#include "/projectile/projectile.hpp"
#include "/projectile/homingprojectile.hpp"
#include "/projectile/projectilemanager.hpp"

class BasicTower_1x1 : public Tower {
	private:
		std::vector<Virus*>& viruses;
		ProjectileManager& projectileManager;
	protected:

	public:
		BasicTower(Coord, const std::vector<Virus*>&, ProjectileManager&);

		void shoot();

		virtual bool update();
		virtual end_of_wave_update();
};

#endif //terd_basictower_1x1
