#ifndef termd_tower_manager
#define termd_tower_manager

#include <map>
#include <vector>

#include "../gui.hpp"
#include "../coord.hpp"
#include "../player.hpp"
#include "../constants.h"
#include "../virus/virus.hpp"
#include "../virus/virusmanager.hpp"
#include "tower.hpp"
#include "towerloader.hpp"
#include "wall_1x1.hpp"
#include "basic_tower_1x1.hpp"
#include "direction_tower_1x1.hpp"
#include "projectiles/projectile.hpp"
#include "projectiles/projectilemanager.hpp"

namespace termd {
	
	class TowerManager {
		private:
			Tower_loader tl;

			Player& player;

			std::map<Coord, tower_ptr> towers;
			const VirusManager& vman;
			ProjectileManager& pman;
		public:
			TowerManager(const VirusManager&, ProjectileManager&, Player&);
			~TowerManager();

			void update();
			void draw_towers() const;
			void end_of_wave();

			Tower* get(Coord) const;

			//This function assumes that coord is inside the game area.
			//Check is done in gameboard where the dimensions are available.
			bool build_tower(Coord, int); //Tries to build a tower (player has to pay if successfull)
			bool place_tower(Coord, int); //Tries to place a tower at the location

			bool save_to_file(std::string filename);
			bool load_from_file(std::string filename);
	};

}
#endif
