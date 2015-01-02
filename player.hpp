#ifndef termd_player
#define termd_player

#ifndef termd_vector
#define termd_vector
#include <vector>
#endif

#include definitions;

class Player {
	private:
		std::vector<String> completed_maps;
		int ram;
		int hp;
	protected:
		
	public:
		Player();
		Player(const Player &) = delete;
		~Player();
		
		void new_map_refresh();
		inline bool is_alive();
		inline void take_damage(int); //returns is_alive after damage is taken
};

#endif //termd_player
