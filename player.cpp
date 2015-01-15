#include "player.hpp"

namespace termd {

	Player::Player() : availiable_towers({BASIC_TOWER_1x1_ID}), ram(PLAYER_DEFAULT_RAM), hp(PLAYER_DEFAULT_HP) {
		
	}

	Player::~Player() {
		//Currently nothing needs to be done
	}

	void Player::new_map_refresh() {
		hp = PLAYER_DEFAULT_HP;
		ram = PLAYER_DEFAULT_RAM;
	}

	int Player::get_hp() const {
		return hp;
	}

	bool Player::is_alive() const {
		return hp > 0;
	}

	void Player::take_damage(int amount) {
		hp -= amount;
	}

	void Player::modify_ram(int amount) {
		ram += amount;
	}

	int Player::get_ram() const{
		return ram;
	}

	void Player::unlock_tower(int id) {
		availiable_towers.insert(id);
	}

	void Player::lock_tower(int id) {
		availiable_towers.erase(id);
	}

	bool Player::has_tower(int id) const {
		return availiable_towers.find(id) != availiable_towers.end();
	}

	bool Player::save_to_file(std::string filename) {
		std::ofstream savefile;
		savefile.open(filename);
		if(savefile.is_open()) {
			//Number of completed maps:
			savefile << completed_maps.size() << std::endl;
			//ID numbers for each completed map:
			for(auto it = completed_maps.begin(); it != completed_maps.end(); ++it) {
				savefile << (*it) << " ";
			}
			savefile << std::endl;

			//Number of availible towers:
			savefile << availiable_towers.size() << std::endl;
			//ID representing towers:
			for(auto it = availiable_towers.begin(); it != availiable_towers.end(); ++it) {
				savefile << (*it) << " ";
			}
			savefile << std::endl;
			
			savefile.close();
			return true;
		}
		return false;
	}

	void Player::load_from_file(std::string filename) {
		std::ifstream loadfile;
		loadfile.open(filename);
		if(loadfile.is_open()) {
			int data;
			std::set<int>::size_type set_size;

			//number of completed maps
			loadfile >> set_size;
			//Iterate through each element (map ID:s)
			for(std::set<int>::size_type i = 0; i < set_size; ++i) {
				loadfile >> data;
				completed_maps.insert(data);
			}

			//Number of availiable towers:
			loadfile >> set_size;
			for(std::set<int>::size_type i = 0; i < set_size; ++i) {				
				loadfile >> data;
				availiable_towers.insert(data);
			}
			loadfile.close();
		}
	}
}
