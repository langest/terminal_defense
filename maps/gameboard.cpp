#include "gameboard.hpp"

GameBoard::GameBoard() {
	ram = 9001; //player ram
	//TODO set size of board
	size_rows = NUMROWS;
	size_cols = NUMCOLS;
}

GameBoard::GameBoard(const GameBoard & src) {
	ram = src.ram;
	size_rows = src.size_rows;
	size_cols = src.size_cols;
	towers = src.towers;
}

GameBoard::~GameBoard() {
	//Not needed, for now
}

GameBoard& GameBoard::operator=(const GameBoard & src) {
	ram = src.ram;
	size_rows = src.size_rows;
	size_cols = src.size_cols;
	towers = src.towers;
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
	switch(tower_id){ //TODO define towers somewhere...
		case WALL_1x1_ID: 
			//is it possible to build here?
			Wall_1x1 w(c);
			//TODO: Check if blocked
			if(ram >= WALL_1x1_COST){
				//SUCCESS!
				ram -= WALL_1x1_COST;
				towers.insert( std::pair<Coord, Tower &>(c, w));
				return true;
			}else{
				//FAIL: Not enough RAM
			}
			break;
	}
	return false;
}
