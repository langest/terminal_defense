#include "wall_3x3.hpp"

Wall_3x3::Wall_3x3(Coord p) {
	size_cols = 3;
	size_rows = 3;
	//Blocking:
	blocking.resize(size_rows);
	for (int i = 0; i < size_rows; ++i)
	{
		blocking[i].resize(size_cols);
		for (int j = 0; j < size_cols; ++j)
		{
			blocking[i][j] = true;
		}
	}

	gfx.resize(size_rows);
	for (int i = 0; i < size_rows; ++i)
	{
		gfx[i].resize(size_cols);
		for (int j = 0; j < size_cols; ++j)
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