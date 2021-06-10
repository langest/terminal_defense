#include <virus/Path.h>

#include <limits>
#include <stack>

namespace termd {

//Algorithm used is not optimal for performance. Though it
//should not matter since this is a pretty light-weight
//game and it is only performed a limited number of times
//on a very restricted amount of nodes.
CPath::CPath(
	const CCoordinate& startPosition,
	int numRows,
	int numCols,
	const std::map<CCoordinate, std::unique_ptr<ITower>>& towers
) {
	const int stepCost = 1000;
	const int stepCostDiagonal = 1414;
	const int startRow = startPosition.getRow();
	const int startCol = startPosition.getCol();
	if (
		startRow >= numRows ||
		startCol >= numCols ||
		startRow < 0 ||
		startCol < 0
	) {
		//invalid start, make no path
		return;
	}

	CCoordinate current(startPosition);

	std::vector<std::vector<std::pair<int, CCoordinate>>> backtrack(
		numRows,
		std::vector<std::pair<int, CCoordinate>>(
			numCols,
			std::pair<int, CCoordinate>(
				std::numeric_limits<int>::max(),
				CCoordinate(-1,-1)
			)
		)
	);

	std::queue<CCoordinate> queue;

	queue.push(current);

	while (!queue.empty()) {
		current = queue.front();
		queue.pop();
		int r = current.getRow();
		int c = current.getCol();

		auto check_bound = [&numRows, &numCols](int row, int col) {
			return row >= 0 &&
				col >= 0 &&
				row < numRows &&
				col < numCols;
		};
		auto step = [&](int row, int col, int cost) {
			if (backtrack[row][col].first > cost && //shorter path
				!towers.contains(CCoordinate(row, col))) {
				queue.push(CCoordinate(row, col));
				backtrack[row][col] = std::pair<int, CCoordinate>(cost, current);
			}
		};

		//Left
		if (check_bound(r, c-1)) {
			step(r, c-1, stepCost + backtrack[r][c].first);
		}
		//Right
		if (check_bound(r, c+1)) {
			step(r, c+1, stepCost + backtrack[r][c].first);
		}
		//Up
		if (check_bound(r-1, c)) {
			step(r-1,c, stepCost + backtrack[r][c].first);
		}
		//Down
		if (check_bound(r+1, c)) {
			step(r+1,c, stepCost + backtrack[r][c].first);
		}
		//Up left
		if (check_bound(r-1, c-1) && (!towers.contains(CCoordinate(r-1, c)) || !towers.contains(CCoordinate(r, c-1)))) {
			step(r-1, c-1, stepCostDiagonal + backtrack[r][c].first);
		}
		//Down left
		if (check_bound(r+1, c-1) && (!towers.contains(CCoordinate(r+1, c)) || !towers.contains(CCoordinate(r, c-1)))) {
			step(r+1, c-1, stepCostDiagonal + backtrack[r][c].first);
		}
		//Up right
		if (check_bound(r-1, c+1) && (!towers.contains(CCoordinate(r-1, c)) || !towers.contains(CCoordinate(r, c+1)))) {
			step(r-1,c+1, stepCostDiagonal + backtrack[r][c].first);
		}
		//Down right
		if (check_bound(r+1, c+1) && (!towers.contains(CCoordinate(r+1, c)) || !towers.contains(CCoordinate(r, c+1)))) {
			step(r+1,c+1, stepCostDiagonal + backtrack[r][c].first);
		}
	}

	int min_cost = backtrack[0][0].first;
	current = backtrack[0][0].second;
	for (int i = 1; i < numRows; ++i) {
		if (backtrack[i][0].first < min_cost) {
			min_cost = backtrack[i][0].first;
			current = backtrack[i][0].second;
		}
	}

	std::stack<CCoordinate> reverse;
	while (current != startPosition) {
		reverse.push(current);
		current = backtrack[current.getRow()][current.getCol()].second;
	}
	reverse.push(startPosition);

	int cost;
	CCoordinate last(current);
	while (!reverse.empty()) {
		current = reverse.top();
		reverse.pop();
		if (current.getCol() != last.getCol() &&
				current.getRow() != current.getRow()) { //We made a diagonal step
			cost = stepCostDiagonal;
		} else {
			cost = stepCost;
		}
		path.push(SStep(current, cost)); //Copy that 's' CCoordinate!
		last = current;
	}
}

const CCoordinate& CPath::getCurrentPosition() const {
	return path.front().coord; // TODO clean up, will break if path is empty
}

bool CPath::isDestinationReached() const {
	return path.empty();
}

int CPath::step(int stamina) {
	while(!path.empty() && stamina >= path.front().cost){
		stamina -= path.front().cost;
		path.pop(); //removes the head of the queue, will be drawn on the "next" place
	}
	return stamina;
}

}
