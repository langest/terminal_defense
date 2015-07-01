#ifndef termd_menu
#define termd_menu

#include <string>

#include "player.hpp"
#include "gui.hpp"
#include "game.hpp"

namespace termd {

	class Menu {
		private:
			Player& player;
			std::map<int, std::function<bool()>> inputcalls;
			void intro();
			void outro();
			void print_menu();
			void clear_menu();
			bool run_game();
			bool load_quicksave();

		public:
			Menu(Player&);

			//blocking until menu is exited
			void run();
	};

}

#endif
