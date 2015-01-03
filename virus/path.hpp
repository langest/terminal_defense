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
		const Coord coord;
		const int cost;
		Step(Coord a, int b) : coord(a), cost(b) {}
	};

	class Path {
		private:
			std::queue<Step> path;
		public:
			Path(Coord); //spawn, goal is everything on final row/col
			Path(const Path &) = delete;
			~Path();

			Path & operator=(const Path &) = delete;

			void step(int &);	 //steps as many steps as possible with the given stamina, will side-effect the inputed stamina
			Coord get_curr_pos() const;
			bool destination_reached() const;
	};

}

#endif //termd_path
