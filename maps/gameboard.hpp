#ifndef termd_game_board
#define termd_game_board

#include <set>
#include <queue>
#include <cstddef>

#include <string>

#include "../virus/wave/wavemanager.hpp"
#include "../constants.h"
#include "../gui.hpp"
#include "../coord.hpp"
#include "../player.hpp"
#include "../virus/virus.hpp"
#include "../virus/virusmanager.hpp"
#include "../tower/towermanager.hpp"
#include "../tower/projectiles/projectilemanager.hpp"

namespace termd {
	
	class GameBoard {
		private:
			//player information:
			Player& player;

			//Board information:
			std::string map_id; //info file location
			int size_rows;
			int size_cols;
			std::vector<std::vector<bool> > towers;
			std::vector<std::vector<int> > environment;
			TowerManager tman;
			ProjectileManager pman;
			VirusManager vman;
			WaveManager wman;
			std::vector<std::vector<int>> pathing;
			std::vector<std::vector<char>> gfx;

			std::set<int> available_towers;

			bool blocked_with(Coord);
			void load_map();
			void draw_environment() const;

		public:
			GameBoard(Player&, std::string);
			GameBoard(const GameBoard &) = delete;
			GameBoard& operator=(const GameBoard &) = delete;

			//Main Game Loop:
			void draw() const;
			bool update();

			//Game Logic
			bool build_tower(Coord, int);
			bool next_wave(); //Prepares next wave and returns true iff sucessful

			//Save/load
			bool save_to_file();
			bool load_from_file();

			//Getters
			const int get_size_rows() const;
			const int get_size_cols() const;
			int get_current_wave_number() const;
			int get_number_of_waves() const;
	};
}
#endif //termd_game_board
