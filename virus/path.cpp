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
		std::vector<std::vector<std::pair<int, Coord> > > backtrack( num_rows, std::vector<std::pair<int, Coord> >( num_cols, std::pair<int, Coord>(INT_MAX, Coord(-1,-1))));

		std::queue<Coord> queue;

		queue.push(current);


		while (current.get_col() > 0 && !queue.empty()) {
			current = queue.front();
			queue.pop();
			int r = current.get_row();
			int c = current.get_col();

			auto step = [&](int row, int col, int cost){
				if ( row >= 0 &&
					col > 0 &&
					row < num_rows &&
					col < num_cols &&
					backtrack[row][col].first > cost && //shorter path
					!towers[row][col] ) {
					queue.push(Coord(row, col));
					backtrack[row][col] = std::pair<int, Coord>(cost, current);
				}
			};

			//Up left
			step(r-1, c-1, VIRUS_STEPCOSTDIAGONAL + backtrack[r][c].first);
			//Down left
			step(r+1, c-1, VIRUS_STEPCOSTDIAGONAL + backtrack[r][c].first);
			//Left
			step(r, c-1, VIRUS_STEPCOST + backtrack[r][c].first);
			//Up right
			step(r-1,c+1, VIRUS_STEPCOSTDIAGONAL + backtrack[r][c].first);
			//Down right
			step(r+1,c+1, VIRUS_STEPCOSTDIAGONAL + backtrack[r][c].first);
			//Right
			step(r, c+1, VIRUS_STEPCOST + backtrack[r][c].first);
			//Up
			step(r-1,c, VIRUS_STEPCOST + backtrack[r][c].first);
			//Down
			step(r+1,c, VIRUS_STEPCOST + backtrack[r][c].first);
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
