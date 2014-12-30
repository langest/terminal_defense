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
#include "../definitions"
#include "../virus/virus.hpp"
#include "../virus/virusmanager.hpp"
#include "tower.hpp"
#include "wall_1x1.hpp"
#include "projectiles/projectile.hpp"
#include "projectiles/projectilemanager.hpp"


class TowerManager {
	private:
		std::map<Coord, Tower*> towers;
		VirusManager& viruses;
		ProjectileManager& projectiles;
	public:
		TowerManager(VirusManager&, ProjectileManager&);
		~TowerManager();

		void update();
		void draw_towers(GUI &);
		void build_tower(Coord, int);
};

#endif
