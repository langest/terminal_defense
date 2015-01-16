#include "wall_1x1.hpp"

namespace termd {
	
	Wall_1x1::Wall_1x1(Coord p) : Tower(p, tower_base(3, '#', 10, 10, 0.8, -1)) {
	}

	bool Wall_1x1::update(){
		return true;
	}

}