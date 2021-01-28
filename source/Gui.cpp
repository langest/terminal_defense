#include <Gui.h>

const char FrameLS = ACS_VLINE;

#define FRAMERS ACS_VLINE
#define FRAMEBS ACS_HLINE
#define FRAMETS ACS_HLINE
#define FRAMETL ACS_ULCORNER
#define FRAMETR ACS_URCORNER
#define FRAMEBL ACS_LLCORNER
#define FRAMEBR ACS_LRCORNER

namespace termd {

//	GUI::GUI() {
//		move(BoardR0, BoardC0); //initialize cursor position
//	}
//
//	GUI::~GUI() {
//		//Currently nothing to do here
//	}

bool GUI::move_cursor(const CCoordinate& pos) {
	int col, row;
	getmaxyx(stdscr, row, col);

	if (pos.getRow() > row || pos.getCol() > col) {
		return false;
	}
	move(pos.getRow(), pos.getCol());
	return true;
}

bool GUI::move_cursor_up(){
	int col, row;
	getyx(stdscr, row, col);

	if (row <= BoardR0) {
		move(BoardR0, col);
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

	if (row >= BoardR0 + board_rows - 1) {
		move(BoardR0 + board_rows - 1, col);
		return false;
	}

	int ret;
	ret = move(row+1, col); //Move cursor
	return ret;
}

bool GUI::move_cursor_left(){
	int col, row;
	getyx(stdscr, row, col);

	if (col <= BoardC0) {
		move(row, BoardC0);
		return false;
	}

	int ret;
	ret = move(row, col-1); //Move cursor
	return ret;
}

bool GUI::move_cursor_right(int board_cols){
	int row, col;
	getyx(stdscr, row, col);

	if (col >= BoardC0 + board_cols - 1) {
		move(row, BoardC0 + board_cols - 1);
		return false;
	}

	int ret;
	ret = move(row, col+1); //Move cursor
	return ret;
}

CCoordinate GUI::get_cursor_pos(){
	int row, col;
	getyx(stdscr, row, col);
	return CCoordinate(row, col);
}

int GUI::get_input() {
	return getch();
}

//Puts a char at specified CCoordinate in the guis window.
//Does not refresh
//Returns true iff successful
bool GUI::draw(const CCoordinate & coord, const char ch){
	int row, col;
	getyx(stdscr, row, col);

	int ret;
	ret = mvwaddch(stdscr, coord.getRow(), coord.getCol(), ch);
	move(row, col);

	return ret;
}

//Draws a gfx in board window
//Does not refresh
bool GUI::draw_gfx(const CCoordinate & coord, const std::vector<std::vector<char> > & gfx){
	int max_row, max_col;
	getmaxyx(stdscr, max_row, max_col);

	if ((int) gfx.size() + coord.getRow() >= max_row
			|| (int) gfx[0].size() + coord.getCol() >= max_col
			|| coord.getRow() < 0
			|| coord.getCol() < 0 ) {
		return false;
	}

	int cur_row, cur_col;
	getyx(stdscr, cur_row, cur_col);

	for (unsigned int r = 0; r < gfx.size(); ++r) {
		for (unsigned int c = 0; c < gfx[0].size(); ++c) {
			mvwaddch(stdscr, BoardR0 + coord.getRow() + r, BoardC0 + coord.getCol() + c, gfx[r][c]);
		}
	}

	move(cur_row, cur_col);
	return true;
}

bool GUI::draw_gfx(const CCoordinate & coord, const char gfx){
	int max_row, max_col;
	getmaxyx(stdscr, max_row, max_col);
	if (coord.getRow() >= max_row ||
			coord.getCol() >= max_col ||
			coord.getRow() < 0 ||
			coord.getCol() < 0) return false;
	int cur_row, cur_col;
	getyx(stdscr, cur_row, cur_col);

	bool ret =  mvwaddch(stdscr, BoardR0 + coord.getRow(), BoardC0 + coord.getCol(), gfx);

	move(cur_row, cur_col);
	return ret;
}

std::vector<CCoordinate> GUI::print_menu_items(const std::vector<std::string> & menu_items) {
	std::vector<CCoordinate> item_coords; // Return values, the position of the menu items
	if (menu_items.size() < 1) return item_coords; // Nothing to draw

	int max_row, max_col;
	getmaxyx(stdscr, max_row, max_col);

	size_t item_len = 0; // Find the longest string
	for (auto it = menu_items.begin(); it != menu_items.end(); ++it) {
		item_len = std::max(item_len +2, it->length()); // +2 because of menu markers
	}

	int col_pos = max_col/2 - item_len/2;

	int window_piece = max_row / 4;
	mvwaddstr(stdscr, window_piece/2, max_col/2 - 4, "* Menu *"); // Draw logo in first piece


	int step = window_piece*2 / menu_items.size(); // step in the two middle pieces

	int item_pos = window_piece+step;
	for (auto it = menu_items.begin(); it != menu_items.end(); ++it) {
		std::string marker("> ");
		mvwaddstr(stdscr, item_pos, col_pos, marker.append(*it).c_str()); // Draw the items in the middle pieces
		item_coords.push_back(CCoordinate(item_pos, col_pos));
		item_pos += step;
	}

	char version [20];
	sprintf(version, "Version: %s", Version);
	mvwaddstr(stdscr, window_piece*3+window_piece/7*6, max_col/2, version); // Draw version in the end piece

	return item_coords;
}

void GUI::print_string(const std::string & message) {
	int cur_row, cur_col;
	getyx(stdscr, cur_row, cur_col);

	mvwaddstr(stdscr, 0, 0, message.c_str());

	move(cur_row, cur_col);
}

void GUI::print_intel(int board_rows, const std::string & message){
	int cur_row, cur_col;
	getyx(stdscr, cur_row, cur_col);

	mvwaddstr(stdscr, BoardR0 + board_rows + WindowSpace + 2, BoardC0, message.c_str());

	move(cur_row, cur_col);
}

void GUI::draw_board_frame(int board_rows, int board_cols){
	int cur_row, cur_col;
	getyx(stdscr, cur_row, cur_col);

	mvaddch(BoardR0 - 1, BoardC0 - 1, FRAMETL);
	mvaddch(BoardR0 + board_rows, BoardC0 - 1, FRAMEBL);
	mvaddch(BoardR0 - 1, BoardC0 + board_cols, FRAMETR);
	mvaddch(BoardR0 + board_rows, BoardC0 + board_cols, FRAMEBR);

	mvhline(BoardR0 - 1, BoardC0, FRAMETS, board_cols);
	mvvline(BoardR0, BoardC0 - 1, FrameLS, board_rows);
	mvhline(BoardR0 + board_rows, BoardC0, FRAMEBS, board_cols);
	mvvline(BoardR0, BoardC0 + board_cols, FRAMERS, board_rows);

	move(cur_row, cur_col);
}

void GUI::draw_intel_frame(int board_rows){
	int cur_row, cur_col;
	getyx(stdscr, cur_row, cur_col);

	mvaddch(BoardR0 + 1 + WindowSpace + board_rows, BoardC0 - 1, FRAMETL);
	mvaddch(BoardR0 + 1 + WindowSpace + board_rows + IntelRows + 1, BoardC0 - 1, FRAMEBL);
	mvaddch(BoardR0 + 1 + WindowSpace + board_rows, BoardC0 + IntelCols, FRAMETR);
	mvaddch(BoardR0 + 1 + WindowSpace + board_rows + IntelRows + 1, BoardC0 + IntelCols, FRAMEBR);

	mvhline(BoardR0 + 1 + WindowSpace + board_rows, BoardC0, FRAMETS, IntelCols);
	mvvline(BoardR0 + 2 + WindowSpace + board_rows, BoardC0 - 1, FrameLS, IntelRows);
	mvhline(BoardR0 + 2 + WindowSpace + board_rows + IntelRows, BoardC0, FRAMEBS, IntelCols);
	mvvline(BoardR0 + 2 + WindowSpace + board_rows, BoardC0 + IntelCols, FRAMERS, IntelRows);

	move(cur_row, cur_col);
}

void GUI::clear_game(int board_rows, int board_cols) {
	int cur_row, cur_col;
	getyx(stdscr, cur_row, cur_col);
	for (int i = BoardR0; i < board_rows + BoardR0; ++i) {
		move(i, BoardC0);
		for (int j = 0; j < board_cols; ++j) {
			addch(' ');
		}
	}
	move(cur_row, cur_col);
}

void GUI::clear_intel(int board_rows){
	int cur_row, cur_col;
	getyx(stdscr, cur_row, cur_col);
	for (int i = BoardR0 + board_rows + WindowSpace + 2; i < BoardR0 + board_rows + WindowSpace + 2 + IntelRows; ++i) {
		move(i, BoardC0);
		for (int j = 0; j < IntelCols; ++j) {
			addch(' ');
		}
	}
	move(cur_row, cur_col);
}

void GUI::refresh(){
	wrefresh(stdscr); //Refresh curses
}

}
