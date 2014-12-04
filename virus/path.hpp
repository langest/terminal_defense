#ifndef termd_path
#define termd_path

#include "../coord.hpp"

class Path {
	private:
		Coord start;
		Coord gaol;
		Coord curr_pos;
	public:
		Path(Coord, Coord); //Start -> Goal
		Path(const Path &);
		~Path();

		Path& operator=(const Path &);

		int get_step_cost(); //Cost for taking another step
		Coord step(int);	 //steps as many steps as possible with the given stamina, returns the end pos
		Coord get_curr_pos();
};
#endif //termd_path
