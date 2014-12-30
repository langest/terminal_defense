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

#include "../virus/virusmanager.hpp"
#include "../definitions"
#include "../gui.hpp"
#include "../tower/tower.hpp"
#include "../tower/wall_1x1.hpp"
#include "../tower/projectiles/projectile.hpp"
#include "../coord.hpp"
#include "../virus/virus.hpp"

//class Tower; //Forward declaration because of circle reference
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
		std::vector<Projectile*> projectiles;

		void draw_towers(GUI &);
		void draw_viruses(GUI &);
		void draw_projectiles(GUI &);

		VirusManager virus_manager;
		void update_towers();
		void update_projectiles();

		bool is_blocked();

	public:
		GameBoard();
		GameBoard(const GameBoard &);
		~GameBoard();

		GameBoard& operator=(const GameBoard &);

		//Main Game Loop:
		void draw(GUI &);
		bool update();

		//Game Logic
		bool build_tower(Coord, int);
		void spawn_virus(int wave_num);

		//Getters and Setters
		const int get_size_rows() const;
		const int get_size_cols() const;
		const int get_env_value(Coord) const;
		const int get_bld_value(Coord) const;
		bool location_availible(Coord) const;

		const std::map<Coord, Tower*> & get_towers() const;
		const std::vector<Virus*> & get_viruses() const;
		const std::vector<Projectile*> & get_projectiles() const;
		void add_projectile(Projectile*);
};

#endif //termd_game_board
