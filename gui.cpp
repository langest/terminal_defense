#include "gui.hpp"

GUI::GUI() : startRow(BOARDR0), startCol(BOARDC0), boardRows(BOARDROWS), boardCols(BOARDCOLS), intelRows(INTELROWS), winSpace(WINDOWSPACE) {

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
}

bool GUI::move_cursor_up() {
	int col, row;
	getyx(stdscr, row, col);

	int ret;
	ret = move(row-1, col); //Move cursor
	return ret;
}

bool GUI::move_cursor_down() {
	int col, row;
	getyx(stdscr, row, col);

	int ret;
	ret = move(row+1, col); //Move cursor
	return ret;
}

bool GUI::move_cursor_left() {
	int col, row;
	getyx(stdscr, row, col);

	int ret;
	ret = move(row, col-1); //Move cursor
	return ret;
}

bool GUI::move_cursor_right() {
	int row, col;
	getyx(stdscr, row, col);

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

//Draws a gfx
bool GUI::draw_gfx(const Coord & coord, std::vector<std::vector<char> > & gfx, int row, int col) {
	int max_row, max_col;
	getmaxyx(stdscr, max_row, max_col);
	if (   row + coord.get_row() > max_row
			|| col + coord.get_col() > max_col
			|| coord.get_row() < 0
			|| coord.get_col() < 0 ) {
		return false;
	}

	int cur_row, cur_col;
	getyx(stdscr, cur_row, cur_col);

	for (int r = 0; r < row; ++r) {
		move(coord.get_row() + r, coord.get_col());
		for (int c = 0; c < col; ++c) {
			addch(gfx[r][c]);
		}
	}

	move(cur_row, cur_col);

	return true;
}

void GUI::draw_board() {
	int cur_row, cur_col;
	getyx(stdscr, cur_row, cur_col);

	mvaddch(startRow, startCol, BOARDTL);
	mvaddch(startRow + boardRows + 1, startCol, BOARDBL);
	mvaddch(startRow, startCol + boardCols + 1, BOARDTR);
	mvaddch(startRow + boardRows + 1, startCol + boardCols + 1, BOARDBR);

	mvhline(startRow, startCol + 1, BOARDTS, boardCols);
	mvvline(startRow + 1, startCol, BOARDLS, boardRows);
	mvhline(startRow + boardRows + 1, startCol + 1, BOARDBS, boardCols);
	mvvline(startRow + 1, startCol + boardCols + 1, BOARDRS, boardRows);

	move(cur_row, cur_col);
}

void GUI::clear() {
	clear(); //Clear curses
}

void GUI::refresh() {
	wrefresh(stdscr); //Refresh curses
}
