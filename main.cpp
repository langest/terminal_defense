#include "main.hpp"

int main() {
	initscr(); //Starts curses mode
	cbreak(); //Since we only want to read characters
	noecho(); //Turns off echo of input
	keypad(stdscr, TRUE);
	
	Game game;

	game.build_phase();
	game.invasion_phase();
	
	endwin(); //End curses mode
	return 0;
}

