#include "gui.hpp"

GUI::GUI() : startRow(BOARDR0), startCol(BOARDC0), boardRows(BOARDROWS), boardCols(BOARDCOLS), intelRows(INTELROWS), intelCols(INTELCOLS) {

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
	getyx(main_win, row, col);

	int ret;
	ret = wmove(main_win, row-1, col); //Move cursor
	wrefresh(main_win);
	return ret;
}

bool GUI::move_cursor_down() {
	int col, row;
	getyx(main_win, row, col);

	int ret;
	ret = wmove(main_win, row+1, col); //Move cursor
	wrefresh(main_win);
	return ret;
}

bool GUI::move_cursor_left() {
	int col, row;
	getyx(main_win, row, col);

	int ret;
	ret = wmove(main_win, row, col-1); //Move cursor
	wrefresh(main_win);
	return ret;
}

bool GUI::move_cursor_right() {
	int row, col;
	getyx(main_win, row, col);

	int ret;
	ret = wmove(main_win, row, col+1); //Move cursor
	wrefresh(main_win);
	return ret;
}

Coord GUI::get_cursor_pos() {
	int row, col;
	getyx(main_win, row, col);
	Coord ret(row, col);
	return ret;
}

//Puts a char at specified coord in the guis window.
//Does not refresh
//Returns true iff successful
bool GUI::draw(const Coord & coord, const char ch) {
	int row, col;
	getyx(main_win, row, col);

	int ret;
	ret = mvwaddch(main_win, coord.get_row(), coord.get_col(), ch);
	wmove(main_win, row, col);
	
	return ret;
}

//Draws a gfx
bool GUI::draw_gfx(const Coord & coord, std::vector<std::vector<char> > & gfx, int row, int col) {
	int max_row, max_col;
	getmaxyx(main_win, max_row, max_col);
	if (   row + coord.get_row() > max_row
			|| col + coord.get_col() > max_col
			|| coord.get_row() < 0
			|| coord.get_col() < 0 ) {
		return false;
	}

	int cur_row, cur_col;
	getyx(main_win, cur_row, cur_col);

	for (int r = 0; r < row; ++r) {
		wmove(main_win, coord.get_row() + r, coord.get_col());
		for (int c = 0; c < col; ++c) {
			waddch(main_win, gfx[r][c]);
		}
	}

	wmove(main_win, cur_row, cur_col);

	return true;
}

void GUI::clear() {
	clear(); //Clear curses
}

void GUI::refresh() {
	wrefresh(main_win); //Refresh curses
}

WINDOW *create_new_win(int height, int width, int starty, int startx) {
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0); /* 0, 0 gives default characters 
                          * for the vertical and horizontal
                          * lines
                          */
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}

void destroy_win(WINDOW *local_win) {
	/* box(local_win, ' ', ' '); : This won't produce the desired
	 * result of erasing the window. It will leave it's four corners 
	 * and so an ugly remnant of window. 
	 */
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	/* The parameters taken are 
	 * 1. win: the window on which to operate
	 * 2. ls: character to be used for the left side of the window 
	 * 3. rs: character to be used for the right side of the window 
	 * 4. ts: character to be used for the top side of the window 
	 * 5. bs: character to be used for the bottom side of the window 
	 * 6. tl: character to be used for the top left corner of the window 
	 * 7. tr: character to be used for the top right corner of the window 
	 * 8. bl: character to be used for the bottom left corner of the window 
	 * 9. br: character to be used for the bottom right corner of the window
	 */
	wrefresh(local_win);
	delwin(local_win);
}
