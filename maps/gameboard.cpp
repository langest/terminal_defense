#include "gameboard.hpp"

GameBoard::GameBoard() : ram(9001), size_rows(BOARDROWS), size_cols(BOARDCOLS), tman(vman, pman) {
}

GameBoard::GameBoard(const GameBoard & src) : ram(src.ram), size_rows(src.size_rows), size_cols(src.size_cols), tman(vman, pman), pman(src.pman), vman(src.vman) {
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

void GameBoard::draw(GUI & gui) {
	tman.draw_towers(gui);
	vman.draw_viruses(gui);
	pman.draw_projectiles(gui);
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
