#include "menu.hpp"

namespace termd {

	Menu::Menu(GUI& g, Player& p) : gui(g), player(p) {
		std::function<bool()> f = [this]() { return run_game(); };
		inputcalls['1'] = f;
	}

	void Menu::intro() {

	}

	void Menu::outro() {

	}

	void Menu::print_menu() {
		gui.print_intel(std::string("1. New game   2. Continue\n")+
										std::string("3. Exit game"));
	}

	void Menu::clear_menu() {
		gui.clear_intel();
	}

	bool Menu::run_game() {
		Game game(gui, player);
		return game.run();
	}

	void Menu::run() {
		intro();

		print_menu();
		char ch;
		while((ch = getch()) != 27 && ch != '3') {
			clear_menu();
			if (inputcalls.find(ch) != inputcalls.end()) {
				inputcalls[ch]();
			}
			print_menu();
		}
		clear_menu();

		outro();
		}

}
