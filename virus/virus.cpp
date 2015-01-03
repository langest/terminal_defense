#include "virus.hpp"

namespace termd {

	Virus::Virus(Coord start) : max_hp(10), cur_hp(10), stamina(0), stamina_increment(1000), reward(10), path(start) /*, TODO path() */{
		gfx.resize(1);
		gfx[0].resize(1);
		gfx[0][0] = '@';
	}

	Virus::Virus(const Virus & src) : path(src.path) {
		max_hp = src.max_hp;
		cur_hp = src.cur_hp;
		stamina = src.stamina;
		stamina_increment = src.stamina_increment;
		reward = src.reward;
		gfx = src.gfx;
	}

	Virus::~Virus() {
		//Currently nothing to do
	}

	Virus& Virus::operator=(const Virus & src) {
		max_hp = src.max_hp;
		cur_hp = src.cur_hp;
		stamina = src.stamina;
		stamina_increment = src.stamina_increment;
		reward = src.reward;
		gfx = src.gfx;
		path = src.path;
		return *this;
	}

	bool Virus::step(){
		path.step(stamina);
		return path.destination_reached() == false; //True if there are more steps, false otherwise
	}

	Coord Virus::get_pos(){
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

	bool Virus::draw(GUI & g){
		return g.draw_gfx(get_pos(), gfx);
	}

	int Virus::get_reward(){
		return reward;
	}

	bool Virus::destination_reached() {
		return path.destination_reached();
	}

	void Virus::take_damage(int amount) {
		cur_hp -= amount;
	}

}
