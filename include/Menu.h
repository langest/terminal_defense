#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>

#include <Coordinate.h>
#include <Player.h>

namespace termd {

class CPlayer;

class CMenu {
	public:
		CMenu();

		void run();

	private:
		void intro();
		void outro();
		std::vector<CCoordinate> printMenu();
		void clearMenu();
		void runGame();

		CPlayer mPlayer;
		const std::vector<std::string> mItems;
		std::map<int, std::function<void()>> mInputCallbacks;
};

}
