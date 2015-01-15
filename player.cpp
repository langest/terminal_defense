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

	void Player::save_to_file(std::string filename) {
		std::ofstream savefile;
		savefile.open(filename);
		if(savefile.is_open()) {
			//writes the size of the completed_maps set
			//cast the value as an array of chars, then print each char. 
			//write binary data instead of text.
			//std::set<int>::size_type set_size(completed_maps.size());
			//savefile.write((char *)&(set_size), sizeof(std::set<int>::size_type));
			savefile << completed_maps.size() << std::endl;
			//writes the ints representing the completed maps
			for(auto it = completed_maps.begin(); it != completed_maps.end(); ++it) {
				savefile << (*it) << " ";
				//savefile.write((char *)&(*it), sizeof(int));
			}
			savefile << std::endl;


			//writes the size of the availiable_towers set
			//set_size = availiable_towers.size();
			//savefile.write((char *)&(set_size), sizeof(std::set<int>::size_type));
			savefile << availiable_towers.size() << std::endl;
			//writes the ints representing the availible towers
			for(auto it = availiable_towers.begin(); it != availiable_towers.end(); ++it) {
				savefile << (*it) << " ";
				//savefile.write((char *)&(*it), sizeof(int));
			}
			savefile << std::endl;
			
			savefile.close();
		}
	}

	void Player::load_from_file(std::string filename) {
		std::ifstream loadfile;
		loadfile.open(filename);
		std::cout << "READING SAVED FILE";
		if(loadfile.is_open()) {
			//empty data to write to:
			int data;
			std::set<int>::size_type set_size;
			std::cout << "READING SAVED FILE";

			//read "Completed Maps" size
			//loadfile.read((char *)&set_size, sizeof(std::set<int>::size_type));
			loadfile >> set_size;
			//Iterate through each element
			for(std::set<int>::size_type i = 0; i < set_size; ++i) {
				loadfile >> data;
				completed_maps.insert(data);
				
				//Read the data, and out it to "Completed Maps" set
				//loadfile.read((char *)&data, sizeof(int));
				std::cout << data;
			}
			std::cout << std::endl;

			//loadfile.read((char *)&set_size, sizeof(std::set<int>::size_type));
			loadfile >> set_size;
			for(std::set<int>::size_type i = 0; i < set_size; ++i) {				
				loadfile >> data;
				//loadfile.read((char *)&data, sizeof(int));
				availiable_towers.insert(data);
				std::cout << data;
			}
			getch();
			loadfile.close();
		}
	}
}
