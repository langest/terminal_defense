#ifndef termd_game
#define termd_game

#include <map>
#include <vector>
#include <functional>
#include <thread>
#include <chrono>

#include "definitions"
#include "gui.hpp"
#include "player.hpp"
#include "maps/gameboard.hpp"
#include "tower/towerloader.hpp"

namespace termd {

	class Game {
		private:
			Player& player;
			GameBoard board;

			bool build_tower(int);

			std::map<int, std::function<void()>> inputcalls;
			void awesome();
			void intro();
			void outro();
			void build_phase();
			bool invasion_phase();
			bool is_player_alive() const;
			int get_player_hp() const;
			void set_wave_number(int);
			void show_menu();
			bool save_game();
		public:
			Game(Player&, int);

			bool load_game();
			bool run();
			void unlock_tower(int);
	};

}

#endif //termd_game
