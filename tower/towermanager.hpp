#ifndef termd_tower_manager
#define termd_tower_manager

#ifndef termd_map
#define termd_map
#include <map>
#endif //termd_map

#ifndef termd_vector
#define termd_vector
#include <vector>
#endif //termd_vector

#include "../gui.hpp"
#include "../coord.hpp"
#include "../player.hpp"
#include "../definitions"
#include "../virus/virus.hpp"
#include "../virus/virusmanager.hpp"
#include "tower.hpp"
#include "wall_1x1.hpp"
#include "basic_tower_1x1.hpp"
#include "right_tower_1x1.hpp"
#include "projectiles/projectile.hpp"
#include "projectiles/projectilemanager.hpp"

namespace termd {
	
	class TowerManager {
		private:
			Player& player;

			std::map<Coord, Tower*> towers;
			const VirusManager& vman;
			ProjectileManager& pman;
		public:
			TowerManager(const VirusManager&, ProjectileManager&, Player&);
			~TowerManager();

			void update();
			void draw_towers(const GUI &);
			bool build_tower(Coord, int);
			void end_of_wave();
	};

}
#endif
