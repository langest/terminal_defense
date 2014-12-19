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
#include "../tower/tower.hpp"
#include "../tower/wall_1x1.hpp"
#include "../coord.hpp"
#include "../virus/virus.hpp"

class GameBoard  {
	private:
		//player information:
		int ram;

		//Board information:
		std::map<Coord, int> grid_env_state;
		std::map<Coord, int> grid_bld_state;
		int size_rows;
		int size_cols;
		std::map<Coord, Tower*> towers;
		std::vector<Virus*> viruses;
		//std::vector<Projectile*> projectiles;

		void render_towers(GUI &);
		void render_viruses(GUI &);
		void render_projectiles(GUI &);

		void update_towers();
		bool update_viruses();
		void update_projectiles();

		bool is_blocked();

	public:
		GameBoard();
		GameBoard(const GameBoard &);
		~GameBoard();

		GameBoard& operator=(const GameBoard &);

		//Main Game Loop:
		void render(GUI &);
		bool update();

		//Getters and Setters
		const int get_size_rows() const;
		const int get_size_cols() const;
		const int get_env_value(Coord) const;
		const int get_bld_value(Coord) const;
		bool location_availible(Coord) const;
		bool build_tower(Coord, int);
		void spawn_virus(int wave_num);

};

#endif //termd_game_board
