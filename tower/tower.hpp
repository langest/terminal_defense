#ifndef termd_tower
#define termd_tower

#ifndef termd_gui
#define termd_gui
#include "gui.hpp"
#endif //termd_gui

#ifndef termd_coord
#define termd_coord
#include "coord.hpp"
#endif //termd_coord

class Tower {
	private:
		
	protected:
		Coord pos;		//Top-left
		bool[][] blocking; //Ground path blocking, children can change this
		char[][] gfx;	//The high-tech 3D model! Children can change this
	public:
		Tower();
		Tower(const Tower &);
		~Tower();

		Tower& operator=(const Tower &);

		//Implemented:
		void draw(GUI &) const;
		const bool get_blocking() const;

		//Virtual:
		virtual bool update() = 0;
};

#endif //termd_tower
