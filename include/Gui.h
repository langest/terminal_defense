#pragma once

#include <ncurses.h>
#include <vector>
#include <string>
#include <utility>
#include <functional>
#include <algorithm>

#include <Coordinate.h>
#include <Constants.h>

namespace termd {

class GUI {
	public:
		GUI() = delete;
		~GUI();
		GUI(const GUI &) = delete;

		//GUI& operator=(const GUI &);

		static bool move_cursor(const CCoordinate &);
		static bool move_cursor_up();
		static bool move_cursor_down(int board_rows); //board_rows is the number of rows on the board, moves the cursor one row.
		static bool move_cursor_left();
		static bool move_cursor_right(int board_cols); //board_cols is the number of rows on the board, moves the cursor one col.
		static CCoordinate get_cursor_pos();
		static int get_input();

		static bool draw(const CCoordinate &, const char); //Does not refresh
		static bool draw_gfx(const CCoordinate &, const std::vector<std::vector<char> > &);
		static bool draw_gfx(const CCoordinate &, const char);
		// Print all menu items in vector and return an other vector with the
		// CCoordinates where the items were drawn
		static std::vector<CCoordinate> print_menu_items(const std::vector<std::string> &); //Does not refresh
		static void print_string(const std::string &);
		static void print_intel(int board_rows, const std::string &);
		static void draw_board_frame(int board_rows, int board_cols);
		static void draw_intel_frame(int board_cols);
		static void clear_game(int board_rows, int board_cols);
		static void clear_intel(int board_cols);
		static void refresh();

};

}