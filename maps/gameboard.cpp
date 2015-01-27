#include "gameboard.hpp"
namespace termd {
	GameBoard::GameBoard(Player& p, int mapid) :
		player(p),
		map_id(mapid),
		size_rows(BOARDROWS),
	 	size_cols(BOARDCOLS),
		tman(vman, pman, p),
		towers(size_rows, std::vector<bool>(size_cols, false)),
		vman(p),
		availible_towers({0, 1, 2}), //TODO solve hardcodedness
		wave_number(0),
		wave(vman)	{

		//TODO load map of mapid
	}

	void GameBoard::draw() const {
		GUI::clear_game();

		tman.draw_towers();
		vman.draw_viruses();
		pman.draw_projectiles();
	}

	bool GameBoard::update() {
		//TODO spawn viruses with cool function
		bool cont = vman.update();
		pman.update();
		tman.update();
		if (!cont) {
			vman.end_of_wave();
			pman.end_of_wave();
			tman.end_of_wave();
		}
		return cont;
	}

	bool GameBoard::blocked_with(Coord coord) {
		bool visited [size_rows][size_cols];
		for (int r = 0; r < size_rows; ++r) {
			for (int c = 0; c < size_cols; ++c) {
				visited[r][c] = false;
			}
		}
		visited[coord.get_row()][coord.get_col()] = true;
		std::queue<Coord> queue;

		queue.push(Coord(0, size_cols-1));
		visited[0][size_cols-1] = true;

		Coord current;
		int r, c;
		while (!queue.empty()) {
			current = queue.front();
			queue.pop();
			r = current.get_row();
			c = current.get_col();

			//GUI::draw_gfx(current, '*');
			//getch();
			//GUI::clear_game();

			if (c <= 1) {
				return false;
			}

			if (r+1 < size_rows &&
					!visited[r + 1][c] &&
					tman.get(Coord(r+1,c)) == nullptr) {
				visited[r + 1][c] = true;
				queue.push(Coord(r + 1, c));
			}
			if (r > 0 &&
					!visited[r - 1][c] &&
					tman.get(Coord(r-1,c)) == nullptr) {
				visited[r - 1][c] = true;
				queue.push(Coord(r - 1, c));
			}
			if (c+1 < size_cols &&
					!visited[r][c + 1] &&
					tman.get(Coord(r,c+1)) == nullptr) {
				visited[r][c + 1] = true;
				queue.push(Coord(r, c + 1));
			}
			if (c > 0 &&
					!visited[r][c - 1] &&
					tman.get(Coord(r,c-1)) == nullptr) {
				visited[r][c - 1] = true;
				queue.push(Coord(r, c - 1));
			}
		}

		return true;
	}

	void GameBoard::load_map() {
		//TODO load map from file
	}

	const int GameBoard::get_size_rows() const {
		return size_rows;
	}

	const int GameBoard::get_size_cols() const {
		return size_cols;
	}

	int GameBoard::get_current_wave_number() const {
		return wave_number;
	}

	int GameBoard::get_number_of_waves() const {
		return 1;
		//return waves.size();
	}

	bool GameBoard::build_tower(Coord c, int tower_id) {
		if (c.get_col() < 0 ||
				c.get_col() >= size_cols ||
				c.get_row() < 0 ||
				c.get_row() >= size_rows ||
				towers[c.get_row()][c.get_col()]) {
		 	return false;
		}

		if (blocked_with(c)) return false;

		towers[c.get_row()][c.get_col()] = tman.build_tower(c, tower_id);
		return towers[c.get_row()][c.get_col()];
	}

	void GameBoard::spawn_virus(){
		wave.spawn(wave_number, size_rows, size_cols, towers);
	}

	bool GameBoard::save_to_file() {
		bool b1 = tman.save_to_file(std::string("tman.save"));
		std::ofstream savefile;
		savefile.open("board.save");
		if (savefile.is_open()) {
			savefile << map_id << std::endl;
			savefile.close();
		} else {
			return false;
		}
		return b1;
	}

	bool GameBoard::load_from_file() {
		bool b = tman.load_from_file(std::string("tman.save"));
		std::ifstream loadfile;
		loadfile.open("board.save");
		if (loadfile.is_open()) {
			loadfile >> map_id;
			load_map();
			return b && true;
		}
		return false;
	}

	void GameBoard::set_wave_number(int num) {
		if (num < 0) return;
		wave_number = num;
	}
}
