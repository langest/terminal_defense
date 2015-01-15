#ifndef termd_player
#define termd_player

#ifndef termd_set
#define termd_set
#include <set>
#endif

#ifndef termd_string
#define termd_string
#include <string>
#endif

#ifndef termd_fstream
#define termd_fstream
#include <fstream>
#endif

#ifndef termd_iostream
#define termd_iostream
#include <iostream>
#endif


#include "gui.hpp"

#include "definitions"

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

			void save_to_file(std::string);
			void load_from_file(std::string);
	};

}

#endif //termd_player
