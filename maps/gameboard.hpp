#ifndef termd_game_board
#define termd_game_board

#include "gui.hpp"
#include "tower.hpp"
#include "coord.hpp"

class GameBoard  {
	private:
		int** blocking;
		int size_rows;
		int size_cols;
	public:
		//Main Game Loop:
		void draw(GUI &);
		bool update();

		//Getters and Setters
		const int get_size_rows() const;
		const int get_size_cols() const;
		const int get_pos_value(Coord) const;
		bool location_availible(Coord) const;
		bool place_tower(Tower);
};

#endif //termd_game_board