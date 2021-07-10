#pragma once


#include <Gui.h>
#include <GameBoard.h>

namespace termd {

class CPlayer;

class CGame {
	public:
		CGame(CPlayer& player);

		bool load_game();
		bool run();
		void unlock_tower(int);

	private:
		void intro();
		void outro();
		void handleInput(const char input);
		void runBuildPhase();
		bool runInvasionPhase();
		void runMenu();

		CPlayer& mPlayer;
		CGameBoard mGameBoard;
		CLogger mLogger;
};

}
