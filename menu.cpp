#include "menu.hpp"

namespace termd {

	Menu::Menu(GUI& g, Player& p) : gui(g), player(p) {}

	void Menu::intro() {

	}

	void Menu::outro() {

	}

	void Menu::run() {
		intro();

		Game game(gui, player);
		game.run();

		outro();
		}

}
