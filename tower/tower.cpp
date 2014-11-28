#include "tower.hpp"

Tower::Tower(const Tower & src) {
	pos = src.pos;
	blocking = src.blocking;
	gfx = src.gfx;
	size_rows = src.size_rows;
	size_cols = src.size_cols;
}

Tower::~Tower() {
	//Currently nothing needs to be done
}

Tower& Tower::operator=(const Tower & src) {
	pos = src.pos;
	blocking = src.blocking;
	gfx = src.gfx;
	size_rows = src.size_rows;
	size_cols = src.size_cols;
	return *this;
}

void Tower::draw(GUI & g) {
	g.draw_gfx(pos, gfx, size_rows, size_cols);
}

inline const bool Tower::get_blocking() const {
	return blocking;
}

inline const int Tower::get_size_rows() const {
	return size_rows;
}

inline const int Tower::get_size_cols() const {
	return size_cols;
}
