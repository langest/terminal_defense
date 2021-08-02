#include <GameBoard.h>

#include <functional>
#include <queue>

#include <Gui.h>
#include <tower/RightTower.h>
#include <tower/Wall.h>

namespace termd {

CGameBoard::CGameBoard(CPlayer& player, int sizeRows, int sizeCols)
    : mPlayer(player)
    , mStartRow(1)
    , mStartCol(1)
    , mSizeRows(sizeRows)
    , mSizeCols(sizeCols)
    , mTowerManager([this](const CCoordinate& position) {
        return this->isInsideGameBoard(position);
    })
    , mVirusManager(mPlayer, sizeRows, sizeCols)
    , mHasMoreToDo(false)
    , mLogger(__FILE__)
{
    loadMap();
    for (int i = 0; i < mSizeRows; ++i) {
        mStartPositions.emplace(CCoordinate(i, mSizeCols - 1));
        mEndPositions.emplace(CCoordinate(i, 0));
    }
}

void CGameBoard::resetCursor()
{
    GUI::moveCursor(CCoordinate(
        (mStartRow + mSizeRows) / 2,
        (mStartCol + mSizeCols) / 2));
}

void CGameBoard::moveCursorLeft()
{
    GUI::moveCursorLeft(mStartCol);
}

void CGameBoard::moveCursorDown()
{
    GUI::moveCursorDown(mStartRow + mSizeRows - 1);
}

void CGameBoard::moveCursorUp()
{
    GUI::moveCursorUp(mStartRow);
}

void CGameBoard::moveCursorRight()
{
    GUI::moveCursorRight(mStartCol + mSizeCols - 1);
}

void CGameBoard::draw()
{
    GUI::clearScreen();

    mTowerManager.draw(std::bind(&CGameBoard::drawCall, this, std::placeholders::_1, std::placeholders::_2));
    mVirusManager.draw(std::bind(&CGameBoard::drawCall, this, std::placeholders::_1, std::placeholders::_2));
    GUI::drawFrame(
        CCoordinate(0, 0),
        CCoordinate(mSizeRows + 1, mSizeCols + 1));
}

void CGameBoard::initInvasion()
{
    if (mHasMoreToDo) {
        mLogger.logError("Tried to init invasion while already having one started");
        return; // Do not start multiple invasions
    }
    mVirusManager.initInvasion();
    mTowerManager.initInvasion();
}

bool CGameBoard::update()
{
    mLogger.log("Update");

    mHasMoreToDo = mVirusManager.update(mStartPositions, mEndPositions, mTowerManager.getTowers());

    std::map<CCoordinate, std::vector<std::reference_wrapper<std::unique_ptr<CVirus>>>> virusMap = mVirusManager.getCoordinateVirusMap();
    mTowerManager.update(
        mVirusManager.getActiveViruses(),
        virusMap);

    if (!mHasMoreToDo) {
        mLogger.log("Nothing more to do, finishing invasion");
        mVirusManager.finishInvasion();
        mTowerManager.finishInvasion();
    }
    return mHasMoreToDo;
}

void CGameBoard::buildTower(char tower)
{
    const CCoordinate cursorPosition = GUI::getCursorPosition();
    const int row = cursorPosition.getRow() - mStartRow;
    const int col = cursorPosition.getCol() - mStartCol;
    const CCoordinate buildPosition(row, col);
    mLogger.log("Trying to build tower at (%d, %d)", row, col);
    if (!this->isInsideGameBoard(buildPosition) || mTowerManager.isTowerAt(buildPosition)) {
        mLogger.log("Can NOT build tower at (%d, %d)", row, col);
        return;
    }

    if (this->isBlockedWith(buildPosition)) {
        mLogger.log("Can NOT build tower at (%d, %d), it would block the path", row, col);
        return;
    }

    // TODO make prettier tower selection
    switch (tower) {
    case 'w': {
        mTowerManager.placeTower(buildPosition, std::make_unique<CWall>());
        break;
    }
    case 'r': {
        mTowerManager.placeTower(buildPosition, std::make_unique<CRightTower>(buildPosition));
        break;
    }
    }
}

bool CGameBoard::hasNextWave() const
{
    return mVirusManager.hasNextWave();
}

int CGameBoard::getSizeRows() const
{
    return mSizeRows;
}

int CGameBoard::getSizeCols() const
{
    return mSizeCols;
}

void CGameBoard::drawCall(const CCoordinate& position, char graphic)
{
    GUI::draw(position + CCoordinate(mStartRow, mStartCol), graphic);
}

bool CGameBoard::isInsideGameBoard(const CCoordinate& coordinate) const
{
    const int row = coordinate.getRow();
    const int col = coordinate.getCol();
    return (0 <= col && col < mSizeCols && 0 <= row && row < mSizeRows);
}

bool CGameBoard::isBlockedWith(const CCoordinate& coordinate) const
{
    if (mStartPositions.contains(coordinate)) {
        return true;
    }
    std::vector<std::vector<int>> visited(mSizeRows, std::vector<int>(mSizeCols, 0));

    visited[coordinate.getRow()][coordinate.getCol()] = 1;
    std::queue<CCoordinate> queue;

    for (const CCoordinate& startPosition : mStartPositions) {
        if (mTowerManager.isTowerAt(startPosition) || visited[startPosition.getRow()][startPosition.getCol()]) {
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
        if (under < mSizeRows && !visited[under][c] && !mTowerManager.isTowerAt(CCoordinate(under, c))) {
            visited[under][c] = 1;
            queue.push(CCoordinate(under, c));
        }
        const int above = r - 1;
        if (above >= 0 && !visited[above][c] && !mTowerManager.isTowerAt(CCoordinate(above, c))) {
            visited[above][c] = 1;
            queue.push(CCoordinate(above, c));
        }
        const int right = c + 1;
        if (right < mSizeCols && !visited[r][right] && !mTowerManager.isTowerAt(CCoordinate(r, right))) {
            visited[r][right] = 1;
            queue.push(CCoordinate(r, right));
        }
        const int left = c - 1;
        if (left >= 0 && !visited[r][left] && !mTowerManager.isTowerAt(CCoordinate(r, left))) {
            visited[r][left] = 1;
            queue.push(CCoordinate(r, left));
        }
    }

    return true;
}

void CGameBoard::loadMap()
{
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
