#ifndef termd_path
#define termd_path

#include "../coord.hpp"

class Path {
	private:
		Coord start;
		Coord curr_pos;
	public:
		Path(Coord); //spawn, goal is everything on final row/col
		Path(const Path &);
		~Path();

		Path & operator=(const Path &);

		void step(int);	 //steps as many steps as possible with the given stamina
		Coord get_curr_pos();
};
#endif //termd_path
