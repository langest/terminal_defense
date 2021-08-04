#pragma once

#include <functional>
#include <memory>
#include <vector>

#include <tower/Tower.h>

namespace termd {

class Coordinate;

class CWall : public ITower {
public:
    CWall() {};

    // ITower
    int getSellValue() const;
    char getGraphic() const;
    bool update(ITower::TSpawnCallback spawnProjectile, const ITower::TVirusList& viruses, const ITower::TVirusMap& virusMap);
    void updateStartOfWave() {};
    void updateEndOfWave() {};
};

template <>
struct STowerTraits<CWall> {
    static const int mCost = 1;
    static const char mGraphic = '#';
};

}
