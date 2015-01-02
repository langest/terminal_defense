#ifndef termd_game
#define termd_game

#include "definitions"
#include "gui.hpp"
#include "player.hpp"
#include "maps/gameboard.hpp"

class Game {
	private:
		GUI gui;
		Player player;
		GameBoard board;

		bool build_tower(int);
	public:
		Game();
		
		void build_phase();
		void invasion_phase();
};

#endif //termd_game
