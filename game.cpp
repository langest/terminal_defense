#include "game.hpp"

bool Game::build_tower(int tower_id) {
	Coord c = gui.get_cursor_pos();
	board.build_tower(c, tower_id);
	board.render(gui); //TODO move away from here
	return true;
}

void Game::build_phase() {
	gui.draw_board_frame();
	gui.draw_intel_frame();
	int ch;
	while((ch = getch()) != 27 && ch != 'q') {
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
			case 'b':
				this->build_tower(1);
			default:
				break;
		}
		gui.refresh();
	}
}

void Game::invasion_phase() {
	//TODO loop
	board.update();
}
