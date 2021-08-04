#include <tower/Wall.h>

#include <Coordinate.h>
#include <Gui.h>

namespace termd {

CWall::CWall()
    : mCost(3)
    , mGraphic('#')
{
}

int CWall::getCost() const
{
    return mCost;
}

int CWall::getSellValue() const
{
    return mCost / 2;
}

char CWall::getGraphic() const
{
    return mGraphic;
}

bool CWall::update(TSpawnCallback /* spawnProjectile */, const TVirusList& /* viruses */, const TVirusMap& /* virusMap */)
{
    return true;
}

void CWall::updateEndOfWave() { }

}
