#ifndef termd_game_board
#define termd_game_board

#ifndef termd_unordered_map
#define termd_unordered_map
#include <unordered_map>
#endif //termd_unordered_map

#include "../gui.hpp"
#include "../tower/tower.hpp"
#include "../tower/wall_1x1.hpp"
#include "../coord.hpp"


class GameBoard  {
	private:
		//player information:
		int ram;

		//Board information:
		int** blocking;	//TODO: Replace with another map!
		int size_rows;
		int size_cols;
		std::unordered_map<Coord, Tower> towers;

	public:
		GameBoard();
		GameBoard(const GameBoard &);
		~GameBoard();

		GameBoard& operator=(const GameBoard &);

		//Main Game Loop:
		void draw(GUI &);
		bool update();

		//Getters and Setters
		const int get_size_rows() const;
		const int get_size_cols() const;
		const int get_pos_value(Coord) const;
		bool location_availible(Coord) const;
		bool build_tower(Coord, int);
};

#endif //termd_game_board
