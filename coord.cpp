#include "coord.hpp"

Coord::Coord() {
	col = 0;
	row = 0;
}

Coord::Coord(int x, int y){
	col = x;
	row = y;
}
Coord::Coord(Coord const & other){
	col = other.col;
	row = other.row;
}
Coord::Coord(Coord const *){
	col = other->col;
	row = other->row;
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