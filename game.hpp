#ifndef termd_game
#define termd_game

#ifndef termd_map
#define termd_map
#include <map>
#endif

#ifndef termd_functional
#define termd_functional
#include <functional>
#endif

#ifndef termd_thread
#define termd_thread
#include <thread>
#endif

#ifndef termd_chrono
#define termd_chrono
#include <chrono>
#endif

#include "definitions"
#include "gui.hpp"
#include "player.hpp"
#include "maps/gameboard.hpp"

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
			void invasion_phase();
			bool is_player_alive() const;
			int get_player_hp() const;
			unsigned int get_number_of_waves() const;
			void set_wave_number(unsigned int);
			void show_menu() const;
			void save_game() const;
		public:
			Game(Player&);

			bool run();
			void unlock_tower(int);
	};

}

#endif //termd_game
