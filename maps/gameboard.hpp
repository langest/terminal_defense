#ifndef termd_game_board
#define termd_game_board

#ifndef termd_map
#define termd_map
#include <map>
#endif //termd_map

#ifndef termd_vector
#define termd_vector
#include <vector>
#endif //termd_vector

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
			std::map<Coord, int> grid_env_state;
			std::map<Coord, int> grid_bld_state;
			int size_rows;
			int size_cols;
			TowerManager tman;
			ProjectileManager pman;
			VirusManager vman;

			bool is_blocked();

		public:
			GameBoard(Player&);
			GameBoard(const GameBoard &) = delete;
			GameBoard& operator=(const GameBoard &) = delete;

			//Main Game Loop:
			void draw(GUI &);
			bool update();

			//Game Logic
			bool build_tower(Coord, int);
			void spawn_virus(int wave_num);

			//Getters and Setters
			const int get_size_rows() const;
			const int get_size_cols() const;
	};
}
#endif //termd_game_board
