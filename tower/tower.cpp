#include "tower.hpp"

namespace termd {
	
	Tower::Tower(Coord c, int nr, int nc, int sellval, float selldec) : pos(c), num_rows(nr), num_cols(nc), sell_value(sellval), sell_decrease(selldec) {}

	Tower::~Tower() {
		//Currently nothing needs to be done
	}

	bool Tower::draw(GUI & g) {
		return g.draw_gfx(pos, gfx);
	}

	int Tower::get_sell_value() const {
		return sell_value;
	}

	bool Tower::get_blocking() const {
		return false;
	}

	int Tower::get_size_rows() const {
		return num_rows;
	}

	int Tower::get_size_cols() const {
		return num_cols;
	}

	bool Tower::end_of_wate() {
		sell_value *= sell_decrease;
	}

}
