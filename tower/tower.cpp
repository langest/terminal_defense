#include "tower.hpp"

namespace termd {
	
	Tower::Tower(Coord c, tower_base tb) : 
	id(tb.id),
	pos(c),
	num_rows(1), 
	num_cols(1), 
	blocking(num_rows, std::vector<bool>(num_cols, true)),
	gfx(num_rows, std::vector<char>(num_cols, tb.gfx)),
	age(0), 
	buy_cost(tb.cost), 
	sell_value(tb.sell_value), 
	sell_decrease(tb.sell_decrease) {}

	Tower::~Tower() {
		//Currently nothing needs to be done
	}

	bool Tower::draw() const {
		return GUI::draw_gfx(pos, gfx);
	}

	int Tower::get_sell_value() const {
		return sell_value;
	}

	const std::vector<std::vector<bool>>& Tower::get_blocking() const {
		return blocking;
	}


	int Tower::get_size_rows() const {
		return num_rows;
	}

	int Tower::get_size_cols() const {
		return num_cols;
	}
	
	int Tower::get_age() const {
		return age;
	}

	int Tower::get_id() const {
		return id;
	}

	int Tower::get_cost() const {
		return buy_cost;
	}
	
	void Tower::set_pos(Coord c) {
		pos = c;
	}

	bool Tower::end_of_wave() {
		sell_value *= sell_decrease;
		++age;
		return true;
	}


}
