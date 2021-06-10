#include <curses.h>

#include <Menu.h>

void init_ncurses() {
	// TODO set up locale
	initscr(); //Starts curses mode
	cbreak(); //Since we only want to read characters
	noecho(); //Turns off echo of input
	keypad(stdscr, TRUE);
}

void end_ncurses() {
	endwin(); //End curses mode
}

int main() {
	init_ncurses();

	termd::CMenu().run();

	end_ncurses();

	return 0;
}

