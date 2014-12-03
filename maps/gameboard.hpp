#ifndef termd_game_board
#define termd_game_board

#ifndef termd_map
#define termd_map
#include <map>
#endif //termd_map

#ifndef termd_cstddef
#define termd_cstddef
#include <cstddef>
#endif //termd_cstddef

#include "../definitions"
#include "../gui.hpp"
#include "../tower/tower.hpp"
#include "../tower/wall_1x1.hpp"
#include "../coord.hpp"

class GameBoard  {
	private:
		//player information:
		int ram;

		//Board information:
		std::map<Coord, int> grid_env_state;
		std::map<Coord, int> grid_bld_state;
		int size_rows;
		int size_cols;
		std::map<Coord, Tower &> towers;

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
};

#endif //termd_game_board
