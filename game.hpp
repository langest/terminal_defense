#ifndef termd_game
#define termd_game

#include "gui.hpp"

class Game {
	private:
		GUI gui;
		GameBoard board;
	public:
		void build_phase();
		bool build_tower();
};

#endif //termd_game
