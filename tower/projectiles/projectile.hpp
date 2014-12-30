#ifndef termd_projectile
#define termd_projectile

#include "../../gui.hpp"
#include "../../coord.hpp"
#include "../../virus/virus.hpp"

class Projectile {
	private:

	protected:
		char gfx;
		Coord pos;
	public:
		virtual ~Projectile() = 0;

		virtual bool update() = 0;
		bool draw(GUI &);

};

#endif
