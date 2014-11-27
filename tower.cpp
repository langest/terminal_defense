#include "tower.hpp"

void Tower::draw(GUI & g) const {
	g.draw(pos, gfx);
}

inline const bool Tower::get_blocking() const {
	return blocking;
}