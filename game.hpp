#ifndef termd_game
#define termd_game

#include "gui.hpp"
#include "maps/gameboard.hpp"

class Game {
	private:
		GUI gui;
		GameBoard board;

		bool build_tower(int);
	public:
		void build_phase();
		void invasion_phase();
};

#endif //termd_game
