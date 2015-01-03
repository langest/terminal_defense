#include "wall_1x1.hpp"

namespace termd {
	
	Wall_1x1::Wall_1x1(Coord p) : Tower(p, 1, 1, WALL_1x1_SELL, WALL_1x1_SELL_DECREASE) {
		blocking.resize(num_rows);
		blocking[0].resize(num_cols);
		blocking = {{true}};
		gfx.resize(num_rows);
		gfx[0].resize(num_cols);
		gfx = {{'#'}};
	}

	bool Wall_1x1::update(){
		return true;
	}

	bool Wall_1x1::end_of_wave_update(){
		sell_value *= sell_decrease;
		return true;
	}
}