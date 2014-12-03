#include "tower.hpp"

Tower::Tower() {
	num_rows = 1;
	num_cols = 1;
	blocking [num_rows][num_cols];
	gfx      [num_rows][num_cols];
}

Tower::Tower(const Tower & src) {
	num_rows = src.num_rows;
	num_cols = src.num_cols;
	pos = src.pos;
	blocking = src.blocking;
	gfx = src.gfx;
}

Tower::~Tower() {
	//Currently nothing needs to be done
}

Tower& Tower::operator=(const Tower & src) {
	pos = src.pos;
	blocking = src.blocking;
	gfx = src.gfx;
	return *this;
}

bool Tower::draw(GUI & g) {
	return g.draw_gfx(pos, gfx, num_rows, num_cols);
}

const int Tower::get_sell_value() const {
	return sell_value;
}

const bool Tower::get_blocking() const {
	return blocking;
}

int Tower::get_size_rows() const {
	return num_rows;
}

int Tower::get_size_cols() const {
	return num_cols;
}


