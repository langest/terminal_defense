#include "path.hpp"

Path::Path(Coord s) : start(s), curr_pos(s) {
}

Path::Path(const Path & src) {
	start = src.start;
	curr_pos = src.curr_pos;
	//TODO keep updated
}

Path::~Path() {
	//Nothing needed here at the moment
}

Path & Path::operator=(const Path & src) {
	start = src.start;
	curr_pos = src.curr_pos;
	//TODO keep updated
	return *this;
}

Coord Path::get_curr_pos() {
	return curr_pos;
}

void Path::step(int sta) {
	//TODO
}