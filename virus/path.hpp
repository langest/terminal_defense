#ifndef termd_path
#define termd_path

#ifndef termd_queue
#define termd_queue
#include <queue>
#endif //termd_queue

#include "../coord.hpp"
#include "../definitions"

namespace termd {

	struct Step
	{
		Coord coord;
		int cost;
		Step(Coord a, int b) : coord(a), cost(b) {}
	};

	class Path {
		private:
			std::queue<Step> path;
		public:
			Path(Coord); //spawn, goal is everything on final row/col
			Path(const Path &);
			~Path();

			Path & operator=(const Path &);

			void step(int &);	 //steps as many steps as possible with the given stamina, will side-effect the inputed stamina
			Coord get_curr_pos();
			bool destination_reached();
	};

}

#endif //termd_path
