#ifndef termd_player
#define termd_player

#ifndef termd_vector
#define termd_vector
#include <vector>
#endif

#ifndef termd_string
#define termd_string
#include <string>
#endif

#include "definitions"

class Player {
	private:
		std::vector<std::string> completed_maps;
		int ram;
		int hp;
	protected:
		
	public:
		Player();
		Player(const Player &) = delete;
		~Player();
		
		void new_map_refresh();
		bool is_alive();
		void take_damage(int);
		void modify_ram(int);
		int get_ram();
};

#endif //termd_player
