#include "gui.hpp"

GUI::GUI(){
	main_win = create_new_win(10, 10, 0, 0);

	initscr(); //Starts curses mode
	cbreak(); //Since we only want to read characters
	noecho(); //Turns off echo of input
}

GUI::~GUI() {
	destroy_win(main_win);
	endwin(); //End curses mode
}

bool GUI::move_cursor_up() {
	int x,y;
	getyx(main_win, y, x);

	if (y < 1) {
		return false;
	}
	move(x,y-1); //Move cursor
	return true;
}

bool GUI::move_cursor_down() {
	int max_x, max_y;
	getmaxyx(main_win,max_y, max_x);
	int x,y;
	getyx(main_win, y, x);

	if (y >= max_y) {
		return false;
	}
	move(x,y+1); //Move cursor
	return true;
}

bool GUI::move_cursor_left() {
	return false;
}

bool GUI::move_cursor_right() {
	return false;
}

bool GUI::draw(Coord coord, char ch) {
	return false;
}

void GUI::clear() {
	clear(); //Clear curses
}

void GUI::refresh() {
	refresh(); //Refresh curses
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
