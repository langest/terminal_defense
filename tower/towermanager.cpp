#include "towermanager.hpp"

namespace termd {
		
	TowerManager::TowerManager(const VirusManager& v, ProjectileManager& pm, Player& p) : player(p), vman(v), pman(pm) {

	}

	TowerManager::~TowerManager() {
		for (auto i = towers.begin(); i != towers.end(); ++i) {
			delete i->second;
		}
	}

	void TowerManager::update() {
		for (auto i = towers.begin(); i != towers.end(); ) {
			if(i->second->update() == false) {
				//If tower is flagging removal, remove it!
				delete i->second;
				i = towers.erase(i);
			}else{
				++i;
			}
		}
	}

	bool TowerManager::build_tower(Coord c, int tower_id) {
		switch(tower_id){ 
			case WALL_1x1_ID: 
				if(player.get_ram() >= WALL_1x1_COST){
					if(place_tower(c, tower_id) == true) {
						player.modify_ram(-WALL_1x1_COST);
						return true;
					}
				}
				break;
			case BASIC_TOWER_1x1_ID: 
				if(player.get_ram() >= BASIC_TOWER_1x1_COST){
					if(place_tower(c, tower_id) == true) {
						player.modify_ram(-BASIC_TOWER_1x1_COST);
						return true;
					}
				}
				break;
			case RIGHT_TOWER_1x1_ID:
				if(player.get_ram() >= RIGHT_TOWER_1x1_COST){
					if(place_tower(c, tower_id) == true) {
						player.modify_ram(-RIGHT_TOWER_1x1_COST);
						return true;
					}
				}
				break;
		}
		return false;
	}

	bool TowerManager::place_tower(Coord c, int tower_id) {
		if(towers.find(c) != towers.end()) {
			//space taken by other tower!
			return false;
		}
		switch(tower_id){ 
			case WALL_1x1_ID: 
				towers.insert( std::pair<Coord, Tower*>(c, new Wall_1x1(c)));
				return true;
			case BASIC_TOWER_1x1_ID: 
				towers.insert( std::pair<Coord, Tower*>(c, new BasicTower_1x1(c, vman, pman)));
				return true;
			case RIGHT_TOWER_1x1_ID: 
				towers.insert( std::pair<Coord, Tower*>(c, new RightTower_1x1(c, vman, pman)));
				return true;
		}
		return false;
	}

	void TowerManager::draw_towers(const GUI & gui) const {
		for (auto i = towers.begin(); i != towers.end(); ++i) {
			if(i->second->draw(gui) == false) {
				//If tower failed to draw:
				#ifdef DEBUGGING
				#include <iostream>
				std::cout << "Failed to draw Tower: " << i->first << std::endl;
				#endif //DEBUGGING
			}
		}
	}

	void TowerManager::end_of_wave() {
		for (auto i = towers.begin(); i != towers.end(); ++i) {
			i->second->end_of_wave();
		}
	}

}
