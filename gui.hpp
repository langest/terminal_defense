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
		WINDOW * main_win;

	public:
		GUI();
		~GUI();
		GUI(const GUI &);

		GUI& operator=(const GUI &);

		void init_gui();
		bool move_cursor_up();
		bool move_cursor_down();
		bool move_cursor_left();
		bool move_cursor_right();

		bool draw(const Coord &, const char); //Does not refresh
		bool draw_gfx(const Coord &, const char**, int, int);
		void clear();
		void refresh();

};

WINDOW *create_new_win(int, int, int, int);
void destroy_win(WINDOW *);

#endif //termd_gui
