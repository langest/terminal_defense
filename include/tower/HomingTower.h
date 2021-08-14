#pragma once

#include <Coordinate.h>
#include <logging/Logger.h>
#include <tower/Tower.h>

#include <memory>
#include <optional>
#include <vector>

namespace termd {

class CHomingTower : public ITower {
public:
    CHomingTower(const CCoordinate& position);

    int getCost() const;
    int getSellValue() const;
    char getGraphic() const;

    bool update(TSpawnCallback spawnProjectile, ITower::TVirusMap& virusMap);
    void updateStartOfWave();
    void updateEndOfWave() {};

private:
    std::optional<CVirusHandle> findTarget(ITower::TVirusMap& virusMap) ;

    const CCoordinate mPosition;
    int mUpdateCounter;
    const int mSquaredRange;

    CLogger mLogger;
};

template <>
struct STowerTraits<CHomingTower> {
    static const int mCost = 60;
    static const char mGraphic = ';';
    static const int mRange = 6;
};

}
