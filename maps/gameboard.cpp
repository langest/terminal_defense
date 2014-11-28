#include "gameboard.hpp"

GameBoard::GameBoard() {
	money = 9001; //player money

	blocking = int*[size_rows];
	for (int i = 0; i < size_rows; ++i) {
		blocking[i] = int[size_cols];
	}
}

void GameBoard::draw(GUI & g) {
	//Draw Towers:
	for (std::unordered_map<Coord, Tower>::iterator i = towers.begin(); i != towers.end(); ++i;) {
		if(*i.draw(g) == false) {
			//If tower failed to draw:
			#ifdef DEBUGGING
			#include <iostream>
			std::cout << "Failed to draw Tower: " << *i << std::endl;
			#endif //DEBUGGING
		}
	}
}

bool GameBoard::update() {
	for (std::unordered_map<Coord, Tower>::iterator i = towers.begin(); i != towers.end(); ) {
		if(*i.update() == false) {
			//If tower is flagging removal, remove it!
			i = tower.erase(i);
		}else{
			++i;
		}
	}
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

bool GameBoard::build_tower(Coord c, int tower_id) {
	switch(tower_id){ //TODO define towers somewhere...
		case 1: 
			//is it possible to build here?
			//enough money?
			//success?
			towers.add(Wall_1x1(c));
			break;
		default:
			//unidentified tower_id!
			return false;
	}
	return true;
}