#pragma once

namespace termd {

class Coordinate;

class ITower {
	public:
		virtual ~ITower() {};

		virtual int getCost() const = 0;
		virtual int getSellValue() const = 0;
		virtual char getGraphic() const = 0;

		virtual bool update() = 0;
		virtual void updateEndOfWave() = 0;
};

}
