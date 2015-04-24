#include "menu.hpp"

namespace termd {

	Menu::Menu(Player& p) : player(p) {
		std::function<bool()> f = [this]() { return run_game(); };
		inputcalls['1'] = f;
		f = [this]() {
			return load_quicksave(); //TODO Test if valid save-file
		};
		inputcalls['2'] = f;
	}

	void Menu::intro() {

	}

	void Menu::outro() {

	}

	void Menu::print_menu() {
		GUI::print_intel(std::string("1. New game   2. Load quicksave\n")+
										std::string("3. Exit game"));
	}

	void Menu::clear_menu() {
		GUI::clear_intel();
	}

	bool Menu::run_game() {
		Game game(player, "map1"); //TODO remove hardcodedness
		return game.run();
	}

	bool Menu::load_quicksave() {
		Game game(player, "map1"); //TODO remove hardcodedness
		game.load_game();
		return game.run();
	}

	void Menu::run() {
		intro();

		print_menu();
		char ch;
		while((ch = GUI::get_input()) != '3') {
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
