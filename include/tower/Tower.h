#pragma once

#include <functional>
#include <memory>
#include <vector>

#include <tower/projectile/Projectile.h>

namespace termd {

class CVirusHandle;

class ITower {
public:
    typedef std::function<void(std::unique_ptr<IProjectile>&& projectile)> TSpawnCallback;
    typedef std::map<CCoordinate, std::vector<CVirusHandle>> TVirusMap;

    virtual ~ITower() {};

    virtual int getSellValue() const = 0;
    virtual char getGraphic() const = 0;

    virtual bool update(TSpawnCallback spawnProjectile, const TVirusMap& virusMap) = 0;
    virtual void updateStartOfWave() = 0;
    virtual void updateEndOfWave() = 0;
};

template <typename T>
struct STowerTraits {
    /*
        static const int mCost;
        static const char mGraphic;
        */
};

}
