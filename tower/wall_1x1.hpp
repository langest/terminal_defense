#ifndef termd_tower_wall_1x1
#define termd_tower_wall_1x1

#ifndef termd_gui
#define termd_gui
#include "gui.hpp"
#endif //termd_gui

#ifndef termd_tower
#define termd_tower
#include "tower.hpp"
#endif //termd_tower

#ifndef termd_coord
#define termd_coord
#include "coord.hpp"
#endif //termd_coord

class Wall_1x1 : public Tower  {
	private:
		
	protected:
		//Coord pos;
		//bool blocking; //Ground path blocking, children can change this
		//char gfx;	//The high-tech 3D model! Children can change this
	public:
		Wall_1x1(Coord);

		//Virtual:
		virtual bool update();
};

#endif //termd_tower_wall_1x1