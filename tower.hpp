#ifndef termd_tower
#define termd_tower

#ifndef termd_gui
#define termd_gui
#include "gui.hpp"
#endif //termd_gui

class Tower {
	private:
		Coord pos;
		bool blocking; //Ground path blocking
	protected:
		char gfx;	//The high-tech 3D model!
	public:
		void draw(GUI) const;
		virtual bool update() = 0;
		const bool get_blocking() const;
};

#endif //termd_tower