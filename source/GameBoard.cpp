#include <GameBoard.h>

#include <queue>

#include <Gui.h>
#include <tower/Wall.h>

namespace termd {

CGameBoard::CGameBoard(CPlayer& player) :
	player(player),
	mSizeRows(0),
	mSizeCols(0),
	//wman(mSizeRows, mSizeCols, towers, std::string(""), mVirusManager),
	mTowerManager(GUI::draw),
	mVirusManager(player) {
		loadMap();
		//wman.set_size(mSizeRows, mSizeCols);
		//pman.set_size(mSizeRows, mSizeCols);
}

void CGameBoard::draw() const {
	GUI::clear_game(mSizeRows, mSizeCols);

	mTowerManager.drawAllTowers();
	mVirusManager.drawAllViruses();
	GUI::draw_board_frame(mSizeRows, mSizeCols);
}

bool CGameBoard::update() {
	//bool cont = wman.update();
	bool hasMoreToDo = mVirusManager.updateAllViruses();
	//pman.update();
	mTowerManager.updateAllTowers();
	if (!hasMoreToDo) {
		mVirusManager.updateAllVirusesEndOfWave();
		//pman.end_of_wave();
		mTowerManager.updateAllTowersEndOfWave();
	}
	return hasMoreToDo;
}

bool CGameBoard::buildTower(const CCoordinate& coordinate) {
	const int row(coordinate.getRow());
	const int col(coordinate.getCol());
	if (col < 0 ||
		col >= mSizeCols ||
		row < 0 ||
		row >= mSizeRows ||
		mTowerManager.isTowerAt(coordinate)) {
		return false;
	}

	if (this->isBlockedWith(coordinate)) {
		return false;
	}

	return mTowerManager.placeTower(coordinate, std::make_unique<CWall>());
}

bool CGameBoard::hasNextWave() const {
	return mVirusManager.hasNextWave();
}

const int CGameBoard::getSizeRows() const {
	return mSizeRows;
}

const int CGameBoard::getSizeCols() const {
	return mSizeCols;
}

bool CGameBoard::isBlockedWith(const CCoordinate& coordinate) {
	std::vector<std::vector<int>> visited(mSizeRows, std::vector(mSizeCols, 0));

	visited[coordinate.getRow()][coordinate.getCol()] = 1;
	std::queue<CCoordinate> queue;

	queue.push(CCoordinate(0, mSizeCols-1));
	visited[0][mSizeCols-1] = 1;

	while (!queue.empty()) {
		const CCoordinate current = queue.front();
		queue.pop();
		const int r = current.getRow();
		const int c = current.getCol();

		if (c <= 0) {
			return false;
		}

		if (r+1 < mSizeRows &&
			!visited[r + 1][c] &&
			!mTowerManager.isTowerAt(CCoordinate(r+1,c))) {
			visited[r + 1][c] = 1;
			queue.push(CCoordinate(r + 1, c));
		}
		if (r > 0 &&
			!visited[r - 1][c] &&
			!mTowerManager.isTowerAt(CCoordinate(r-1,c))) {
			visited[r - 1][c] = 1;
			queue.push(CCoordinate(r - 1, c));
		}
		if (c+1 < mSizeCols &&
			!visited[r][c + 1] &&
			!mTowerManager.isTowerAt(CCoordinate(r,c+1))) {
			visited[r][c + 1] = 1;
			queue.push(CCoordinate(r, c + 1));
		}
		if (c > 0 &&
			!visited[r][c - 1] &&
			!mTowerManager.isTowerAt(CCoordinate(r,c-1))) {
			visited[r][c - 1] = 1;
			queue.push(CCoordinate(r, c - 1));
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
	//	player.set_max_cp(max_cp);
	//	player.set_cp(max_cp);

	//	int ram;
	//	loadfile >> ram;
	//	player.set_ram(ram);

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
