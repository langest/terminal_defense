#pragma once

#include <memory>
#include <vector>

#include <Coordinate.h>
#include <logging/Logger.h>
#include <tower/Tower.h>

namespace termd {

class CRightTower : public ITower {
public:
    CRightTower(const CCoordinate& position);

    int getCost() const;
    int getSellValue() const;
    char getGraphic() const;

    bool update(ITower::TSpawnCallback spawnProjectile, const ITower::TVirusList& viruses, const ITower::TVirusMap& virusMap);
    void updateEndOfWave();

private:
    CCoordinate mPosition;
    const int mCost;
    const int mGraphic;
    int mUpdateCounter;

    CLogger mLogger;
};

}
