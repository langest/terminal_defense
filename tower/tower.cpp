#include "tower.hpp"

Tower::~Tower() {
	//Currently nothing needs to be done
}

bool Tower::draw(GUI & g) {
	return g.draw_gfx(pos, gfx, num_rows, num_cols);
}

const int Tower::get_sell_value() const {
	return sell_value;
}

const bool Tower::get_blocking() const {
	return false;
}

int Tower::get_size_rows() const {
	return num_rows;
}

int Tower::get_size_cols() const {
	return num_cols;
}


