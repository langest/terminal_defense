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

    int getSellValue() const;
    char getGraphic() const;

    bool update(TSpawnCallback spawnProjectile, const TVirusMap& virusMap);
    void updateStartOfWave();
    void updateEndOfWave();

private:
    CCoordinate mPosition;
    int mUpdateCounter;

    CLogger mLogger;
};

template <>
struct STowerTraits<CRightTower> {
    static const int mCost = 10;
    static const char mGraphic = 'E';
};

}
