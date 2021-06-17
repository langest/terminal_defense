#pragma once

#include <set>

#include <logging/Logger.h>
#include <tower/TowerManager.h>
#include <virus/VirusManager.h>

namespace termd {

class CCoordinate;
class CPlayer;

class CGameBoard {
	public:
		CGameBoard(CPlayer& player);
		CGameBoard(const CGameBoard &) = delete;
		CGameBoard& operator=(const CGameBoard &) = delete;

		void resetCursor();
		void moveCursorLeft();
		void moveCursorDown();
		void moveCursorUp();
		void moveCursorRight();

		void draw();
		void initInvasion();
		bool update();
		bool buildTower();
		bool hasNextWave() const;

		int getSizeRows() const;
		int getSizeCols() const;

	private:
		void drawCall(const CCoordinate& position, char graphic);

		bool isBlockedWith(const CCoordinate& coordinate);
		void loadMap();

		CPlayer& mPlayer;
		const int mStartRow;
		const int mStartCol;
		const int mSizeRows;
		const int mSizeCols;
		std::set<CCoordinate> mStartPositions;
		std::set<CCoordinate> mEndPositions;
		CTowerManager mTowerManager;
		CVirusManager mVirusManager;
		bool mHasMoreToDo;

		CLogger mLogger;
};

}
