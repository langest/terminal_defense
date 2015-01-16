#include "towermanager.hpp"

namespace termd {
		
	TowerManager::TowerManager(const VirusManager& v, ProjectileManager& pm, Player& p) : player(p), vman(v), pman(pm) {

	}

	TowerManager::~TowerManager() {
	}

	void TowerManager::update() {
		for (auto i = towers.begin(); i != towers.end(); ) {
			if(i->second->update() == false) {
				//If tower is flagging removal, remove it!
				i = towers.erase(i);
			}else{
				++i;
			}
		}
	}

	bool TowerManager::build_tower(Coord c, int tower_id) {
		tower_base * tbp;
		try {
			tbp = tl.get(tower_id);
		} catch (const std::invalid_argument &) {
			//invalid tower tried to load
			return false;
		}
		if(player.get_ram() >= tbp->cost) {
			if(true == place_tower(c, tower_id)){
				player.modify_ram(-tbp->cost);
				return true;
			}
		}
		return false;
	}

	bool TowerManager::place_tower(Coord c, int tower_id) {
		if(towers.find(c) != towers.end()) {
			//space taken by other tower!
			return false;
		}
		tower_base * tbp;
		try {
			tbp = tl.get(tower_id);
		} catch (const std::invalid_argument &) {
			//invalid tower tried to load
			return false;
		}
		switch(tbp->type){
			case TOWER_DIRECTION: 
			{
				attacking_tower_base* atbp = (attacking_tower_base*) tbp;
				towers.insert( std::pair<Coord, tower_ptr>(c, tower_ptr(new DirectionTower_1x1(c, *atbp, vman, pman))));
			return true;
			}
			case TOWER_HOMING:
			{
				attacking_tower_base* atbp = (attacking_tower_base*) tbp;
				towers.insert( std::pair<Coord, tower_ptr>(c, tower_ptr(new BasicTower_1x1(c, *atbp, vman, pman))));
			return true;
			}
			case TOWER_WALL:
				towers.insert( std::pair<Coord, tower_ptr>(c, tower_ptr(new Wall_1x1(c))));
			return true;
		}
		return false;
	}

	void TowerManager::draw_towers() const {
		for (auto i = towers.begin(); i != towers.end(); ++i) {
			if(i->second->draw() == false) {
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

	bool TowerManager::save_to_file(std::string filename) {
		std::ofstream savefile;
		savefile.open(filename);
		if(savefile.is_open()) {
			//Number of towers on map:
			savefile << towers.size() << std::endl<< std::endl;
			//ID numbers for each tower:
			for(auto it = towers.begin(); it != towers.end(); ++it) {
				savefile << (it->second)->get_id() << " " << it->first << " " << (it->second)->get_age() << std::endl;
			}
			savefile << std::endl << std::endl;
			savefile.close();
			return true;
		} else {
			return false;
		}
	}
	bool TowerManager::load_from_file(std::string filename) {
		std::ifstream loadfile;
		loadfile.open(filename);
		if(loadfile.is_open()) {
			int size;
			int id;
			int age;
			Coord c;
			//Number of towers on map:
			loadfile >> size;
			//ID numbers for each tower:
			for(int i = 0; i < size; ++i) {
				loadfile >> id >> c >> age;
				place_tower(c, id);
				for(int a = 0; a < age; ++a) {
					towers[c]->end_of_wave();
				}
			}			
			loadfile.close();
			return true;
		} else {
			return false;
		}
	}
}
