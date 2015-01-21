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

	Path::Path(Coord start, int num_rows, int num_cols, const std::vector<std::vector<bool> > & towers) {
GUI::print_intel(std::string("new path"));
getch();
		Coord current(start);
		bool visited [num_rows][num_cols];
		Coord backtrack [num_rows][num_cols];

		for (int r = 0; r < num_rows; ++r) {
			for(int c = 0; c < num_cols; ++c) {
				visited[r][c] = false;
			}
		}
		std::queue<Coord> queue;

		visited[current.get_row()][current.get_col()] = true;
		queue.push(current);


		while (current.get_col() > 0 && !queue.empty()) {
			current = queue.front();
			queue.pop();
			int r = current.get_row();
			int c = current.get_col();

			auto available = [&num_rows, &num_cols, &towers](int r, int c){
				return r >= 0 &&
					c > 0 &&
					r < num_rows &&
					c < num_cols &&
					!towers[r][c];
			};

			//Up left
			if (available(r-1, c-1) && !visited[r-1][c-1]) {
				queue.push(Coord(r-1, c-1));
				visited[r-1][c-1] = true;
				backtrack[r-1][c-1] = current;
			}
			//Down left
			if (available(r+1, c-1) && !visited[r+1][c-1]) {
				queue.push(Coord(r+1, c-1));
				visited[r+1][c-1] = true;
				backtrack[r+1][c-1] = current;
			}
			//Up right
			if (available(r-1, c+1) && !visited[r-1][c+1]) {
				queue.push(Coord(r-1, c+1));
				visited[r-1][c+1] = true;
				backtrack[r-1][c+1] = current;
			}
			//Down right
			if (available(r+1, c+1) && !visited[r+1][c+1]) {
				queue.push(Coord(r+1, c+1));
				visited[r+1][c+1] = true;
				backtrack[r+1][c+1] = current;
			}
			//Left
			if (available(r, c-1) && !visited[r][c-1]) {
				queue.push(Coord(r, c-1));
				visited[r][c-1] = true;
				backtrack[r][c-1] = current;
			}
			//Right
			if (available(r, c+1) && !visited[r][c+1]) {
				queue.push(Coord(r, c+1));
				visited[r][c+1] = true;
				backtrack[r][c+1] = current;
			}
			//Up
			if (available(r-1, c) && !visited[r-1][c]) {
				queue.push(Coord(r-1, c));
				visited[r-1][c] = true;
				backtrack[r-1][c] = current;
			}
			//Down
			if (available(r+1, c) && !visited[r+1][c]) {
				queue.push(Coord(r+1, c));
				visited[r+1][c] = true;
				backtrack[r+1][c] = current;
			}
		}

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
