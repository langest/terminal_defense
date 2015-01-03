#ifndef termd_gui
#define termd_gui

#ifndef termd_ncurses
#define termd_ncurses
#include <ncurses.h>
#endif //termd_ncurses

#ifndef termd_vector
#define termd_vector
#include <vector>
#endif //termd_vector

#ifndef termd_string
#define termd_string
#include <string>
#endif

#include "coord.hpp"
#include "definitions"

namespace termd {

	class GUI {
		private:
			int startRow, startCol;
			int boardRows, boardCols;
			int intelRows, intelCols;
			int winSpace;

		public:
			void clear_game();

			GUI();
			~GUI();
			GUI(const GUI &) = delete;

			GUI& operator=(const GUI &);

			void init_gui();
			bool move_cursor_up();
			bool move_cursor_down();
			bool move_cursor_left();
			bool move_cursor_right();
			Coord get_cursor_pos();

			bool draw(const Coord &, const char); //Does not refresh
			bool draw_gfx(const Coord &, std::vector<std::vector<char> > &);
			bool draw_gfx(const Coord &, char);
			void print_intel(std::string);
			void draw_board_frame();
			void draw_intel_frame();
			void clear();
			void refresh();

	};

	WINDOW *create_new_win(int, int, int, int);
	void destroy_win(WINDOW *);

}

#endif //termd_gui
