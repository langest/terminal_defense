#include "tower.hpp"

Tower::Tower() : pos(0, 0), blocking(false), gfx(' '){

}

Tower::Tower(const Tower & src) {
	pos = src.pos;
	blocking = src.blocking;
	gfx = src.gfx;
}

Tower::~Tower() {
	//Currently nothing needs to be done
}

Tower& Tower::operator=(const Tower & src) {
	pos = src.pos;
	blocking = src.blocking;
	gfx = src.gfx;
}

void Tower::draw(GUI & g) const {
	g.draw(pos, gfx);
}

inline const bool Tower::get_blocking() const {
	return blocking;
}
