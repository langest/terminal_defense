#include "gameboard.hpp"

GameBoard::GameBoard() {
	ram = 9001; //player ram
	//TODO set size of board
	size_rows = BOARDROWS;
	size_cols = BOARDCOLS;
}

GameBoard::GameBoard(const GameBoard & src) {
	ram = src.ram;
	size_rows = src.size_rows;
	size_cols = src.size_cols;
	towers = src.towers;
}

GameBoard::~GameBoard() {
	for (auto i = towers.begin(); i != towers.end(); ++i) {
		delete i->second;
	}
	for (auto i = viruses.begin(); i != viruses.end(); ++i) {
		delete i->second;
	}
}

GameBoard& GameBoard::operator=(const GameBoard & src) {
	ram = src.ram;
	size_rows = src.size_rows;
	size_cols = src.size_cols;
	towers = src.towers;
	return *this;
}

void GameBoard::render_towers(GUI & gui) {
	for (auto i = towers.begin(); i != towers.end(); ++i) {
		if(i->second->draw(gui) == false) {
			//If tower failed to draw:
			#ifdef DEBUGGING
			#include <iostream>
			std::cout << "Failed to draw Tower: " << i->second << std::endl;
			#endif //DEBUGGING
		}
	}
}

void GameBoard::render_viruses(GUI & gui) {
	for (auto i = viruses.begin(); i != viruses.end(); ++i) {
		if(i->second->draw(gui) == false) {
			//If tower failed to draw:
			#ifdef DEBUGGING
			#include <iostream>
			std::cout << "Failed to draw Tower: " << i->second << std::endl;
			#endif //DEBUGGING
		}
	}
}

void GameBoard::render_projectiles(GUI & gui) {

}

void GameBoard::render(GUI & gui) {
	this->render_towers(gui);
	this->render_viruses(gui);
	this->render_projectiles(gui);
}

void GameBoard::update_towers() {
	for (auto i = towers.begin(); i != towers.end(); ) {
		if(i->second->update() == false) {
			//If tower is flagging removal, remove it!
			delete i->second;
			i = towers.erase(i);
		}else{
			++i;
		}
	}
}

bool GameBoard::update_viruses() {
	if (viruses.empty()) {
		return false;
	}
	for (auto i = viruses.begin(); i != viruses.end(); ) {
		if(i->second->update() == false) {
			//If virus is flagging removal, remove it!
			//delete i->second;
			dead_viruses.insert(i->second);
			i = viruses.erase(i);
		}else{
			//Check if viruses has reached goal and put them in dead_viruses if so
			++i;
		}
	}
	return true;
}

void GameBoard::update_projectiles() {

}

bool GameBoard::update() {
	//TODO spawn viruses with cool function
	bool ret = this->update_viruses();
	this->update_towers();
	this->update_projectiles();
	return ret;
}

bool GameBoard::is_blocked() {
	bool visited [size_rows][size_cols];
	std::queue<Coord> queue;

	queue.push(Coord(size_rows, 0));
	visited[size_rows][0] = true;

	Coord current;
	int r, c;
	while (queue.size() < 0) {
		current = queue.front();
		queue.pop();
		r = current.get_row();
		c = current.get_col();

		if (r <= 1) {
			return true;
		}

		if (r < size_rows &&
				!visited[r + 1][c]) {
			visited[r + 1][c] = true;
			queue.push(Coord(r + 1, c));
		}
		if (r > 0 &&
				!visited[r - 1][c]) {
			visited[r - 1][c] = true;
			queue.push(Coord(r - 1, c));
		}
		if (c < size_cols &&
				!visited[r][c + 1]) {
			visited[r][c + 1] = true;
			queue.push(Coord(r, c + 1));
		}
		if (c > 0 &&
				!visited[r][c - 1]) {
			visited[r][c - 1] = true;
			queue.push(Coord(r, c - 1));
		}
	}

	return false;
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
			Wall_1x1* w = new Wall_1x1(c);
			//TODO: Check if blocked
			if(ram >= WALL_1x1_COST){
				//SUCCESS!
				ram -= WALL_1x1_COST;
				towers.insert( std::pair<Coord, Tower*>(c, w));
				return true;
			}else{
				//FAIL: Not enough RAM
				delete w;
			}
			break;
	}
	return false;
}

void GameBoard::spawn_virus(int wave_num){
	Coord c(0, size_cols);
	Virus * v;
	for(int r = 0; r < size_rows; r += 2){
		c.set_row(r);
		v = new Virus(c);
		viruses.insert(std::pair<Coord, Virus*>(c, v));
	}
}


const std::map<Coord, Tower*> & GameBoard::get_towers() const {
	return towers;
}

const std::vector<Virus*> & GameBoard::get_viruses() const {
	return viruses;
}

const std::vector<Projectile*> & GameBoard::get_projectiles() const {
	return projectiles;
}

void GameBoard::add_projectile(Projectile& p) {
	projectiles.insert(p);
}
