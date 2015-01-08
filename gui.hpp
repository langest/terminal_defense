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
		public:
			GUI();
			~GUI();
			GUI(const GUI &) = delete;

			GUI& operator=(const GUI &);

			void init_gui() const;
			bool move_cursor_up() const;
			bool move_cursor_down() const;
			bool move_cursor_left() const;
			bool move_cursor_right() const;
			Coord get_cursor_pos() const;

			bool draw(const Coord &, const char) const; //Does not refresh
			bool draw_gfx(const Coord &, const std::vector<std::vector<char> > &) const;
			bool draw_gfx(const Coord &, const char) const;
			void print_intel(const std::string) const;
			void draw_board_frame() const;
			void draw_intel_frame() const;
			void clear_game() const;
			void clear_intel() const;
			void refresh() const;

	};

	WINDOW *create_new_win(int, int, int, int);
	void destroy_win(WINDOW *);

}

#endif //termd_gui
