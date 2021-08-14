#include <tower/HomingTower.h>

#include <tower/projectile/HomingProjectile.h>
#include <virus/Virus.h>

namespace termd {

CHomingTower::CHomingTower(const CCoordinate& position)
    : mPosition(position)
    , mUpdateCounter(0)
    , mSquaredRange(STowerTraits<CHomingTower>::mRange * STowerTraits<CHomingTower>::mRange)
    , mLogger(__FILE__) {
    mLogger.log("CHomingTower constructor, position: (%d, %d)", position.getRow(), position.getCol());
}

int CHomingTower::getSellValue() const {
    return STowerTraits<CHomingTower>::mCost / 2;
}

char CHomingTower::getGraphic() const {
    return STowerTraits<CHomingTower>::mGraphic;
}

bool CHomingTower::update(ITower::TSpawnCallback spawnProjectile, ITower::TVirusMap& virusMap) {
    if (130 < mUpdateCounter) {
        std::optional<CVirusHandle> target = this->findTarget(virusMap);
        if (target) {
            mLogger.log("Spawning homing projectile");
            spawnProjectile(std::make_unique<CHomingProjectile>(mPosition, *target));
            mUpdateCounter = 0;
        }
    }
    ++mUpdateCounter;
    return true;
}

void CHomingTower::updateStartOfWave() {
    mUpdateCounter = 0;
}

std::optional<CVirusHandle> CHomingTower::findTarget(ITower::TVirusMap& virusMap) {
    std::optional<CVirusHandle> closestVirus = std::nullopt;
    double closestDistance;

    for (auto pair : virusMap) {
        const CCoordinate& position = pair.first;

        const double distancedSquared = position.squaredDistance(mPosition);
        if (mSquaredRange < distancedSquared) {
            mLogger.log("Target too far away: %f < %f", mSquaredRange, distancedSquared);
            continue;
        }

        std::vector<CVirusHandle> viruses = pair.second;
        for (CVirusHandle& virusHandle : viruses) {
            if (!virusHandle->isActive()) {
                continue;
            }
            if (std::nullopt == closestVirus ||
                distancedSquared < closestDistance) { // TODO, maybe choose random if many are in range
                closestVirus = virusHandle;
                closestDistance = distancedSquared;
                break;
            }
        }
    }
    if (std::nullopt == closestVirus) {
        return std::nullopt;
    }
    return closestVirus;
}

}
