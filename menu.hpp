#ifndef termd_menu
#define termd_menu

#include "player.hpp"
#include "gui.hpp"
#include "game.hpp"

namespace termd {

	class Menu {
		private:
			GUI& gui;
			Player& player;
			void intro();
			void outro();

		public:
			Menu(GUI&, Player&);

			//blocking until menu is exited
			void run();
	};

}

#endif
