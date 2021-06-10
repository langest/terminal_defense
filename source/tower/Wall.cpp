#include <tower/Wall.h>

#include <Gui.h>
#include <Coordinate.h>

namespace termd {

CWall::CWall() : mCost(10), mGraphic('#') {}

int CWall::getCost() const {
	return mCost;
}

int CWall::getSellValue() const {
	return mCost/2;
}

char CWall::getGraphic() const {
	return mGraphic;
}

bool CWall::update() {
	return true;
}

void CWall::updateEndOfWave() {
	return;
}

}
