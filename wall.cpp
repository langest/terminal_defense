#include "tower.hpp"

Wall::Wall(Coord p) {
	pos = p;
	gfx = '#';
}

bool Wall::update(){
	return true;
}