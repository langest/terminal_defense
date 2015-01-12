#ifndef termd_menu
#define termd_menu

#ifndef termd_string
#define termd_string
#include <string>
#endif

#include "player.hpp"
#include "gui.hpp"
#include "game.hpp"

namespace termd {

	class Menu {
		private:
			GUI& gui;
			Player& player;
			std::map<int, std::function<bool()>> inputcalls;
			void intro();
			void outro();
			void print_menu();
			void clear_menu();
			bool run_game();

		public:
			Menu(GUI&, Player&);

			//blocking until menu is exited
			void run();
	};

}

#endif
