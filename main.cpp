#include "main.hpp"

int main() {
	init_ncurses();
	
	termd::Player player;

	termd::Menu menu(player);
	menu.run();

	end_ncurses();

	return 0;
}

void init_ncurses() {
	initscr(); //Starts curses mode
	cbreak(); //Since we only want to read characters
	noecho(); //Turns off echo of input
	keypad(stdscr, TRUE);
}

void end_ncurses() {
	endwin(); //End curses mode
}
