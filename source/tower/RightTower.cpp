#include <tower/RightTower.h>

#include <tower/projectile/DirectionProjectile.h>

namespace termd {

CRightTower::CRightTower(const CCoordinate& position)
    : mPosition(position)
    , mUpdateCounter(0)
    , mLogger(__FILE__)
{
    mLogger.log("Creating Right Tower");
}

int CRightTower::getSellValue() const
{
    return STowerTraits<CRightTower>::mCost / 2;
}

char CRightTower::getGraphic() const
{
    return STowerTraits<CRightTower>::mGraphic;
}

bool CRightTower::update(TSpawnCallback spawnProjectile, const TVirusList& /* viruses */, const TVirusMap& /* virusMap */)
{
    if (0 == mUpdateCounter % 63) {
        mLogger.log("Spawning direction projectile");
        spawnProjectile(std::make_unique<CDirectionProjectile<EDirection::Right>>(mPosition));
    }
    ++mUpdateCounter;
    return true;
}

void CRightTower::updateStartOfWave()
{
    mUpdateCounter = 0;
}

void CRightTower::updateEndOfWave() { }

}
