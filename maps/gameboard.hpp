#ifndef termd_game_board
#define termd_game_board

#ifndef termd_map
#define termd_map
#include <map>
#endif //termd_map

#ifndef termd_set
#define termd_set
#include <set>
#endif //termd_set

#ifndef termd_queue
#define termd_queue
#include <queue>
#endif //termd_queue

#ifndef termd_cstddef
#define termd_cstddef
#include <cstddef>
#endif //termd_cstddef

#include "../definitions"
#include "../gui.hpp"
#include "../coord.hpp"
#include "../player.hpp"
#include "../virus/virus.hpp"
#include "../virus/virusmanager.hpp"
#include "../tower/towermanager.hpp"
#include "../tower/projectiles/projectilemanager.hpp"

namespace termd {
	
	class GameBoard  {
		private:
			//player information:
			Player& player;

			//Board information:
			const int map_id;
			std::map<Coord, int> grid_env_state;
			std::map<Coord, int> grid_bld_state;
			const int size_rows;
			const int size_cols;
			TowerManager tman;
			ProjectileManager pman;
			VirusManager vman;
			std::vector<std::vector<int>> pathing;
			std::vector<std::vector<char>> gfx;

			std::set<int> availible_towers;

			int wave_number;
			std::vector<int> waves; //TODO wave object for this map in this vector

			bool is_blocked();

		public:
			GameBoard(Player&, int);
			GameBoard(const GameBoard &) = delete;
			GameBoard& operator=(const GameBoard &) = delete;

			//Main Game Loop:
			void draw() const;
			bool update();

			//Game Logic
			bool build_tower(Coord, int);
			void spawn_virus(int wave_num);
			bool save_to_file();
			void set_wave_number(int);

			//Save/load
			void save_game(std::string filename);
			void load_game(std::string filename);

			//Getters
			const int get_size_rows() const;
			const int get_size_cols() const;
			unsigned int get_number_of_waves() const;
	};
}
#endif //termd_game_board
