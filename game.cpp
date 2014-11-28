#include "game.hpp"

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
