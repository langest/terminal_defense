#include "gameboard.hpp"
namespace termd {
	GameBoard::GameBoard(Player& p, std::string map_identification) :
		player(p),
		map_id(map_identification),
		size_rows(0),
		size_cols(0),
		tman(vman, pman, p),
		vman(p),
		wman(size_rows, size_cols, towers, std::string("info/") + std::string(map_id) + std::string("/wave.info"), vman) {
			load_map();
			wman.set_size(size_rows, size_cols);
			pman.set_size(size_rows, size_cols);
	}

	void GameBoard::draw() const {
		GUI::clear_game(size_rows, size_cols);

		draw_environment();
		tman.draw_towers();
		vman.draw_viruses();
		pman.draw_projectiles();
		GUI::draw_board_frame(board.get_size_rows(), board.get_size_cols());
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
			char tmp;
			for (int i = 0; i < number_of_towers; ++i) {
				loadfile >> tmp;
				available_towers.insert(tmp);
			}

			loadfile >> size_rows;
			loadfile >> size_cols;

			environment = std::vector<std::vector<int> >(size_rows, std::vector<int>(size_cols));

			int tile;
			for (int r = 0; r < size_rows; r++) {
				for (int c = 0; c < size_cols; c++) {
					loadfile >> tile;
					environment[r][c] = tile;
				}
			}
		towers = std::vector<std::vector<bool> >(size_rows, std::vector<bool>(size_cols, false));
		}
	}

	void GameBoard::draw_environment() const {
		for (int r = 0; r < size_rows; ++r) {
			for (int c = 0; c < size_cols; ++c) {
				if (environment[r][c] != 0) {
					GUI::draw_gfx(Coord(r, c), 'O');
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
		int row(c.get_row());
		int col(c.get_col());
		if (col < 0 ||
			col >= size_cols ||
			row < 0 ||
			row >= size_rows ||
			towers[row][col] ||
			environment[row][col] != 0) {
		 	return false;
		}

		if(available_towers.find(tower_id) == available_towers.end()) {
			return false;
		}

		if (blocked_with(c)) return false;

		towers[row][col] = tman.build_tower(c, tower_id);
		return towers[row][col];
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
