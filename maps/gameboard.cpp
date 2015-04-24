#include "gameboard.hpp"
namespace termd {
	GameBoard::GameBoard(Player& p, std::string map_identification) :
		player(p),
		map_id(map_identification),
		size_rows(BOARDROWS),
	 	size_cols(BOARDCOLS),
		tman(vman, pman, p),
		towers(size_rows, std::vector<bool>(size_cols, false)),
		vman(p),
		wman(size_rows, size_cols, towers, std::string("info/") + std::string(map_id) + std::string("/wave.info"), vman)	{
				load_map();
	}

	void GameBoard::draw() const {
		GUI::clear_game();

		tman.draw_towers();
		vman.draw_viruses();
		pman.draw_projectiles();
	}

	bool GameBoard::update() {
		bool cont = wman.update();
		cont = vman.update() || cont;
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

			if (c <= 0) {
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
		std::ifstream loadfile;
		loadfile.open(std::string("info/") + map_id + std::string("/gameboard.info"));
		if (loadfile.is_open()) {

			int max_cp;
			loadfile >> max_cp;
			player.set_max_cp(max_cp);
			player.set_cp(max_cp);

			int ram;
			loadfile >> ram;
			player.set_ram(ram);

			int number_of_towers;

			loadfile >> number_of_towers;
			std::vector<char> available_towers(number_of_towers);
			char tmp;
			for (int i = 0; i < number_of_towers; ++i) {
				loadfile >> tmp;
				available_towers.push_back(tmp);
			}

			int n_rows, n_cols;
			loadfile >> n_rows;
			loadfile >> n_cols;

			int tile;
			for (int r = 0; r < n_rows; r++) {
				for (int c = 0; c < n_cols; c++) {
					loadfile >> tile;
					if (tile != 0) {
						grid_env_state.insert(std::pair<Coord, int>(Coord(r,c), tile));
					}
				}
			}
		}
	}

	const int GameBoard::get_size_rows() const {
		return size_rows;
	}

	const int GameBoard::get_size_cols() const {
		return size_cols;
	}

	bool GameBoard::build_tower(Coord c, int tower_id) {
		if (c.get_col() < 0 ||
				c.get_col() >= size_cols ||
				c.get_row() < 0 ||
				c.get_row() >= size_rows ||
				towers[c.get_row()][c.get_col()]) {
		 	return false;
		}

		if(availible_towers.find(tower_id) == availible_towers.end()) {
			return false;
		}

		if (blocked_with(c)) return false;

		towers[c.get_row()][c.get_col()] = tman.build_tower(c, tower_id);
		return towers[c.get_row()][c.get_col()];
	}

	bool GameBoard::next_wave() {
		return wman.spawn();
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
}
