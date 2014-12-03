#include "coord.hpp"

Coord::Coord() {
	col = 0;
	row = 0;
}

Coord::Coord(int x, int y) {
	col = x;
	row = y;
}

Coord::Coord(const Coord & src) {
	col = src.col;
	row = src.row;
}

Coord::Coord(const Coord * src) {
	col = src->col;
	row = src->row;
}

Coord& Coord::operator=(const Coord & src) {
	col = src.col;
	row = src.row;
	return *this;
}

bool Coord::operator==(const Coord & other) const {
	return other.row == row && other.col == col;
}

bool Coord::operator!=(const Coord & other) const {
	return other.row != row || other.col != col;
}

bool Coord::operator<(const Coord & other) const {
	if (row == other.row) {
		return col < other.col;
	}
	return row < other.row;
}

bool Coord::operator>(const Coord & other) const {
	if (row == other.row) {
		return col > other.col;
	}
	return row > other.row;
}


int Coord::get_col() const {
	return col;
}

int Coord::get_row() const {
	return row;
}

bool Coord::set_col(const int x) {
	if(x < 0) { //TODO upper bound
		return false;
	}
	col = x;
	return true;
}

bool Coord::set_row(const int y) {
	if(y < 0) { //TODO upper bound
		return false;
	}
	row = y;
	return true;
}

std::ostream & operator<<(std::ostream & os, const Coord & coord) {
	os << "row: " << coord.get_row() << ", col: " << coord.get_col();
	return os;
}
