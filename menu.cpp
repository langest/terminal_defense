#include "menu.hpp"

namespace termd {

	Menu::Menu(Player& p) : player(p) {
		menu_items.push_back(std::string("Campain"));
		menu_items.push_back(std::string("Random Level"));
		menu_items.push_back(std::string("Level Select"));
		menu_items.push_back(std::string("Load Quicksave"));
		menu_items.push_back(std::string("Exit"));

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

	std::vector<Coord> Menu::print_menu() {
		return GUI::print_menu_items(menu_items);
	}

	void Menu::clear_menu() {
		GUI::clear_intel(0);
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

		//TODO restructure here
		std::vector<Coord> item_pos = print_menu();
		int ch;
		int current_item = 0;
		GUI::move_cursor(item_pos[current_item]);
		GUI::refresh();
		while((ch = GUI::get_input()) != '3') {
			if (ch == 'j' || ch == KEY_DOWN) {
				current_item = (current_item + 1) % item_pos.size();
			}
			if (ch == 'k' || ch == KEY_UP) {
				--current_item;
				if (current_item < 0) {
					current_item = item_pos.size()-1;
				}
			} else if (inputcalls.find(ch) != inputcalls.end()) {
				inputcalls[ch]();
			}
			GUI::move_cursor(item_pos[current_item]);
		}
		clear_menu();

		outro();
		}

}
