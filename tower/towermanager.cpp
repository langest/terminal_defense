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
		Tower* tp;
		switch(tower_id){ //TODO define towers somewhere...
			case WALL_1x1_ID: 
				//is it possible to build here?
				tp = new Wall_1x1(c);
				//TODO: Check if blocked
				if(player.get_ram() >= WALL_1x1_COST){
					//SUCCESS!
					player.modify_ram(-WALL_1x1_COST);
					towers.insert( std::pair<Coord, Tower*>(c, tp));
					return true;
				}else{
					//FAIL: Not enough RAM
					delete tp;
				}
				break;
			case BASIC_TOWER_1x1_ID: 
				//is it possible to build here?
				tp = new BasicTower_1x1(c, vman, pman);
				//TODO: Check if blocked
				if(player.get_ram() >= BASIC_TOWER_1x1_COST){
					//SUCCESS!
					player.modify_ram(-BASIC_TOWER_1x1_COST);
					towers.insert( std::pair<Coord, Tower*>(c, tp));
					return true;
				}else{
					//FAIL: Not enough RAM
					delete tp;
				}
				break;
			case RIGHT_TOWER_1x1_ID: 
				//is it possible to build here?
				tp = new RightTower_1x1(c, vman, pman);
				//TODO: Check if blocked
				if(player.get_ram() >= RIGHT_TOWER_1x1_COST){
					//SUCCESS!
					player.modify_ram(-RIGHT_TOWER_1x1_COST);
					towers.insert( std::pair<Coord, Tower*>(c, tp));
					return true;
				}else{
					//FAIL: Not enough RAM
					delete tp;
				}
				break;
		}
		return false;
	}

	void TowerManager::draw_towers(GUI & gui) {
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
