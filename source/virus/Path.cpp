#include <virus/Path.h>

#include <algorithm>
#include <limits>
#include <stack>

namespace termd {

// Algorithm used is not optimal for performance. Though it
// should not matter since this is a pretty light-weight
// game and it is only performed a limited number of times
// on a very restricted amount of nodes.
CPath::CPath(
    const CCoordinate& startPosition,
    const std::set<CCoordinate>& endPositions,
    int numRows,
    int numCols,
    const std::map<CCoordinate, std::unique_ptr<ITower>>& towers)
    : mLogger(__FILE__) {
    const int stepCost = 1000;
    const int stepCostDiagonal = 1414;
    const int startRow = startPosition.getRow();
    const int startCol = startPosition.getCol();
    if (towers.contains(startPosition)) {
        mLogger.log("Blocked start position: (%d, %d)", startRow, startCol);
        return;
    }
    if (startRow >= numRows || startCol >= numCols || startRow < 0 || startCol < 0) {
        mLogger.logError("Invalid start position");
        return;
    }

    std::vector<std::vector<std::pair<int, CCoordinate>>> backtrack(
        numRows,
        std::vector<std::pair<int, CCoordinate>>(
            numCols,
            std::pair<int, CCoordinate>(std::numeric_limits<int>::max(), CCoordinate(-1, -1))));

    std::queue<CCoordinate> queue;
    for (const CCoordinate& endPosition : endPositions) {
        const int endRow = endPosition.getRow();
        const int endCol = endPosition.getCol();
        if (towers.contains(endPosition)) {
            mLogger.log("Blocked end position: (%d, %d)", endRow, endCol);
            continue;
        }
        if (endRow >= numRows || endCol >= numCols || endRow < 0 || endCol < 0) {
            mLogger.logError("Invalid end position: (%d, %d)", endRow, endCol);
            return;
        }
        queue.push(endPosition);
        backtrack[endRow][endCol] = std::pair<int, CCoordinate>(0, endPosition);
    }

    while (!queue.empty()) {
        const CCoordinate& current = queue.front();
        const int r = current.getRow();
        const int c = current.getCol();

        auto checkBound = [&numRows, &numCols](int row, int col) {
            return row >= 0 && col >= 0 && row < numRows && col < numCols;
        };
        auto step = [&](int row, int col, int cost) {
            mLogger.log("Stepping, (%d, %d) %d", row, col, cost);
            const int oldEstimate = backtrack[row][col].first;

            // if paths are equal, randomize wich one to use
            const bool isShorter = (cost < oldEstimate || (cost == oldEstimate && std::rand() % 2 == 0));

            if (isShorter && !towers.contains(CCoordinate(row, col))) {
                mLogger.log("Found better path");
                queue.push(CCoordinate(row, col));
                backtrack[row][col] = std::pair<int, CCoordinate>(cost, current);
            }
        };

        const int currentCost = backtrack[r][c].first;
        // Left
        if (checkBound(r, c - 1)) {
            step(r, c - 1, stepCost + currentCost);
        }
        // Right
        if (checkBound(r, c + 1)) {
            step(r, c + 1, stepCost + currentCost);
        }
        // Up
        if (checkBound(r - 1, c)) {
            step(r - 1, c, stepCost + currentCost);
        }
        // Down
        if (checkBound(r + 1, c)) {
            step(r + 1, c, stepCost + currentCost);
        }
        // Up left
        if (checkBound(r - 1, c - 1)
            && (!towers.contains(CCoordinate(r - 1, c)) || !towers.contains(CCoordinate(r, c - 1)))) {
            step(r - 1, c - 1, stepCostDiagonal + currentCost);
        }
        // Down left
        if (checkBound(r + 1, c - 1)
            && (!towers.contains(CCoordinate(r + 1, c)) || !towers.contains(CCoordinate(r, c - 1)))) {
            step(r + 1, c - 1, stepCostDiagonal + currentCost);
        }
        // Up right
        if (checkBound(r - 1, c + 1)
            && (!towers.contains(CCoordinate(r - 1, c)) || !towers.contains(CCoordinate(r, c + 1)))) {
            step(r - 1, c + 1, stepCostDiagonal + currentCost);
        }
        // Down right
        if (checkBound(r + 1, c + 1)
            && (!towers.contains(CCoordinate(r + 1, c)) || !towers.contains(CCoordinate(r, c + 1)))) {
            step(r + 1, c + 1, stepCostDiagonal + currentCost);
        }
        queue.pop();
    }

    CCoordinate current = startPosition;
    CCoordinate previous = current;
    while (!endPositions.contains(current)) {
        if (current.getCol() != previous.getCol() && current.getRow() != previous.getRow()) {
            // We made a diagonal step
            mPath.push(SStep(current, stepCostDiagonal));
        } else {
            mPath.push(SStep(current, stepCost));
        }
        previous = current;
        current = backtrack[current.getRow()][current.getCol()].second;
    }
    mPath.push(SStep(current, stepCost));
}

const CCoordinate& CPath::getCurrentPosition() const {
    return mPath.front().coord; // TODO clean up, will break if path is empty
}

bool CPath::isDestinationReached() const {
    return mPath.empty();
}

int CPath::step(int stamina) {
    while (!mPath.empty() && stamina >= mPath.front().cost) {
        mLogger.log("Stepping loop, stamina: %d", stamina);
        stamina -= mPath.front().cost;
        mPath.pop();
    }
    mLogger.log("Done stepping, stamina: %d", stamina);
    return stamina;
}

}
