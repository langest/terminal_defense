#ifndef termd_gui
#define termd_gui

#ifndef MOCK_GUI
#ifndef termd_ncurses
#define termd_ncurses
#include <ncurses.h>
#endif //termd_ncurses
#endif //MOCK_GUI

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
		public:
			GUI() = delete;
			~GUI();
			GUI(const GUI &) = delete;

			//GUI& operator=(const GUI &);

			static bool move_cursor_up();
			static bool move_cursor_down();
			static bool move_cursor_left();
			static bool move_cursor_right();
			static Coord get_cursor_pos();

			static bool draw(const Coord &, const char); //Does not refresh
			static bool draw_gfx(const Coord &, const std::vector<std::vector<char> > &);
			static bool draw_gfx(const Coord &, const char);
			static void print_intel(const std::string);
			static void draw_board_frame();
			static void draw_intel_frame();
			static void clear_game();
			static void clear_intel();
			static void refresh();

	};
}

#endif //termd_gui
