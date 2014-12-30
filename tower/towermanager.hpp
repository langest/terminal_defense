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
#include "tower.hpp"
#include "wall_1x1.hpp"
#include "projectiles/projectile.hpp"
#include "../virus/virus.hpp"


class TowerManager {
	private:
		std::map<Coord, Tower*> towers;
		std::vector<Virus*>& viruses;
		std::vector<Projectile*>& projectiles;
	public:
		TowerManager(std::vector<Virus*>&, std::vector<Projectile*>&);
		~TowerManager();

		void update();
		void draw_towers(GUI &);
		void build_tower(Coord, int);
};

#endif
