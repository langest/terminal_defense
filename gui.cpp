#include "gui.hpp"

namespace termd {

//	GUI::GUI() {
//		move(BOARDR0, BOARDC0); //initialize cursor position
//	}
//
//	GUI::~GUI() {
//		//Currently nothing to do here
//	}

	bool GUI::move_cursor_up(){
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

//board_rows is the number of rows on the board, moves the cursor one row.
	bool GUI::move_cursor_down(int board_rows){
		int col, row;
		getyx(stdscr, row, col);

		if (row >= BOARDR0 + board_rows - 1) {
			move(BOARDR0 + board_rows - 1, col);
			return false;
		}

		int ret;
		ret = move(row+1, col); //Move cursor
		return ret;
	}

	bool GUI::move_cursor_left(){
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

	bool GUI::move_cursor_right(int board_cols){
		int row, col;
		getyx(stdscr, row, col);

		if (col >= BOARDC0 + board_cols - 1) {
			move(row, BOARDC0 + board_cols - 1);
			return false;
		}

		int ret;
		ret = move(row, col+1); //Move cursor
		return ret;
	}

	Coord GUI::get_cursor_pos(){
		int row, col;
		getyx(stdscr, row, col);
		Coord ret(row, col);
		return ret;
	}

	int GUI::get_input() {
		return getch();
	}

	//Puts a char at specified coord in the guis window.
	//Does not refresh
	//Returns true iff successful
	bool GUI::draw(const Coord & coord, const char ch){
		int row, col;
		getyx(stdscr, row, col);

		int ret;
		ret = mvwaddch(stdscr, coord.get_row(), coord.get_col(), ch);
		move(row, col);
		
		return ret;
	}

	//Draws a gfx in board window
	//Does not refresh
	bool GUI::draw_gfx(const Coord & coord, const std::vector<std::vector<char> > & gfx){
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

	bool GUI::draw_gfx(const Coord & coord, const char gfx){
		int max_row, max_col;
		getmaxyx(stdscr, max_row, max_col);
		if (coord.get_row() >= max_row ||
				coord.get_col() >= max_col ||
				coord.get_row() < 0 ||
				coord.get_col() < 0) return false;
		int cur_row, cur_col;
		getyx(stdscr, cur_row, cur_col);

		bool ret =  mvwaddch(stdscr, BOARDR0 + coord.get_row(), BOARDC0 + coord.get_col(), gfx);
		
		move(cur_row, cur_col);
		return ret;
	}

	void GUI::print_intel(int board_rows, std::string message){
		int cur_row, cur_col;
		getyx(stdscr, cur_row, cur_col);

		mvwaddstr(stdscr, BOARDR0 + board_rows + WINDOWSPACE + 2, BOARDC0, message.c_str());

		move(cur_row, cur_col);
	}

	void GUI::draw_board_frame(int board_rows, int board_cols){
		int cur_row, cur_col;
		getyx(stdscr, cur_row, cur_col);

		mvaddch(BOARDR0 - 1, BOARDC0 - 1, FRAMETL);
		mvaddch(BOARDR0 + board_rows, BOARDC0 - 1, FRAMEBL);
		mvaddch(BOARDR0 - 1, BOARDC0 + board_cols, FRAMETR);
		mvaddch(BOARDR0 + board_rows, BOARDC0 + board_cols, FRAMEBR);

		mvhline(BOARDR0 - 1, BOARDC0, FRAMETS, board_cols);
		mvvline(BOARDR0, BOARDC0 - 1, FRAMELS, board_rows);
		mvhline(BOARDR0 + board_rows, BOARDC0, FRAMEBS, board_cols);
		mvvline(BOARDR0, BOARDC0 + board_cols, FRAMERS, board_rows);

		move(cur_row, cur_col);
	}

	void GUI::draw_intel_frame(int board_rows){
		int cur_row, cur_col;
		getyx(stdscr, cur_row, cur_col);

		mvaddch(BOARDR0 + 1 + WINDOWSPACE + board_rows, BOARDC0 - 1, FRAMETL);
		mvaddch(BOARDR0 + 1 + WINDOWSPACE + board_rows + INTELROWS + 1, BOARDC0 - 1, FRAMEBL);
		mvaddch(BOARDR0 + 1 + WINDOWSPACE + board_rows, BOARDC0 + INTELCOLS, FRAMETR);
		mvaddch(BOARDR0 + 1 + WINDOWSPACE + board_rows + INTELROWS + 1, BOARDC0 + INTELCOLS, FRAMEBR);

		mvhline(BOARDR0 + 1 + WINDOWSPACE + board_rows, BOARDC0, FRAMETS, INTELCOLS);
		mvvline(BOARDR0 + 2 + WINDOWSPACE + board_rows, BOARDC0 - 1, FRAMELS, INTELROWS);
		mvhline(BOARDR0 + 2 + WINDOWSPACE + board_rows + INTELROWS, BOARDC0, FRAMEBS, INTELCOLS);
		mvvline(BOARDR0 + 2 + WINDOWSPACE + board_rows, BOARDC0 + INTELCOLS, FRAMERS, INTELROWS);

		move(cur_row, cur_col);
	}

	void GUI::clear_game(int board_rows, int board_cols) {
		int cur_row, cur_col;
		getyx(stdscr, cur_row, cur_col);
		for (int i = BOARDR0; i < board_rows + BOARDR0; ++i) {
			move(i, BOARDC0);
			for (int j = 0; j < board_cols; ++j) {
				addch(' ');
			}
		}
		move(cur_row, cur_col);
	}

	void GUI::clear_intel(int board_rows){
		int cur_row, cur_col;
		getyx(stdscr, cur_row, cur_col);
		for (int i = BOARDR0 + board_rows + WINDOWSPACE + 2; i < BOARDR0 + board_rows + WINDOWSPACE + 2 + INTELROWS; ++i) {
			move(i, BOARDC0);
			for (int j = 0; j < INTELCOLS; ++j) {
				addch(' ');
			}
		}
		move(cur_row, cur_col);
	}

	void GUI::refresh(){
		wrefresh(stdscr); //Refresh curses
	}

}
