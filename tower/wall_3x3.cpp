#include "wall_3x3.hpp"

namespace termd {
	
	Wall_3x3::Wall_3x3(Coord p) {
		num_cols = 3;
		num_rows = 3;
		//Blocking:
		blocking.resize(num_rows);
		for (int i = 0; i < num_rows; ++i)
		{
			blocking[i].resize(num_cols);
			for (int j = 0; j < num_cols; ++j)
			{
				blocking[i][j] = true;
			}
		}

		gfx.resize(num_rows);
		for (int i = 0; i < num_rows; ++i)
		{
			gfx[i].resize(num_cols);
			for (int j = 0; j < num_cols; ++j)
			{
				gfx[i][j] = '#';
			}
		}

		pos = p;
		sell_value = 100;
		sell_decrease = 0.80;
	}

	bool Wall_3x3::update(){
		return true;
	}

	bool Wall_3x3::end_of_wave_update(){
		sell_value *= sell_decrease;
		return true;
	}
}