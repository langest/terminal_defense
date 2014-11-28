#ifndef termd_player
#define termd_player

#ifndef termd_vector
#define termd_vector
#include <vector>
#endif

class Player {
	private:
		std::vector<String> completed_maps;
	protected:
		
	public:
		Player();
		Player(const Player &);
		~Player();

		Player& Player(const Player &);
		
};

#endif //termd_player
