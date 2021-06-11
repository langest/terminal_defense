#include <curses.h>

#include <Menu.h>
#include <logging/logger.h>

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
	termd::CLogger logger(__FILE__);
	logger.log("Init ncurses");

	init_ncurses();

	logger.log("Run menu");
	termd::CMenu().run();

	logger.log("End ncurses");
	end_ncurses();

	logger.log("Exiting");
	return 0;
}

