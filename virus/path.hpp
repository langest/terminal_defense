#ifndef termd_path
#define termd_path

#include <queue>
#include <stack>
#include <utility>

#include "../gui.hpp"
#include "../definitions"
#include "../coord.hpp"
#include "../definitions"

namespace termd {

	struct Step
	{
		Coord coord;
		int cost;
		Step(Coord a, int b) : coord(a), cost(b) {}
		Step(const Step & src) : coord(src.coord), cost(src.cost) {}
		Step(Step && src) : coord(std::move(src.coord)), cost(std::move(src.cost)) {}

		Step& operator=(const Step & src) {
			coord = src.coord;
			cost = src.cost;
			return (*this);
		}

		Step& operator=(Step && src) {
			coord = std::move(src.coord);
			cost = std::move(src.cost);
			return (*this);
		}
	};

	class Path {
		private:
			std::queue<Step> path;

			int heuristic_cost(const Coord &, const Coord &);
		public:
			Path(Coord);
			Path(Coord, int nr, int nc, const std::vector<std::vector<bool> > & towers); //spawn, goal is everything on final row/col
			//Assumes that a path is available
			Path(const Path &);
			Path(Path &&);
			~Path();

			Path & operator=(const Path &);
			Path & operator=(Path &&);

			void step(int &);	 //steps as many steps as possible with the given stamina, will side-effect the inputed stamina
			Coord get_curr_pos() const;
			bool destination_reached() const;
	};

}

#endif //termd_path
