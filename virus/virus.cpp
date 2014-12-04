#include "virus.hpp"

Virus::Virus() : max_hp(10), cur_hp(10), stamina(0), stamina_increment(10) /*, TODO path() */{

}

Virus::Virus(const Virus & src) {
	max_hp = src.max_hp;
	cur_hp = src.cur_hp;
	stamina = src.stamina;
	gfx = src.gfx;
	path = src.path;
}

Virus::~Virus() {
	//Currently nothing to do
}

Virus& Virus::operator=(const Virus & src) {
	max_hp = src.max_hp;
	cur_hp = src.cur_hp;
	stamina = src.stamina;
	gfx = src.gfx;
	return *this;
}

Coord Virus::get_pos(){
	return path.get_curr_pos();
}

bool Virus::update(){
	stamina += stamina_increment;
	//TODO walk with as much stamina as possible
	return true;
}

bool Virus::draw(GUI & g){
	return g.draw_gfx(pos, gfx, num_rows, num_cols);
}