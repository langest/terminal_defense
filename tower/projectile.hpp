#ifndef termd_projectile
#define termd_projectile

#include "../gui.hpp"
#include "../coord.hpp"

class Projectile{
	private:

	protected:
		char gfx;
		Coord pos;
		Coord target;
		int speed_increment;
		int speed_curr;
	public:
		Projectile(Coord, Coord);
		Projectile(const Projectile &);
		~Projectile();
		operator=(const Projectile &);

		bool update();
		bool draw(GUI &);
};

#endif //termd_projectile
