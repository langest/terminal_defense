#pragma once

#include <map>
#include <memory>
#include <queue>

#include <Coordinate.h>
#include <tower/Tower.h>

namespace termd {

class CPath {
	public:
		CPath(
				const CCoordinate& startPosition,
				int numRows,
				int numCols,
				const std::map<CCoordinate, std::unique_ptr<ITower>>& towers
			);

		int step(int stamina);
		const CCoordinate& getCurrentPosition() const;
		bool isDestinationReached() const;

	private:
		struct SStep
		{
			CCoordinate coord;
			int cost;
			SStep(CCoordinate a, int b) : coord(a), cost(b) {}
			SStep(const SStep & src) : coord(src.coord), cost(src.cost) {}
			SStep(SStep && src) : coord(std::move(src.coord)), cost(std::move(src.cost)) {}

			SStep& operator=(const SStep & src) {
				coord = src.coord;
				cost = src.cost;
				return (*this);
			}

			SStep& operator=(SStep && src) {
				coord = std::move(src.coord);
				cost = std::move(src.cost);
				return (*this);
			}
		};

		std::queue<SStep> mPath;

		int heuristic_cost(const CCoordinate &, const CCoordinate &);
};

}
