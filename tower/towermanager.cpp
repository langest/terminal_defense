#include "towermanager.hpp"

TowerManager::TowerManager(std::vector<Virus*>& v, std::vector<Projectile*>& p) : viruses(v), projectiles(p){

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
	switch(tower_id){ //TODO define towers somewhere...
		case WALL_1x1_ID: 
			//is it possible to build here?
			Wall_1x1* w = new Wall_1x1(c, *this);
			//TODO: Check if blocked
			if(ram >= WALL_1x1_COST){
				//SUCCESS!
				ram -= WALL_1x1_COST;
				towers.insert( std::pair<Coord, Tower*>(c, w));
				return true;
			}else{
				//FAIL: Not enough RAM
				delete w;
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
