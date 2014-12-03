#include "gameboard.hpp"

GameBoard::GameBoard() {
	ram = 9001; //player ram
	//TODO set size of board
	size_rows = 80;
	size_cols = 80;
}

GameBoard::GameBoard(const GameBoard & src) {
	ram = src.ram;
	size_rows = src.size_rows;
	size_cols = src.size_cols;
}

GameBoard::~GameBoard() {
	//Currently nothing to do here
}

GameBoard& GameBoard::operator=(const GameBoard & src) {
	ram = src.ram;
	size_rows = src.size_rows;
	size_cols = src.size_cols;
	return *this;
}

void GameBoard::render(GUI & g) {
	//Render Towers:
	for (auto i = towers.begin(); i != towers.end(); ++i) {
		if(i->second.draw(g) == false) {
			//If tower failed to draw:
			#ifdef DEBUGGING
			#include <iostream>
			std::cout << "Failed to draw Tower: " << i->second << std::endl;
			#endif //DEBUGGING
		}
	}
}

bool GameBoard::update() {
	for (auto i = towers.begin(); i != towers.end(); ) {
		if(i->second.update() == false) {
			//If tower is flagging removal, remove it!
			i = towers.erase(i);
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

const int GameBoard::get_env_value(Coord c) const {
	return 0; //TODO
}

const int GameBoard::get_bld_value(Coord c) const {
	return 0; //TODO
}

bool GameBoard::location_availible(Coord c) const {
	return true;
}

bool GameBoard::build_tower(Coord c, int tower_id) {
	Wall_1x1* w = new Wall_1x1(c); //TODO memoryleak and proper build
	switch(tower_id){ //TODO define towers somewhere...
		case 1: 
			//is it possible to build here?
			//enough ram?
			//success?
			towers.insert( std::pair<Coord, Tower &>(c, *w));
			break;
		default:
			//unidentified tower_id!
			return false;
	}
	return true;
}
