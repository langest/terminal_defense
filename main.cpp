#include "main.hpp"

int main() {
	init_ncurses();
	
	termd::Game game;

	game.intro();
	game.build_phase();
	game.invasion_phase();
	if(game.is_player_alive() == false) {
		game.outro();
		end_ncurses();
		return 0;
	}
	if(game.get_player_hp() < PLAYER_DEFAULT_HP) {
		game.unlock_tower(RIGHT_TOWER_1x1_ID);
	}
	game.build_phase();
	game.invasion_phase();
	game.outro();

	end_ncurses();

	return 0;
}

void init_ncurses() {
#ifndef mock_gui
	initscr(); //Starts curses mode
	cbreak(); //Since we only want to read characters
	noecho(); //Turns off echo of input
	keypad(stdscr, TRUE);
#endif //mock_gui
}

void end_ncurses() {
#ifndef mock_gui
	endwin(); //End curses mode
#endif //mock_gui
}
