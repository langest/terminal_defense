#include "path.hpp"

namespace termd {

	Path::Path(Coord s) {
		int col = s.get_col();
		for (int i = col; i > 0; --i)
		{
			s.set_col(i);
			path.push(Step(s, VIRUS_STEPCOST)); //Copy that 's' Coord!
		}
	}

	//Implementing jump-point search enhanced BFS
	Path::Path(Coord start, int num_rows, int num_cols, const std::vector<std::vector<bool> > & towers) {

		auto is_valid_bounds = [&num_rows, &num_cols](int row, int col) {
			return row >= 0 &&
				col >= 0 &&
				row < num_rows &&
				col < num_cols;
		};

		//Check so we have a valid start
		if (!is_valid_bounds(start.get_row(), start.get_col())) {
			return;
		}

		enum DIR {up, down, left, right, up_right, up_left, down_right, down_left};
		struct Node {
			Coord coord;
			DIR dir;
			Node(Coord cc, DIR dd) : coord(cc), dir(dd){}
			Node(int r, int c , DIR dd) : coord(r, c), dir(dd){}
		};

		std::queue<Node> queue;
		std::vector<std::vector<Coord> > backtrack( num_rows, std::vector<Coord>( num_cols, Coord(-1,-1) ) );

		auto step = [&](Coord came_from, int row, int col, DIR dir) {
			if (backtrack[row][col].get_row() != -1 &&
					!towers[row][col] ) {
				queue.push(Node(row, col, dir));
				backtrack[row][col] = came_from;
			}
		};
		auto step_straight = [&](Coord came_from, int row, int col, DIR dir) {
			if (backtrack[row][col].get_row() != -1 &&
					!towers[row][col] ) {
				queue.push(Node(row, col, dir));
				backtrack[row][col] = came_from;
				switch (dir) {
					case right:
						{
							if (row > 0 && towers[row-1][col-1]) {
								step(Coord(row, col), row-1, col, up);
								step(Coord(row, col), row-1, col+1, up_right);
							}
								step(Coord(row, col), row, col+1, right);
							if (row < num_rows && towers[row+1][col-1]) {
								step(Coord(row, col), row+1, col, down);
								step(Coord(row, col), row+1, col+1, down_right);
							}
						}
					case left:
						{
							if (row > 0 && towers[row-1][col+1]) {
								step(Coord(row, col), row-1, col, up);
								step(Coord(row, col), row-1, col-1, up_left);
							}
								step(Coord(row, col), row, col-1, left);
							if (row < num_rows && towers[row+1][col+1]) {
								step(Coord(row, col), row+1, col, down);
								step(Coord(row, col), row+1, col-1, down_left);
							}
							break;
						}
					case up:
						{
							break;
						}
					case down:
						{
							break;
						}
					case up_left:
						{
							break;
						}
					case down_left:
						{
							break;
						}
					case up_right:
						{
							break;
						}
					case down_right:
						{
							break;
						}
				}
			}
		};

		//Initialize by starting all directions in the queue
		Coord current(start);
		int r = current.get_row();
		int c = current.get_col();
		if (is_valid_bounds(r-1, c)) {
			step_straight(current, r-1, c, up);
		}
		if (is_valid_bounds(r+1, c)) {
			step_straight(current, r+1, c, down);
		}
		if (is_valid_bounds(r, c-1)) {
			step_straight(current, r, c-1, left);
		}
		if (is_valid_bounds(r, c+1)) {
			step_straight(current, r, c+1, right);
		}

		if (is_valid_bounds(r-1, c-1)) {
			step(current, r-1, c-1, up_left);
		}
		if (is_valid_bounds(r+1, c-1)) {
			step(current, r+1, c, down_left);
		}
		if (is_valid_bounds(r-1, c+1)) {
			step(current, r-1, c+1, up_right);
		}
		if (is_valid_bounds(r+1, c+1)) {
			step(current, r+1, c+1, down_right);
		}

		DIR d;
		while (current.get_col() > 0 && !queue.empty()) {
			current = queue.front().coord;
			d = queue.front().dir;
			r = current.get_row();
			c = current.get_col();
			queue.pop();

			switch (d) {
				case up:
					{
						if (is_valid_bounds(r-1, c)) {
							step(current, r-1, c, up);
						}
						break;
					}
				case down:
					{
						if (is_valid_bounds(r+1, c)) {
							step(current, r+1, c, down);
						}
						break;
					}
				case left:
					{
						if (is_valid_bounds(r, c-1)) {
							step(current, r, c-1, left);
						}
						break;
					}
				case right:
					{
						if (is_valid_bounds(r, c+1)) {
							step(current, r, c+1, right);
						}
						break;
					}
				case up_left:
					{
						break;
					}
				case up_right:
					{
						break;
					}
				case down_left:
					{
						break;
					}
				case down_right:
					{
						break;
					}
			}
		} //End while pathfinding

		std::stack<Coord> reverse;
		while (current != start) {
			reverse.push(current);
			current = backtrack[current.get_row()][current.get_col()];
		}
		reverse.push(start);
		int cost;
		Coord last(current);
		while (!reverse.empty()) {
			current = reverse.top();
			reverse.pop();
			if (current.get_col() != last.get_col() &&
					current.get_row() != current.get_row()) { //We made a diagonal step
				cost = VIRUS_STEPCOSTDIAGONAL;
			} else {
				cost = VIRUS_STEPCOST;
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
