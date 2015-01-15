#include "gameboard.hpp"
namespace termd {
	GameBoard::GameBoard(Player& p, int mapid) : player(p), map_id(mapid), size_rows(BOARDROWS), size_cols(BOARDCOLS), tman(vman, pman, p), vman(p), availible_towers({BASIC_TOWER_1x1_ID, RIGHT_TOWER_1x1_ID, WALL_1x1_ID}) {
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

	void GameBoard::load_map() {
		//TODO load map from file
	}

	const int GameBoard::get_size_rows() const {
		return size_rows;
	}

	const int GameBoard::get_size_cols() const {
		return size_cols;
	}

	unsigned int GameBoard::get_number_of_waves() const {
		return waves.size();
	}

	bool GameBoard::build_tower(Coord c, int tower_id) {
		if(availible_towers.find(tower_id) != availible_towers.end() && player.has_tower(tower_id)) {
			return tman.build_tower(c, tower_id);
		} else {
			return false;
		}
	}

	void GameBoard::spawn_virus(int wave_num){
		Coord c(0, size_cols - 1);
		Virus * v;
		for(int r = 2; r < size_rows; r += 2){
			c.set_row(r);
			v = new Virus(c);
			vman.add_virus(v);
		}
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
