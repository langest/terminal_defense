#include <tower/RightTower.h>

#include <tower/projectile/DirectionProjectile.h>

namespace termd {

CRightTower::CRightTower(const CCoordinate& position)
    : mPosition(position)
    , mCost(10)
    , mGraphic('E')
    , mUpdateCounter(0)
    , mLogger(__FILE__)
{
    mLogger.log("Creating Right Tower");
}

int CRightTower::getCost() const
{
    return mCost;
}

int CRightTower::getSellValue() const
{
    return this->getCost() / 2;
}

char CRightTower::getGraphic() const
{
    return mGraphic;
}

bool CRightTower::update(TSpawnCallback spawnProjectile, const TVirusList& /* viruses */, const TVirusMap& /* virusMap */)
{
    if (0 == mUpdateCounter % 40) {
        mLogger.log("Spawning direction projectile");
        spawnProjectile(std::make_unique<CDirectionProjectile>(CDirectionProjectile::EDirection::Right, mPosition));
    }
    ++mUpdateCounter;
    return true;
}

void CRightTower::updateEndOfWave() { }

}
