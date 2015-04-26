#ifndef termd_player
#define termd_player

#include <set>
#include <string>
#include <fstream>
#include <iostream>

#include "definitions"
#include "gui.hpp"

namespace termd {

	class Player {
		private:
			std::set<int> completed_maps;
			std::set<int> availiable_towers;
			int ram;
			int hp;
		protected:
			
		public:
			Player();
			Player(const Player &) = delete;
			~Player();
			
			void new_map_refresh();
			int get_hp() const;
			bool is_alive() const;
			void take_damage(int);
			void modify_ram(int);
			int get_ram() const;

			void unlock_tower(int);
			void lock_tower(int);
			bool has_tower(int) const; 

			bool save_to_file(std::string);
			void load_from_file(std::string);
	};

}

#endif //termd_player
