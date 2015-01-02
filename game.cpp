#include "game.hpp"

Game::Game() : board(player) {}

bool Game::build_tower(int tower_id) {
	Coord c = gui.get_cursor_pos();
	c -= Coord(BOARDR0, BOARDC0);
	board.build_tower(c, tower_id);
	return true;
}

void Game::build_phase() {
	int ch;
	gui.draw_board_frame();
	gui.draw_intel_frame();
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
				this->build_tower(BASIC_TOWER_1x1_ID);
			default:
				break;
		}
		board.draw(gui);
		gui.refresh();
	}
}

void Game::invasion_phase() {
	int ch;
	board.spawn_virus(0);
	while (board.update()) {
		board.draw(gui);
		gui.refresh();
		if ((ch = getch()) == 27 || ch == 'q') {
			break;
		}
	}
}
