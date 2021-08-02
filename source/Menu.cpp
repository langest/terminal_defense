#include <Menu.h>

#include <ncurses.h>

#include <Game.h>
#include <Gui.h>

namespace termd {

CMenu::CMenu()
    : mPlayer(10, 10)
    , mItems({ std::string("Campain"),
          std::string("Random Level"),
          std::string("Level Select"),
          std::string("Exit") })
    , mInputCallbacks()
{
    std::function<void()> f = [this]() { this->runGame(); };
    mInputCallbacks[0] = f;
    mInputCallbacks[1] = f;
    mInputCallbacks[2] = f;
}

void CMenu::run()
{
    std::vector<CCoordinate> itemPositions = this->printMenu();
    int ch;
    int currentItem = 0;
    GUI::moveCursor(itemPositions[currentItem]);
    GUI::refresh();
    while ((ch = GUI::getInput()) != 'q') {
        if (ch == 'j' || ch == KEY_DOWN) {
            currentItem = (currentItem + 1) % itemPositions.size();
        } else if (ch == 'k' || ch == KEY_UP) {
            --currentItem;
            if (currentItem < 0) {
                currentItem = itemPositions.size() - 1;
            }
        } else if ((ch == KEY_ENTER || ch == KEY_RIGHT || ch == 'l') && mInputCallbacks.find(currentItem) != mInputCallbacks.end()) {
            mInputCallbacks[currentItem]();
            break;
        } else if ((ch == KEY_ENTER || ch == KEY_RIGHT || ch == 'l') && mInputCallbacks.find(currentItem) == mInputCallbacks.end()) {
            break;
        }
        GUI::moveCursor(itemPositions[currentItem]);
    }
    this->clearMenu();
}

std::vector<CCoordinate> CMenu::printMenu()
{
    return GUI::printMenuItems(mItems);
}

void CMenu::clearMenu()
{
    GUI::clearScreen();
}

void CMenu::runGame()
{
    CGame game(mPlayer);
    this->clearMenu();
    game.run();
}

}
