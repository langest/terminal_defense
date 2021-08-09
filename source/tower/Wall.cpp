#include <tower/Wall.h>

#include <Coordinate.h>
#include <Gui.h>

namespace termd {

int CWall::getSellValue() const {
    return STowerTraits<CWall>::mCost / 2;
}

char CWall::getGraphic() const {
    return STowerTraits<CWall>::mGraphic;
}

bool CWall::update(ITower::TSpawnCallback /* spawnProjectile */, const ITower::TVirusMap& /* virusMap */) {
    return true;
}

}
