#pragma once

#include <set>

#include <virus/VirusManager.h>
#include <tower/TowerManager.h>

namespace termd {

class CCoordinate;
class CPlayer;

class CGameBoard {
	public:
		CGameBoard(CPlayer& player);
		CGameBoard(const CGameBoard &) = delete;
		CGameBoard& operator=(const CGameBoard &) = delete;

		void draw() const;
		bool update();
		bool buildTower(const CCoordinate& coordinate);
		bool hasNextWave() const;

		const int getSizeRows() const;
		const int getSizeCols() const;

	private:
		bool isBlockedWith(const CCoordinate& coordinate);
		void loadMap();

		CPlayer& player;
		const int mSizeRows;
		const int mSizeCols;
		CTowerManager mTowerManager;
		CVirusManager mVirusManager;
};

}
