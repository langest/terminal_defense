#include "wall_1x1.hpp"

Wall_1x1::Wall_1x1(Coord p) {
	num_rows = 1;
	num_cols = 1;
	blocking.resize(num_rows);
	blocking[0].resize(num_cols);
	blocking[0][0]	= true;
	gfx.resize(num_rows);
	gfx[0].resize(num_cols);
	gfx[0][0]	= '#';

	pos = p;
	sell_value = 100;
	sell_decrease = 0.80;
}

bool Wall_1x1::update(){
	return true;
}

//bool Wall_1x1::end_of_wave_update(){
//	sell_value *= sell_decrease;
//	return true;
//}
