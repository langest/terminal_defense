#include "gameboard.hpp"

GameBoard::GameBoard() : size_rows(BOARDROWS), size_cols(BOARDCOLS) {
	ram = 9001; //player ram
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
		delete *i;
	}
}

GameBoard& GameBoard::operator=(const GameBoard & src) {
	ram = src.ram;
	size_rows = src.size_rows;
	size_cols = src.size_cols;
	towers = src.towers;
	return *this;
}

void GameBoard::draw_towers(GUI & gui) {
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

void GameBoard::draw_viruses(GUI & gui) {
	for (auto i = viruses.begin(); i != viruses.end(); ++i) {
		if((*i)->draw(gui) == false) {
			//If tower failed to draw:
			#ifdef DEBUGGING
			#include <iostream>
			std::cout << "Failed to draw Tower: " << (**i) << std::endl;
			#endif //DEBUGGING
		}
	}
}

void GameBoard::draw_projectiles(GUI & gui) {

}

void GameBoard::draw(GUI & gui) {
	this->draw_towers(gui);
	this->draw_viruses(gui);
	this->draw_projectiles(gui);
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


void GameBoard::update_projectiles() {
	pman.update();
}

bool GameBoard::update() {
	//TODO spawn viruses with cool function
	bool ret = vman.update();
	tman.update();
	pman.update();
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

bool GameBoard::build_tower(Coord c, int tower_id) {
	return tman.build_tower(c, tower_id);
}

void GameBoard::spawn_virus(int wave_num){
	Coord c(0, size_cols);
	Virus * v;
	for(int r = 0; r < size_rows; r += 2){
		c.set_row(r);
		v = new Virus(c);
		virus_manager.add(v);
	}
}
