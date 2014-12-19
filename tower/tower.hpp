#ifndef termd_tower
#define termd_tower

#ifndef termd_cstddef
#define termd_cstddef
#include <cstddef>
#endif //term_cstddef

#ifndef termd_vector
#define termd_vector
#include <vector>
#endif //termd_vector

#include "../gui.hpp"
#include "../coord.hpp"
#include "../maps/gameboard.hpp"


class Tower {
	private:
		
	protected:
		//Variables:
		Coord pos;			//Top-left
		GameBoard & gameboard;

		std::vector<std::vector<bool> > blocking; 	//Ground path blocking, children can change this
		std::vector<std::vector<char> > gfx;			//The high-tech 3D model! Children can change this

		int num_rows;
		int num_cols;

		int sell_value;
		float sell_decrease;

		//Functions:
	public:
		Tower();
		virtual ~Tower() = 0;

		//Implemented:
		bool draw(GUI &);
		int get_sell_value() const;
		bool get_blocking() const;
		int get_size_rows() const;
		int get_size_cols() const;

		//Virtual:
		virtual bool update() = 0;
		virtual bool end_of_wave_update() = 0;
};

#endif //termd_tower
