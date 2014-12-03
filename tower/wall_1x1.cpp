#include "wall_1x1.hpp"

Wall_1x1::Wall_1x1(Coord p) {
	size_cols = 1;
	size_rows = 1;
	blocking 		= bool*[size_rows];
	blocking[0]		= bool[size_cols];
	blocking[0][0]	= true;
	gfx 		= char*[size_rows];
	gfx[0] 		= char[size_cols];
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
