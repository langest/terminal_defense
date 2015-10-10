#include "game.hpp"

namespace termd {

	Game::Game(Player & p, std::string map_id) : player(p), board(player, map_id) {
		//initialize input calls
		std::function<void()> f = [this]() { GUI::move_cursor_left(); };
		inputcalls['h'] = f;
		inputcalls[KEY_LEFT] = f;

		f = [this]() { GUI::move_cursor_up(); };
		inputcalls['k'] = f;
		inputcalls[KEY_UP] = f;

		f = [this]() { GUI::move_cursor_right(board.get_size_cols()); };
		inputcalls['l'] = f;
		inputcalls[KEY_RIGHT] = f;

		f = [this]() { GUI::move_cursor_down(board.get_size_rows()); };
		inputcalls['j'] = f;
		inputcalls[KEY_DOWN] = f;

		f = [this]() { show_menu(); };
		inputcalls['m'] = f;

		
		//Reading tower build buttons from file
		Tower_loader tl;
		std::vector<int> tids = tl.id_list();

		for (int id : tids) {
			inputcalls[id] = [&, id]() { build_tower(id); };
		}
	}

	bool Game::build_tower(int tower_id) {
		Coord c = GUI::get_cursor_pos();
		c -= Coord(BoardR0, BoardC0);
		board.build_tower(c, tower_id);
		return true;
	}

	void Game::intro() {
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
y - Build a DOWN TOWER \n\
d - Build a RIGHT TOWER \n\
w - Build a WALL \n\
MOVE CURSOR as you normally would (arrows or vim-like)\n");
		GUI::print_string(intromsg);
		GUI::get_input();
		clear();
		move(BoardR0, BoardC0);
	}

	void Game::outro() {
		clear();
		move(0,0);
		if (player.is_alive()) {
			GUI::print_string(std::string("gz, you won"));
		} else {
			GUI::print_string(std::string("You lost control over your terminal. There is nothing you can do..."));
		}
		GUI::get_input();
	}

	void Game::build_phase() {
		int ch;
		GUI::draw_board_frame(board.get_size_rows(), board.get_size_cols());
		GUI::draw_intel_frame(board.get_size_rows());
		char intelmsg[IntelCols];
		while((ch = GUI::get_input()) != 27 && ch != 'q') {
			if (inputcalls.find(ch) != inputcalls.end()) {
				inputcalls[ch]();
			}
			board.draw();
			GUI::clear_intel(board.get_size_cols());
			sprintf(intelmsg, "RAM: %d\t Terminal Control Points: %d", player.get_ram(), player.get_cp());
			GUI::print_intel(board.get_size_rows(), intelmsg);
			GUI::refresh();
		}
	}

	bool Game::invasion_phase() {
		char intelmsg[IntelCols];

		//Frame counter setup
		std::queue<std::chrono::time_point<std::chrono::high_resolution_clock> > timestamps;
		std::chrono::time_point<std::chrono::high_resolution_clock> avglimit;
		std::size_t avgseconds = 1;
		std::chrono::milliseconds avgtime(1000 * avgseconds);
		std::size_t avgfps;

		//Framerate limiter setup
		std::chrono::milliseconds interval(1000/Frames);
		std::chrono::time_point<std::chrono::high_resolution_clock> last_update(
				std::chrono::system_clock::now() - interval );
		std::chrono::time_point<std::chrono::high_resolution_clock> cur_update;

		while (board.update()) {
			//Framerate counter
			avglimit = std::chrono::system_clock::now() - avgtime;
			while (!timestamps.empty() && timestamps.front() < avglimit) {
				timestamps.pop();
			}
			timestamps.push(std::chrono::system_clock::now());
			avgfps = timestamps.size() / avgseconds;

			//Framerate limiter
			board.draw();
			GUI::clear_intel(board.get_size_rows());
			sprintf(intelmsg, "RAM: %d\t Terminal Control Points: %d\t FPS: %zd", player.get_ram(), player.get_cp(), avgfps);
			GUI::print_intel(board.get_size_rows(), intelmsg);
			GUI::refresh();

			cur_update = std::chrono::system_clock::now();
			auto sleep_dur = 2 * interval - std::chrono::duration_cast<std::chrono::milliseconds>(cur_update - last_update);
			last_update = cur_update;
			std::this_thread::sleep_for(sleep_dur);
		}
		board.draw();//Redraw the board so all projectiles are removed TODO prettier solution since this just instantly removes all their gfx.
		return board.next_wave();
	}

	bool Game::run() {
		intro();
		build_phase();
		while (invasion_phase()) {
			if(false == is_player_alive()) {
				outro();
				return false;
			}
			if(player.get_cp() < player.get_max_cp()) {
				unlock_tower(1); //TODO remove hardcodedness
			}
			build_phase();
		}
		outro();
		return true;
	}

	bool Game::is_player_alive() const {
		return player.is_alive();
	}

	//board.set_wave_number(int) has check for negative numbers
	void Game::set_wave_number(int num) {
		//board.set_wave_number(num); TODO needed for saving game
	}

	void Game::show_menu() {
		char ch;
		bool done = false;
		while (!done) {
			GUI::clear_intel(board.get_size_rows());
			GUI::print_intel(board.get_size_rows(), std::string("1.Save and quit    2.Return to game"));
			while ((ch = GUI::get_input()) != '1' && ch != '2');

			if (ch == '1') {
				if (save_game()) {
					//TODO save game get wavenumber
					done = true;
				} else {
					GUI::print_intel(board.get_size_rows(), std::string("Failed to save game, press any key to resume menu."));
					GUI::get_input();
				}
			} else {
				done = true;
			}
		}
		GUI::clear_intel(board.get_size_rows());
	}

	bool Game::save_game() {
		bool b1 = player.save_to_file(std::string("player.save"));
		bool b2 = board.save_to_file();
		return b1 && b2;
	}

	bool Game::load_game() {
		return board.load_from_file();
	}

	void Game::unlock_tower(int id) {
		//TODO - removed hardcodedness
		GUI::print_intel(board.get_size_rows(), "TOWER UNLOCKED! - Button 'd' - RIGHT SHOTING TOWER");
		player.unlock_tower(id);
		GUI::get_input(); //make sure to display the intel!
	}


}
