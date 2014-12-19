#ifndef termd_basictower_1x1
#define termd_basictower_1x1

#ifndef termd_limits
#define termd_limits
include <limits>
#endif

#include "tower.hpp"
#include "../definitions"
#include "/prjectile/projectile.hpp"

class BasicTower_1x1 : public Tower {
	private:

	protected:

	public:
		BasicTower(Coord, std::vector<Virus*>&);

		void shoot();

		virtual bool update();
		virtual end_of_wave_update();
};

#endif //terd_basictower_1x1
