#include "main.hpp"

namespace termd {

	int main() {
		initscr(); //Starts curses mode
		cbreak(); //Since we only want to read characters
		noecho(); //Turns off echo of input
		keypad(stdscr, TRUE);
		
		Game game;

		game.intro();
		game.build_phase();
		game.invasion_phase();
		game.outro();
		
		endwin(); //End curses mode
		return 0;
	}

}
