#include "gui.hpp"

namespace termd {

	GUI::GUI() {
		move(BOARDR0, BOARDC0); //initialize cursor position
	}

	GUI::~GUI() {
		//Currently nothing to do here
	}

	bool GUI::move_cursor_up() const {
		int col, row;
		getyx(stdscr, row, col);

		if (row <= BOARDR0) {
			move(BOARDR0, col);
			return false;
		}

		int ret;
		ret = move(row-1, col); //Move cursor
		return ret;
	}

	bool GUI::move_cursor_down() const {
		int col, row;
		getyx(stdscr, row, col);

		if (row >= BOARDR0 + BOARDROWS - 1) {
			move(BOARDR0 + BOARDROWS - 1, col);
			return false;
		}

		int ret;
		ret = move(row+1, col); //Move cursor
		return ret;
	}

	bool GUI::move_cursor_left() const {
		int col, row;
		getyx(stdscr, row, col);

		if (col <= BOARDC0) {
			move(row, BOARDC0);
			return false;
		}

		int ret;
		ret = move(row, col-1); //Move cursor
		return ret;
	}

	bool GUI::move_cursor_right() const {
		int row, col;
		getyx(stdscr, row, col);

		if (col >= BOARDC0 + BOARDCOLS - 1) {
			move(row, BOARDC0 + BOARDCOLS - 1);
			return false;
		}

		int ret;
		ret = move(row, col+1); //Move cursor
		return ret;
	}

	Coord GUI::get_cursor_pos() const {
		int row, col;
		getyx(stdscr, row, col);
		Coord ret(row, col);
		return ret;
	}

	//Puts a char at specified coord in the guis window.
	//Does not refresh
	//Returns true iff successful
	bool GUI::draw(const Coord & coord, const char ch) const {
		int row, col;
		getyx(stdscr, row, col);

		int ret;
		ret = mvwaddch(stdscr, coord.get_row(), coord.get_col(), ch);
		move(row, col);
		
		return ret;
	}

	//Draws a gfx in board window
	//Does not refresh
	bool GUI::draw_gfx(const Coord & coord, const std::vector<std::vector<char> > & gfx) const {
		int max_row, max_col;
		getmaxyx(stdscr, max_row, max_col);
		if (   (int) gfx.size() + coord.get_row() >= max_row
				|| (int) gfx[0].size() + coord.get_col() >= max_col
				|| coord.get_row() < 0
				|| coord.get_col() < 0 ) {
			return false;
		}

		int cur_row, cur_col;
		getyx(stdscr, cur_row, cur_col);

		for (unsigned int r = 0; r < gfx.size(); ++r) {
			for (unsigned int c = 0; c < gfx[0].size(); ++c) {
				mvwaddch(stdscr, BOARDR0 + coord.get_row() + r, BOARDC0 + coord.get_col() + c, gfx[r][c]);
			}
		}

		move(cur_row, cur_col);
		return true;
	}

	bool GUI::draw_gfx(const Coord & coord, const char gfx) const {
		if (coord.get_row() >= BOARDROWS ||
				coord.get_col() >= BOARDCOLS ||
				coord.get_row() < 0 ||
				coord.get_col() < 0) return false;
		int cur_row, cur_col;
		getyx(stdscr, cur_row, cur_col);

		bool ret =  mvwaddch(stdscr, BOARDR0 + coord.get_row(), BOARDC0 + coord.get_col(), gfx);
		
		move(cur_row, cur_col);
		return ret;
	}

	void GUI::print_intel(std::string message) const {
		int cur_row, cur_col;
		getyx(stdscr, cur_row, cur_col);

		mvwaddstr(stdscr, BOARDR0 + BOARDROWS + WINDOWSPACE + 2, BOARDC0, message.c_str());

		move(cur_row, cur_col);
	}

	void GUI::draw_board_frame() const {
		int cur_row, cur_col;
		getyx(stdscr, cur_row, cur_col);

		mvaddch(BOARDR0 - 1, BOARDC0 - 1, FRAMETL);
		mvaddch(BOARDR0 + BOARDROWS, BOARDC0 - 1, FRAMEBL);
		mvaddch(BOARDR0 - 1, BOARDC0 + BOARDCOLS, FRAMETR);
		mvaddch(BOARDR0 + BOARDROWS, BOARDC0 + BOARDCOLS, FRAMEBR);

		mvhline(BOARDR0 - 1, BOARDC0, FRAMETS, BOARDCOLS);
		mvvline(BOARDR0, BOARDC0 - 1, FRAMELS, BOARDROWS);
		mvhline(BOARDR0 + BOARDROWS, BOARDC0, FRAMEBS, BOARDCOLS);
		mvvline(BOARDR0, BOARDC0 + BOARDCOLS, FRAMERS, BOARDROWS);

		move(cur_row, cur_col);
	}

	void GUI::draw_intel_frame() const {
		int cur_row, cur_col;
		getyx(stdscr, cur_row, cur_col);

		mvaddch(BOARDR0 + 1 + WINDOWSPACE + BOARDROWS, BOARDC0 - 1, FRAMETL);
		mvaddch(BOARDR0 + 1 + WINDOWSPACE + BOARDROWS + INTELROWS + 1, BOARDC0 - 1, FRAMEBL);
		mvaddch(BOARDR0 + 1 + WINDOWSPACE + BOARDROWS, BOARDC0 + BOARDCOLS, FRAMETR);
		mvaddch(BOARDR0 + 1 + WINDOWSPACE + BOARDROWS + INTELROWS + 1, BOARDC0 + BOARDCOLS, FRAMEBR);

		mvhline(BOARDR0 + 1 + WINDOWSPACE + BOARDROWS, BOARDC0, FRAMETS, BOARDCOLS);
		mvvline(BOARDR0 + 2 + WINDOWSPACE + BOARDROWS, BOARDC0 - 1, FRAMELS, INTELROWS);
		mvhline(BOARDR0 + 2 + WINDOWSPACE + BOARDROWS + INTELROWS, BOARDC0, FRAMEBS, BOARDCOLS);
		mvvline(BOARDR0 + 2 + WINDOWSPACE + BOARDROWS, BOARDC0 + BOARDCOLS, FRAMERS, INTELROWS);

		move(cur_row, cur_col);
	}

	void GUI::clear_game() const {
		int cur_row, cur_col;
		getyx(stdscr, cur_row, cur_col);
		for (int i = BOARDR0; i < BOARDROWS + BOARDR0; ++i) {
			move(i, BOARDC0);
			for (int j = 0; j < BOARDCOLS; ++j) {
				addch(' ');
			}
		}
		move(cur_row, cur_col);
	}

	void GUI::clear_intel() const {
		int cur_row, cur_col;
		getyx(stdscr, cur_row, cur_col);
		for (int i = BOARDR0 + BOARDROWS + WINDOWSPACE + 2; i < BOARDR0 + BOARDROWS + WINDOWSPACE + 2 + INTELROWS; ++i) {
			move(i, BOARDC0);
			for (int j = 0; j < BOARDCOLS; ++j) {
				addch(' ');
			}
		}
		move(cur_row, cur_col);
	}

	void GUI::refresh() const {
		wrefresh(stdscr); //Refresh curses
	}

}
