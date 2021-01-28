#include <Menu.h>

#include <Game.h>
#include <Gui.h>

namespace termd {

CMenu::CMenu() :
	mPlayer(10, 10),
	mItems({
			std::string("Campain"),
			std::string("Random Level"),
			std::string("Level Select"),
			std::string("Exit")
			}),
	mInputCallbacks() {
		std::function<void()> f = [this]() { runGame(); };
		mInputCallbacks[0] = f;
		mInputCallbacks[1] = f;
		mInputCallbacks[2] = f;
	}

void CMenu::run() {
	intro();

	std::vector<CCoordinate> itemPositions = printMenu();
	int ch;
	int currentItem = 0;
	GUI::move_cursor(itemPositions[currentItem]);
	GUI::refresh();
	while((ch = GUI::get_input()) != 'q') {
		if (ch == 'j' || ch == KEY_DOWN) {
			currentItem = (currentItem + 1) % itemPositions.size();
		}
		else if (ch == 'k' || ch == KEY_UP) {
			--currentItem;
			if (currentItem < 0) {
				currentItem = itemPositions.size()-1;
			}
		} else if ((ch == KEY_ENTER || ch == KEY_RIGHT || ch == 'l') && mInputCallbacks.find(currentItem) != mInputCallbacks.end()) {
			mInputCallbacks[currentItem]();
		} else if ((ch == KEY_ENTER || ch == KEY_RIGHT || ch == 'l') && mInputCallbacks.find(currentItem) == mInputCallbacks.end()) {
			break;
		}
		GUI::move_cursor(itemPositions[currentItem]);
	}
	clearMenu();

	outro();
}

void CMenu::intro() {

}

void CMenu::outro() {

}

std::vector<CCoordinate> CMenu::printMenu() {
	return GUI::print_menu_items(mItems);
}

void CMenu::clearMenu() {
	GUI::clear_intel(0);
}

void CMenu::runGame() {
	CGame game(mPlayer);
	game.run();
}

}
