#include <cstdlib>
#include <ctime>
#include <curses.h>

#include <Menu.h>
#include <logging/Logger.h>

namespace {

void initNcurses() {
	// TODO set up locale
	initscr(); //Starts curses mode
	cbreak(); //Since we only want to read characters
	noecho(); //Turns off echo of input
	keypad(stdscr, TRUE);
}

void endNcurses() {
	endwin();
}

void seedRandomGenerator() {
	std::srand(std::time(nullptr));
}

}

int main() {
	termd::CLogger logger(__FILE__);

	logger.log("Seeding random generator");
	seedRandomGenerator();

	logger.log("Init ncurses");
	initNcurses();

	logger.log("Run menu");
	termd::CMenu().run();

	logger.log("End ncurses");
	endNcurses();

	logger.log("Exiting");
	return 0;
}

