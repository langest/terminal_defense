#include "virus.hpp"

Virus::Virus() : max_hp(10), cur_hp(10), stamina(10), gfx(' ') /*, TODO path() */{

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
}
