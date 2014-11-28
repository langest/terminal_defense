#include "gameboard.hpp"

GameBoard::GameBoard(){
	blocking = int*[size_rows];
	for (int i = 0; i < size_rows; ++i)
	{
		blocking[i] = int[size_cols];
	}
}

void GameBoard::draw(GUI & g){
	//g.draw_gfx(pos, blocking, size_rows, size_cols);
}
bool GameBoard::update(){
	return true;
}

const int GameBoard::get_size_rows() const {
	return size_rows;
}

const int GameBoard::get_size_cols() const {
	return size_cols;
}

const int GameBoard::get_pos_value(Coord c) const {
	return blocking[c.get_row()][c.get_col()];
}

bool GameBoard::location_availible(Coord c) const {
	return true;
}

bool GameBoard::place_tower(Tower t) {
	return true;
}