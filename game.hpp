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

#include "definitions"
#include "gui.hpp"
#include "player.hpp"
#include "maps/gameboard.hpp"

namespace termd {

	class Game {
		private:
			GUI gui;
			Player player;
			GameBoard board;

			bool build_tower(int);

			std::map<int, std::function<void()>> inputcalls;
		public:
			Game();
			
			void intro();
			void outro();
			void build_phase();
			void invasion_phase();
	};

}

#endif //termd_game
