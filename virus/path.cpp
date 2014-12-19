#include "path.hpp"

Path::Path(Coord s) {
	int col = s.get_col();
	for (int i = col; i > 0; --i)
	{
		s.set_col(i);
		path.push(Step(s, STEPCOST)); //Copy that 's' Coord!
	}
}

Path::Path(const Path & src) {
	path = src.path;
	//TODO keep updated
}

Path::~Path() {
	//Nothing needed here at the moment
}

Path & Path::operator=(const Path & src) {
	path = src.path;
	//TODO keep updated
	return *this;
}

Coord Path::get_curr_pos() {
	return path.front(); //Must not be called when path is empty!
}

bool Path::destination_reached() {
	return path.empty();
}

void Path::step(int& sta) {
	while(path.empty() == false && sta >= path.front().cost){
		sta -= path.front().cost;
		path.pop(); //removes the head of the queue, will be drawn on the "next" place
	}
}