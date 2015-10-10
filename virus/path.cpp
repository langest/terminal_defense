#include "path.hpp"

namespace termd {

	Path::Path(Coord s) {
		int col = s.get_col();
		for (int i = col; i > 0; --i)
		{
			s.set_col(i);
			path.push(Step(s,VirusStepCost )); //Copy that 's' Coord!
		}
	}

	//Algorithm used is not optimal for performance. Though it
	//should not matter since this is a pretty light-weight
	//game and it is only performed a limited number of times
	//on a very restricted amount of nodes.
	Path::Path(Coord start, int num_rows, int num_cols, const std::vector<std::vector<bool> > & towers) {
		if (start.get_row() >= num_rows || start.get_col() >= num_cols ||
				start.get_row() < 0 || start.get_col() < 0) return; //invalid start, make no path
		Coord current(start);
		std::vector<std::vector<std::pair<int, Coord> > > backtrack( num_rows, std::vector<std::pair<int, Coord> >( num_cols, std::pair<int, Coord>(IntMax, Coord(-1,-1))));

		std::queue<Coord> queue;

		queue.push(current);

		while (!queue.empty()) {
			current = queue.front();
			queue.pop();
			int r = current.get_row();
			int c = current.get_col();

			auto check_bound = [&num_rows, &num_cols](int row, int col) {
				return row >= 0 &&
					col >= 0 &&
					row < num_rows &&
					col < num_cols;
			};
			auto step = [&](int row, int col, int cost) {
				if (backtrack[row][col].first > cost && //shorter path
					!towers[row][col] ) {
					queue.push(Coord(row, col));
					backtrack[row][col] = std::pair<int, Coord>(cost, current);
				}
			};

			//Left
			if (check_bound(r, c-1))
				step(r, c-1, VirusStepCost + backtrack[r][c].first);
			//Right
			if (check_bound(r, c+1))
				step(r, c+1, VirusStepCost + backtrack[r][c].first);
			//Up
			if (check_bound(r-1, c))
				step(r-1,c, VirusStepCost + backtrack[r][c].first);
			//Down
			if (check_bound(r+1, c))
				step(r+1,c, VirusStepCost + backtrack[r][c].first);
			//Up left
			if (check_bound(r-1, c-1) &&( !towers[r-1][c] || !towers[r][c-1]))
				step(r-1, c-1, VirusStepCostDiagonal + backtrack[r][c].first);
			//Down left
			if (check_bound(r+1, c-1) &&( !towers[r+1][c] || !towers[r][c-1]))
				step(r+1, c-1, VirusStepCostDiagonal + backtrack[r][c].first);
			//Up right
			if (check_bound(r-1, c+1) &&( !towers[r-1][c] || !towers[r][c+1]))
				step(r-1,c+1, VirusStepCostDiagonal + backtrack[r][c].first);
			//Down right
			if (check_bound(r+1, c+1) &&( !towers[r+1][c] || !towers[r][c+1]))
				step(r+1,c+1, VirusStepCostDiagonal + backtrack[r][c].first);
		}

		int min_cost = backtrack[0][0].first;
		current = backtrack[0][0].second;
		for (int i = 1; i < num_rows; ++i) {
			if (backtrack[i][0].first < min_cost) {
				min_cost = backtrack[i][0].first;
				current = backtrack[i][0].second;
			}
		}

		std::stack<Coord> reverse;
		while (current != start) {
			reverse.push(current);
			current = backtrack[current.get_row()][current.get_col()].second;
		}
		reverse.push(start);

		int cost;
		Coord last(current);
		while (!reverse.empty()) {
			current = reverse.top();
			reverse.pop();
			if (current.get_col() != last.get_col() &&
					current.get_row() != current.get_row()) { //We made a diagonal step
				cost =VirusStepCostDiagonal ;
			} else {
				cost =VirusStepCost ;
			}
			path.push(Step(current, cost)); //Copy that 's' Coord!
			last = current;
		}
	}

	Path::Path(const Path & src) : path(src.path) {}
	Path::Path(Path && src) : path(std::move(src.path)) {}

	Path::~Path() {
		//Nothing needed here at the moment
	}

	Path& Path::operator=(const Path & src) {
		path = src.path;
		return (*this);
	}

	Path& Path::operator=(Path && src) {
		path = std::move(src.path);
		return (*this);
	}

	Coord Path::get_curr_pos() const {
		return path.front().coord; //Must not be called when path is empty!
	}

	bool Path::destination_reached() const {
		return path.empty();
	}

	void Path::step(int& sta) {
		while(path.empty() == false && sta >= path.front().cost){
			sta -= path.front().cost;
			path.pop(); //removes the head of the queue, will be drawn on the "next" place
		}
	}

}
