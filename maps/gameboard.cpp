#include "gameboard.hpp"
namespace termd {
	GameBoard::GameBoard(Player& p) : player(p), size_rows(BOARDROWS), size_cols(BOARDCOLS), tman(vman, pman, p), vman(p), availible_towers({BASIC_TOWER_1x1_ID, RIGHT_TOWER_1x1_ID, WALL_1x1_ID}) {
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

	const int GameBoard::get_size_rows() const {
		return size_rows;
	}

	const int GameBoard::get_size_cols() const {
		return size_cols;
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

	void GameBoard::save_game(std::string filename) {
		tman.save_game(filename);
	}

	void GameBoard::load_game(std::string filename) {
		tman.load_game(filename);
	}

}
