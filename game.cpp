#include "game.hpp"

namespace termd {

	Game::Game() : board(player) {
		//initialize input calls
		std::function<void()> f = [&]() { gui.move_cursor_left(); };
		inputcalls['h'] = f;
		inputcalls[KEY_LEFT] = f;

		f = [&]() { gui.move_cursor_up(); };
		inputcalls['k'] = f;
		inputcalls[KEY_UP] = f;

		f = [&]() { gui.move_cursor_right(); };
		inputcalls['l'] = f;
		inputcalls[KEY_RIGHT] = f;

		f = [&]() { gui.move_cursor_down(); };
		inputcalls['j'] = f;
		inputcalls[KEY_DOWN] = f;

		inputcalls['i'] = [&]() { build_tower(BASIC_TOWER_1x1_ID); };
		inputcalls['d'] = [&]() { build_tower(RIGHT_TOWER_1x1_ID); };
	}

	
	bool Game::build_tower(int tower_id) {
		Coord c = gui.get_cursor_pos();
		c -= Coord(BOARDR0, BOARDC0);
		board.build_tower(c, tower_id);
		return true;
	}

	void Game::intro() {
		addstr("awesome game YOLO!");
		getch();
		clear();
		move(BOARDR0, BOARDC0);
	}

	void Game::outro() {
		clear();
		move(0,0);
		if (player.is_alive()) {
			addstr("gz, you won");
		} else {
			addstr("gz, you lose");
		}
		getch();
	}

	void Game::build_phase() {
		int ch;
		gui.draw_board_frame();
		gui.draw_intel_frame();
		while((ch = getch()) != 27 && ch != 'q') {
			if (inputcalls.find(ch) != inputcalls.end()) {
				inputcalls[ch]();
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

}
