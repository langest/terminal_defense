#ifndef termd_wall_1x1
#define termd_wall_1x1

#include "../gui.hpp"
#include "tower.hpp"
#include "../coord.hpp"
#include "../definitions"

namespace termd {
	
	class Wall_1x1 : public Tower {
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

}
#endif //termd_tower_wall_1x1
