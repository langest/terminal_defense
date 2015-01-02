#include "coord.hpp"

Coord::Coord() : row(0), col(0) {
}

Coord::Coord(int r, int c) : row(r), col(c) {
}

Coord::Coord(const Coord & src) { //TODO use initialization list
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

void Coord::add_col(int amount) const {
	col += amount;
}

bool Coord::set_col(const int x) {
	if(x < 0) { //TODO upper bound
		return false;
	}
	col = x;
	return true;
}

int Coord::get_row() const {
	return row;
}

void Coord::add_row(int amount) const {
	row += amount;
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

Coord Coord::operator-(const Coord & other) const {
	return Coord(this->row - other.row, this->col - other.col);
}

Coord Coord::operator+(const Coord & other) const {
	return Coord(this->row + other.row, this->col + other.col);
}

void Coord::operator-=(const Coord & other) {
	row = row - other.row;
	col = col - other.col;
}

void Coord::operator+=(const Coord & other) {
	row = row + other.row;
	col = col + other.col;
}

double Coord::length() const {
	return sqrt(row*row + col*col);
}
