#include <Game.h>

#include <string>
#include <map>
#include <thread>
#include <chrono>
#include <vector>
#include <queue>

#include <Coordinate.h>
#include <Player.h>

namespace {
	const int numBoardRows = 10;
	const int numBoardCols = 16;
	const int intelMessageBufferSize = 4 * numBoardCols;
	const int numIntelRows = 2;
	const int frameRate = 30;
}

namespace termd {

CGame::CGame(CPlayer& player) :
	mPlayer(player),
	mGameBoard(player, numBoardRows, numBoardCols),
	mLogger(__FILE__) {}

void CGame::intro() {
	const char* introMessage("You are a hacker minding your own business when suddenly viruses are invading your terminal! \n\
Viruses , as you all know, begins on the right side and runs over to the left side. \n\
You lose 1 terminal control point if you let a virus get to the left making you lose some control. \n\
You lose when you lose control over your terminal (reach 0 terminal control points). \n\
You win by defeating ALL the viruses! \n\
\n\
You defend your terminal by building towers.\n\
Towers costs RAM to build, you gain more RAM by destroying viruses\n\
\n\
q - Start the next wave of viruses \n\
i - Build a BASIC TOWER \n\
y - Build a DOWN TOWER \n\
d - Build a RIGHT TOWER \n\
w - Build a WALL \n\
MOVE CURSOR as you normally would (arrows or vim-like)\n");
	GUI::printText(CCoordinate(0, 0), introMessage, -1);
	GUI::getInput();
	GUI::clearScreen();
}

void CGame::handleInput(const char input) {
	switch (input) {
		case 'h': {
			mGameBoard.moveCursorLeft();
			break;
		}
		case 'j': {
			mGameBoard.moveCursorDown();
			break;
		}
		case 'k': {
			mGameBoard.moveCursorUp();
			break;
		}
		case 'l': {
			mGameBoard.moveCursorRight();
			break;
		}
		case 'm': {
			this->runMenu();
			break;
		}
		case 'w': {
			mGameBoard.buildTower();
			break;
		}
		default: {
			break;
		}
	}
}

void CGame::outro() {
	GUI::moveCursor(CCoordinate(0,0));
	GUI::getInput();
	GUI::clearScreen();
}

void CGame::runBuildPhase() {
	mLogger.log("runBuildPhase");
	// Draw game board frame
	GUI::drawFrame(
		CCoordinate(0, 0),
		CCoordinate(mGameBoard.getSizeRows() + 1, mGameBoard.getSizeCols() + 1));
	// Draw intel frame
	GUI::drawFrame(
		CCoordinate(mGameBoard.getSizeRows() + 2, 0),
		CCoordinate(mGameBoard.getSizeRows() + 2 + numIntelRows, mGameBoard.getSizeCols() + 1));
	char intelMessage[intelMessageBufferSize];

	char input;
	while((input = GUI::getInput()) != 27 && input != 'q') {
		mLogger.log("got input %c", input);
		this->handleInput(input);
		GUI::clearRectangle(
			CCoordinate(1, 1),
			CCoordinate(mGameBoard.getSizeRows(), mGameBoard.getSizeCols()));
		snprintf(
			intelMessage,
			intelMessageBufferSize,
			"RAM: %d\t Terminal Control Points: %d",
			mPlayer.getRam(),
			mPlayer.getControlPoints()
		);
		//TODO move all gui prints to gameboard
		GUI::printText(CCoordinate(mGameBoard.getSizeRows() + 3, 1), intelMessage, mGameBoard.getSizeCols() - 1); // Add/subtract borders
		mGameBoard.draw();
		GUI::refresh();
	}
}

bool CGame::runInvasionPhase() {
	mLogger.log("Run invasion phase");
	char intelMessage[intelMessageBufferSize];

	mGameBoard.initInvasion();

	//Frame counter setup
	std::queue<std::chrono::time_point<std::chrono::high_resolution_clock> > timestamps;
	std::chrono::time_point<std::chrono::high_resolution_clock> avglimit;
	std::size_t avgseconds = 1;
	std::chrono::milliseconds avgtime(1000 * avgseconds);
	std::size_t avgfps;

	//Framerate limiter setup
	std::chrono::milliseconds interval(1000/frameRate);
	std::chrono::time_point<std::chrono::high_resolution_clock> lastUpdate(
			std::chrono::system_clock::now() - interval );
	std::chrono::time_point<std::chrono::high_resolution_clock> curUpdate;

	while (mGameBoard.update()) {
		//Framerate counter
		avglimit = std::chrono::system_clock::now() - avgtime;
		while (!timestamps.empty() && timestamps.front() < avglimit) {
			timestamps.pop();
		}
		timestamps.push(std::chrono::system_clock::now());
		avgfps = timestamps.size() / avgseconds;

		//Framerate limiter
		mGameBoard.draw();
		GUI::clearRectangle(
			CCoordinate(mGameBoard.getSizeRows() + 3, 1),
			CCoordinate(mGameBoard.getSizeRows() + numIntelRows, mGameBoard.getSizeCols() - 2));
		snprintf(
			intelMessage,
			intelMessageBufferSize,
			"RAM: %d\t Terminal Control Points: %d\t FPS: %zd",
			mPlayer.getRam(),
			mPlayer.getControlPoints(),
			avgfps
		);
		GUI::printText(CCoordinate(mGameBoard.getSizeRows() + 3, 1), intelMessage, mGameBoard.getSizeCols() - 1); // Add/subtract borders
		GUI::refresh();

		curUpdate = std::chrono::system_clock::now();
		auto sleepMilliseconds = 2 * interval - std::chrono::duration_cast<std::chrono::milliseconds>(curUpdate - lastUpdate);
		lastUpdate = curUpdate;
		std::this_thread::sleep_for(sleepMilliseconds);
	}
	mGameBoard.draw();//Redraw the mGameBoard so all projectiles are removed TODO prettier solution since this just instantly removes all their gfx.
	return mGameBoard.hasNextWave();

}

bool CGame::run() {
	this->intro();
	mGameBoard.resetCursor();
	this->runBuildPhase();
	while (runInvasionPhase()) {
		if(!mPlayer.isAlive()) {
			mLogger.log("Player not alive anymore");
			this->outro();
			return false;
		}
		this->runBuildPhase();
	}
	this->outro();
	return true;
}

void CGame::runMenu() {
	GUI::clearScreen();
	const char* intelMessage = "1.Quit Game    2.Return to game";
	GUI::printText(CCoordinate(mGameBoard.getSizeRows() + 3, 1), intelMessage, mGameBoard.getSizeCols() - 1); // Add/subtract borders

	char input;
	while ((input = GUI::getInput()) != '1' && input != '2');

	GUI::clearScreen();
}

}
