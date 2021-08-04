#pragma once

#include <functional>
#include <memory>
#include <vector>

#include <tower/Tower.h>

namespace termd {

class Coordinate;

class CWall : public ITower {
public:
    CWall();

    // ITower
    int getCost() const;
    int getSellValue() const;
    char getGraphic() const;
    bool update(ITower::TSpawnCallback spawnProjectile, const ITower::TVirusList& viruses, const ITower::TVirusMap& virusMap);
    void updateEndOfWave();

private:
    const int mCost;
    const char mGraphic;
};

}
