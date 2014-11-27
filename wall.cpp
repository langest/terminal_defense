#include "wall.hpp"

Wall::Wall(Coord p) {
	pos = p;
	gfx = '#';
}

bool Wall::update(){
	return true;
}