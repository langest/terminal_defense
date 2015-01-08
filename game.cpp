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

		inputcalls['+'] = std::bind( &Game::awesome, this );
	}

	void Game::awesome() {
		gui.print_intel("Thomas and Daniel are awesome!\nYeah. Foh shoo!");
	}
	
	bool Game::build_tower(int tower_id) {
		Coord c = gui.get_cursor_pos();
		c -= Coord(BOARDR0, BOARDC0);
		board.build_tower(c, tower_id);
		return true;
	}

	void Game::intro() {
#ifndef MOCK_GUI
		std::string intromsg("You are a hacker minding your own business when suddenly viruses are invading your terminal! \n\
Viruses (as you all know) begins on the right side and flies to the left. \n\
You lose 1 terminal control point if you let a virus get to the left making you lose some control. \n\
You lose when you lose control over your terminal (reach 0 terminal control points). \n\
You win by defeating ALL the viruses! \n\
\n\
You defend your terminal by building towers.\n\
Towers costs RAM to build, you gain more RAM by destroying viruses\n\
\n\
q - Start the next wave of viruses \n\
i - Build a BASIC TOWER \n\
MOVE CURSOR as you normally would (arrows or vim-like)\n");
		addstr(intromsg.c_str());
		getch();
		clear();
		move(BOARDR0, BOARDC0);
#endif
	}

	void Game::outro() {
#ifndef MOCK_GUI
		clear();
		move(0,0);
		if (player.is_alive()) {
			addstr("gz, you won");
		} else {
			addstr("You lost control over your terminal. There is nothing you can do...");
		}
		getch();
#endif
	}

	void Game::build_phase() {
		int ch;
		gui.draw_board_frame();
		gui.draw_intel_frame();
		char intelmsg[BOARDCOLS];
#ifndef MOCK_GUI
		while((ch = getch()) != 27 && ch != 'q') {
#else
		{
#endif
			if (inputcalls.find(ch) != inputcalls.end()) {
				inputcalls[ch]();
			}
			board.draw(gui);
			gui.clear_intel();
			sprintf(intelmsg, "RAM: %d\t Terminal Control Points: %d", player.get_ram(), player.get_hp());
			gui.print_intel(intelmsg);
			gui.refresh();
		}
	}

	void Game::invasion_phase() {
		int ch;
		board.spawn_virus(0);
		char intelmsg[BOARDCOLS];
		while (board.update()) {
			board.draw(gui);
			gui.clear_intel();
			sprintf(intelmsg, "RAM: %d\t Terminal Control Points: %d", player.get_ram(), player.get_hp());
			gui.print_intel(intelmsg);
			gui.refresh();
#ifndef MOCK_GUI
			if ((ch = getch()) == 27 || ch == 'q') {
				break;
			}
#endif
		}
	}

	bool Game::is_player_alive() const {
		return player.is_alive();
	}

	int Game::get_player_hp() const {
		return player.get_hp();
	}

	void Game::unlock_tower(int id) {
		//TODO - removed hardcodedness
		gui.print_intel("TOWER UNLOCKED! - Button 'd' - RIGHT SHOTING TOWER");
		player.unlock_tower(id);
#ifndef MOCK_GUI
		getch(); //make sure to display the intel!
#endif
	}


}
