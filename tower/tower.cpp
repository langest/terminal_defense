#include "tower.hpp"

template<size_t row_size, size_t col_size>
Tower<row_size, col_size>::Tower() {
	blocking [row_size][col_size];
	gfx      [row_size][col_size];
}

template<size_t row_size, size_t col_size> template<size_t a, size_t b>
Tower<row_size, col_size>::Tower(const Tower<a, b> & src) {
	pos = src.pos;
	blocking = src.blocking;
	gfx = src.gfx;
}

template<size_t row_size, size_t col_size>
Tower<row_size, col_size>::~Tower() {
	//Currently nothing needs to be done
}

template<size_t row_size, size_t col_size>
Tower<row_size, col_size>& Tower<row_size, col_size>::operator=(const Tower<row_size, col_size> & src) {
	pos = src.pos;
	blocking = src.blocking;
	gfx = src.gfx;
	return *this;
}

template<size_t row_size, size_t col_size>
bool Tower<row_size, col_size>::draw(GUI & g) {
	return g.draw_gfx(pos, gfx, row_size, col_size);
}

template<size_t row_size, size_t col_size>
const int Tower<row_size, col_size>::get_sell_value() const {
	return sell_value;
}

template<size_t row_size, size_t col_size>
const bool Tower<row_size, col_size>::get_blocking() const {
	return blocking;
}

template<size_t row_size, size_t col_size>
int Tower<row_size, col_size>::get_size_rows() const {
	return row_size;
}

template<size_t row_size, size_t col_size>
int Tower<row_size, col_size>::get_size_cols() const {
	return col_size;
}


