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
			int max_cp;
			int cp;
		protected:
			
		public:
			Player();
			Player(const Player &) = delete;
			~Player();
			
			void new_map_refresh();
			int get_max_cp() const;
			void set_max_cp(int);
			int get_cp() const;
			void set_cp(int);
			bool is_alive() const;
			void take_damage(int);
			void set_ram(int); //Sets the current ram to the value
			void modify_ram(int); //Adds the value to the current ram
			int get_ram() const;

			void unlock_tower(int);
			void lock_tower(int);
			bool has_tower(int) const; 

			bool save_to_file(std::string);
			void load_from_file(std::string);
	};

}

#endif //termd_player
