#ifndef termd_tower_wall_3x3
#define termd_tower_wall_3x3

#include "../gui.hpp"
#include "tower.hpp"
#include "../coord.hpp"
#include "../definitions"

class Wall_3x3 : public Tower  {
	private:
		
	protected:
		//Coord pos;
		//bool blocking; //Ground path blocking, children can change this
		//char gfx;	//The high-tech 3D model! Children can change this
	public:
		Wall_3x3(Coord);

		//Virtual:
		virtual bool update();
		virtual bool end_of_wave_update();
};

#endif //termd_tower_wall_3x3