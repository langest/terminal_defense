#ifndef termd_tower
#define termd_tower

#ifndef termd_gui
#define termd_gui
#include "gui.hpp"
#endif //termd_gui

class Tower {
	private:
		Coord pos;
	protected:
		bool blocking; //Ground path blocking, children can change this
		char gfx;	//The high-tech 3D model! Children can change this
	public:
		//Implemented:
		void draw(GUI &) const;
		const bool get_blocking() const;

		//Virtual:
		virtual bool update() = 0;
};

#endif //termd_tower