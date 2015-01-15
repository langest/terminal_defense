#include "virus.hpp"

namespace termd {

	Virus::Virus(Coord start) : max_hp(15), cur_hp(max_hp), stamina(0), stamina_increment(75), reward(10), path(start) /*, TODO path() */{
		gfx.resize(1);
		gfx[0].resize(1);
		gfx[0][0] = '@';
	}

	Virus::~Virus() {
		//Currently nothing to do
	}

	bool Virus::step(){
		path.step(stamina);
		return path.destination_reached() == false; //True if there are more steps, false otherwise
	}

	Coord Virus::get_pos() const{
		return path.get_curr_pos();
	}

	bool Virus::update(){
		if(cur_hp <= 0) {
			return false;
		}
		stamina += stamina_increment;
		step();
		return true;
	}

	bool Virus::draw() const {
		return GUI::draw_gfx(get_pos(), gfx);
	}

	int Virus::get_reward() const {
		return reward;
	}

	bool Virus::destination_reached() const {
		return path.destination_reached();
	}

	void Virus::take_damage(int amount) {
		cur_hp -= amount;
	}

}
