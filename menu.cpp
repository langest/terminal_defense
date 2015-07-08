#include "menu.hpp"

namespace termd {

	Menu::Menu(Player& p) : player(p) {
		menu_items.push_back(std::string("Campain")); // item 0
		menu_items.push_back(std::string("Random Level")); // item 1
		menu_items.push_back(std::string("Level Select")); // item 2
		menu_items.push_back(std::string("Load Quicksave")); // item 3
		menu_items.push_back(std::string("Exit")); // item 4

		std::function<bool()> f = [this]() { return run_game(); };
		inputcalls[0] = f;
		inputcalls[1] = f;
		inputcalls[2] = f;
		f = [this]() {
			return load_quicksave(); //TODO Test if valid save-file
		};
		inputcalls[3] = f;
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

		std::vector<Coord> item_pos = print_menu();
		int ch;
		int current_item = 0;
		GUI::move_cursor(item_pos[current_item]);
		GUI::refresh();
		while((ch = GUI::get_input()) != 'q') {
			if (ch == 'j' || ch == KEY_DOWN) {
				current_item = (current_item + 1) % item_pos.size();
			}
			else if (ch == 'k' || ch == KEY_UP) {
				--current_item;
				if (current_item < 0) {
					current_item = item_pos.size()-1;
				}
			} else if ((ch == KEY_ENTER || ch == KEY_RIGHT || ch == 'l') && inputcalls.find(current_item) != inputcalls.end()) {
				inputcalls[current_item]();
			} else if ((ch == KEY_ENTER || ch == KEY_RIGHT || ch == 'l') && inputcalls.find(current_item) == inputcalls.end()) {
				break;
			}
			GUI::move_cursor(item_pos[current_item]);
		}
		clear_menu();

		outro();
		}

}
