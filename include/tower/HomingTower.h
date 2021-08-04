#pragma once

#include <Coordinate.h>
#include <logging/Logger.h>
#include <tower/Tower.h>

#include <memory>
#include <vector>

namespace termd {

class CHomingTower : public ITower {
public:
    CHomingTower(const CCoordinate& position);

    int getCost() const;
    int getSellValue() const;
    char getGraphic() const;

    bool update(ITower::TSpawnCallback spawnProjectile, const ITower::TVirusList& viruses, const ITower::TVirusMap& virusMap);
    void updateStartOfWave();
    void updateEndOfWave();

private:
    CCoordinate mPosition;
    int mUpdateCounter;

    CLogger mLogger;
};

template <>
struct STowerTraits<CHomingTower> {
    static const int mCost = 60;
    static const char mGraphic = ';';
};

}
