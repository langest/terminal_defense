#include <GameBoard.h>

#include <functional>
#include <queue>

#include <Gui.h>
#include <tower/Wall.h>

namespace termd {

CGameBoard::CGameBoard(CPlayer& player) :
	mPlayer(player),
	mStartRow(1),
	mStartCol(1),
	mSizeRows(10),
	mSizeCols(10),
	mTowerManager(),
	mVirusManager(mPlayer),
	mHasMoreToDo(false),
	mLogger(__FILE__) {
		loadMap();
		for (int i = 0; i < mSizeRows; ++i) {
			mStartPositions.emplace(CCoordinate(i, mSizeCols - 1));
			mEndPositions.emplace(CCoordinate(i, 0));
		}
	}

void CGameBoard::resetCursor() {
	GUI::moveCursor(CCoordinate(
		(mStartRow + mSizeRows) / 2,
		(mStartCol + mSizeCols) / 2));
}

void CGameBoard::moveCursorLeft() {
	GUI::moveCursorLeft(mStartCol);
}

void CGameBoard::moveCursorDown() {
	GUI::moveCursorDown(mStartRow + mSizeRows - 1);
}

void CGameBoard::moveCursorUp() {
	GUI::moveCursorUp(mStartRow);
}

void CGameBoard::moveCursorRight() {
	GUI::moveCursorRight(mStartCol + mSizeCols - 1);
}

void CGameBoard::draw() {
	GUI::clearScreen();

	mTowerManager.drawTowers(std::bind(&CGameBoard::drawCall, this, std::placeholders::_1, std::placeholders::_2));
	mVirusManager.drawViruses(std::bind(&CGameBoard::drawCall, this, std::placeholders::_1, std::placeholders::_2));
	GUI::drawFrame(
		CCoordinate(0, 0),
		CCoordinate(mSizeRows + 1, mSizeCols + 1));
}

void CGameBoard::initInvasion() {
	if (mHasMoreToDo) {
		mLogger.logError("Tried to init invasion while already having one started");
		return; // Do not start multiple invasions
	}
	mVirusManager.initInvasion(mStartPositions, mEndPositions, mTowerManager.getTowers());
	// TODO mTowerManager.initInvasion();
}

bool CGameBoard::update() {
	mLogger.log("Update");
	mHasMoreToDo = mVirusManager.update();
	mTowerManager.updateTowers();
	if (!mHasMoreToDo) {
		mLogger.log("Nothing more to do, finishing invasion");
		mVirusManager.finishInvasion();
		// TODO mTowerManager.finishInvasion();
	}
	return mHasMoreToDo;
}

bool CGameBoard::buildTower() {
	const CCoordinate cursorPosition = GUI::getCursorPosition();
	const int row = cursorPosition.getRow() - mStartRow;
	const int col = cursorPosition.getCol() - mStartCol;
	const CCoordinate buildPosition(row, col);
	mLogger.log("Trying to build tower at (%d, %d)", row, col);
	if (col < 0 ||
		col >= mSizeCols ||
		row < 0 ||
		row >= mSizeRows ||
		mTowerManager.isTowerAt(buildPosition)) {
		return false;
	}

	if (this->isBlockedWith(buildPosition)) {
		return false;
	}

	return mTowerManager.placeTower(buildPosition, std::make_unique<CWall>());
}

bool CGameBoard::hasNextWave() const {
	return mVirusManager.hasNextWave();
}

int CGameBoard::getSizeRows() const {
	return mSizeRows;
}

int CGameBoard::getSizeCols() const {
	return mSizeCols;
}

void CGameBoard::drawCall(const CCoordinate& position, char graphic) {
	GUI::draw(position + CCoordinate(mStartRow, mStartCol), graphic);
}

bool CGameBoard::isBlockedWith(const CCoordinate& coordinate) {
	if (mStartPositions.contains(coordinate)) {
		return true;
	}
	std::vector<std::vector<int>> visited(mSizeRows, std::vector<int>(mSizeCols, 0));

	visited[coordinate.getRow()][coordinate.getCol()] = 1;
	std::queue<CCoordinate> queue;

	for (const CCoordinate& startPosition: mStartPositions) {
		if (mTowerManager.isTowerAt(startPosition) ||
			visited[startPosition.getRow()][startPosition.getCol()]) {
			continue;
		}
		queue.push(startPosition);
		visited[startPosition.getRow()][startPosition.getCol()] = 1;
	}

	while (!queue.empty()) {
		const CCoordinate& current = queue.front();
		const int r = current.getRow();
		const int c = current.getCol();
		if (mEndPositions.contains(current)) {
			return false;
		}
		queue.pop();

		const int under = r + 1;
		if (under < mSizeRows &&
			!visited[under][c] &&
			!mTowerManager.isTowerAt(CCoordinate(under,c))) {
			visited[under][c] = 1;
			queue.push(CCoordinate(under, c));
		}
		const int above = r - 1;
		if (above >= 0 &&
			!visited[above][c] &&
			!mTowerManager.isTowerAt(CCoordinate(above,c))) {
			visited[above][c] = 1;
			queue.push(CCoordinate(above, c));
		}
		const int right = c + 1;
		if (right < mSizeCols &&
			!visited[r][right] &&
			!mTowerManager.isTowerAt(CCoordinate(r,right))) {
			visited[r][right] = 1;
			queue.push(CCoordinate(r, right));
		}
		const int left = c - 1;
		if (left >= 0 &&
			!visited[r][left] &&
			!mTowerManager.isTowerAt(CCoordinate(r,left))) {
			visited[r][left] = 1;
			queue.push(CCoordinate(r, left));
		}
	}

	return true;
}

void CGameBoard::loadMap() {
	// TODO load from map object instead
	//std::ifstream loadfile;
	//loadfile.open(std::string("info/") + map_id + std::string("/gameboard.info"));
	//if (loadfile.is_open()) {

	//	int max_cp;
	//	loadfile >> max_cp;
	//	mPlayer.set_max_cp(max_cp);
	//	mPlayer.set_cp(max_cp);

	//	int ram;
	//	loadfile >> ram;
	//	mPlayer.set_ram(ram);

	//	int number_of_towers;

	//	loadfile >> number_of_towers;
	//	char tmp;
	//	for (int i = 0; i < number_of_towers; ++i) {
	//		loadfile >> tmp;
	//		available_towers.insert(tmp);
	//	}

	//	loadfile >> mSizeRows;
	//	loadfile >> mSizeCols;

	//	environment = std::vector<std::vector<int> >(mSizeRows, std::vector<int>(mSizeCols));

	//	int tile;
	//	for (int r = 0; r < mSizeRows; r++) {
	//		for (int c = 0; c < mSizeCols; c++) {
	//			loadfile >> tile;
	//			environment[r][c] = tile;
	//		}
	//	}
	//towers = std::vector<std::vector<bool> >(mSizeRows, std::vector<bool>(mSizeCols, false));
	//}
}

}
