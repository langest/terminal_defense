#include "main.hpp"

int main() {
	initscr(); //Starts curses mode
	cbreak(); //Since we only want to read characters
	noecho(); //Turns off echo of input
	keypad(stdscr, TRUE);
	
	Game game;

	game.build_phase();
	
	endwin(); //End curses mode
	return 0;
}

void Game::build_phase() {
	int ch;
	while((ch = getch()) != 27) {
		switch (ch) {
			case KEY_LEFT:
			case 'h':
				gui.move_cursor_left();
				break;
			case KEY_RIGHT:
			case 'l':
				gui.move_cursor_right();
				break;
			case KEY_UP:
			case 'k':
				gui.move_cursor_up();
				break;
			case KEY_DOWN:
			case 'j':
				gui.move_cursor_down();
				break;
			default:
				break;
		}
		gui.refresh();
	}
}
