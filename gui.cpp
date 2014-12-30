#include "gui.hpp"

GUI::GUI() : startRow(BOARDR0), startCol(BOARDC0), boardRows(BOARDROWS), boardCols(BOARDCOLS), intelRows(INTELROWS), winSpace(WINDOWSPACE) {
	move(startRow, startCol); //initialize cursor position
}

GUI::~GUI() {
	//Currently nothing to do here
}

GUI::GUI(const GUI & src) {
	startRow = src.startRow;
	startCol = src.startCol;
	boardRows = src.boardRows;
	boardCols = src.boardCols;
	intelRows = src.intelRows;
	intelCols = src.intelCols;
	move(startRow, startCol); //initialize cursor position
}

bool GUI::move_cursor_up() {
	int col, row;
	getyx(stdscr, row, col);

	if (row <= startRow) {
		move(startRow, col);
		return false;
	}

	int ret;
	ret = move(row-1, col); //Move cursor
	return ret;
}

bool GUI::move_cursor_down() {
	int col, row;
	getyx(stdscr, row, col);

	if (row >= startRow + boardRows - 1) {
		move(startRow + boardRows - 1, col);
		return false;
	}

	int ret;
	ret = move(row+1, col); //Move cursor
	return ret;
}

bool GUI::move_cursor_left() {
	int col, row;
	getyx(stdscr, row, col);

	if (col <= startCol) {
		move(row, startCol);
		return false;
	}

	int ret;
	ret = move(row, col-1); //Move cursor
	return ret;
}

bool GUI::move_cursor_right() {
	int row, col;
	getyx(stdscr, row, col);

	if (col >= startCol + boardCols - 1) {
		move(row, startCol + boardCols - 1);
		return false;
	}

	int ret;
	ret = move(row, col+1); //Move cursor
	return ret;
}

Coord GUI::get_cursor_pos() {
	int row, col;
	getyx(stdscr, row, col);
	Coord ret(row, col);
	return ret;
}

//Puts a char at specified coord in the guis window.
//Does not refresh
//Returns true iff successful
bool GUI::draw(const Coord & coord, const char ch) {
	int row, col;
	getyx(stdscr, row, col);

	int ret;
	ret = mvwaddch(stdscr, coord.get_row(), coord.get_col(), ch);
	move(row, col);
	
	return ret;
}

//Draws a gfx in board window
bool GUI::draw_gfx(const Coord & coord, std::vector<std::vector<char> > & gfx) {
	int max_row, max_col;
	getmaxyx(stdscr, max_row, max_col);
	if (   (int) gfx.size() + coord.get_row() > max_row
			|| (int) gfx[0].size() + coord.get_col() > max_col
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

void GUI::draw_board_frame() {
	int cur_row, cur_col;
	getyx(stdscr, cur_row, cur_col);

	mvaddch(startRow - 1, startCol - 1, FRAMETL);
	mvaddch(startRow + boardRows, startCol - 1, FRAMEBL);
	mvaddch(startRow - 1, startCol + boardCols, FRAMETR);
	mvaddch(startRow + boardRows, startCol + boardCols, FRAMEBR);

	mvhline(startRow - 1, startCol, FRAMETS, boardCols);
	mvvline(startRow, startCol - 1, FRAMELS, boardRows);
	mvhline(startRow + boardRows, startCol, FRAMEBS, boardCols);
	mvvline(startRow, startCol + boardCols, FRAMERS, boardRows);

	move(cur_row, cur_col);
}

void GUI::draw_intel_frame() {
	int cur_row, cur_col;
	getyx(stdscr, cur_row, cur_col);

	mvaddch(startRow + 1 + winSpace + boardRows, startCol - 1, FRAMETL);
	mvaddch(startRow + 1 + winSpace + boardRows + intelRows + 1, startCol - 1, FRAMEBL);
	mvaddch(startRow + 1 + winSpace + boardRows, startCol + boardCols, FRAMETR);
	mvaddch(startRow + 1 + winSpace + boardRows + intelRows + 1, startCol + boardCols, FRAMEBR);

	mvhline(startRow + 1 + winSpace + boardRows, startCol, FRAMETS, boardCols);
	mvvline(startRow + 2 + winSpace + boardRows, startCol - 1, FRAMELS, intelRows);
	mvhline(startRow + 2 + winSpace + boardRows + intelRows, startCol, FRAMEBS, boardCols);
	mvvline(startRow + 2 + winSpace + boardRows, startCol + boardCols, FRAMERS, intelRows);

	move(cur_row, cur_col);
}

void GUI::clear() {
	clear(); //Clear curses
}

void GUI::refresh() {
	wrefresh(stdscr); //Refresh curses
}
