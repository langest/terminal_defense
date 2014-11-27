#ifndef termd_gui
#define termd_gui

#ifndef termd_ncurses
#define termd_ncurses
#include <ncurses.h>
#endif

#ifndef termd_coord
#define termd_coord
#include "coord.hpp"
#endif

class GUI {
	private:

	public:
		bool move_cursor_up();
		bool move_cursor_down();
		bool move_cursor_left();
		bool move_cursor_right();

		bool draw(int, int, char);
		bool clear();

};
