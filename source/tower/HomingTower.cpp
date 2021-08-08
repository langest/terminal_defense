#include <tower/HomingTower.h>

namespace termd {

CHomingTower::CHomingTower(const CCoordinate& position)
    : mPosition(position)
    , mUpdateCounter(0)
    , mLogger(__FILE__)
{
    mLogger.log("CHomingTower constructor, position: (%d, %d)", position.getRow(), position.getCol());
}

int CHomingTower::getSellValue() const { return STowerTraits<CHomingTower>::mCost / 2; }

char CHomingTower::getGraphic() const { return STowerTraits<CHomingTower>::mGraphic; }

bool CHomingTower::update(ITower::TSpawnCallback /*spawnProjectile*/, const ITower::TVirusMap& /*virusMap*/)
{
    return true;
}

void CHomingTower::updateStartOfWave()
{
    mUpdateCounter = 0;
}

void CHomingTower::updateEndOfWave() { }

}
