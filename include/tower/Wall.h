#pragma once

#include <vector>
#include <functional>

#include <tower/Tower.h>

namespace termd {

class Coordinate;

class CWall : public ITower {
	public:
		CWall();
		~CWall() {};

		// ITower
		int getCost() const;
		int getSellValue() const;
		char getGraphic() const;
		bool update();
		void updateEndOfWave();

	private:
		const int mCost;
		const char mGraphic;
};

}
