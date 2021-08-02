#pragma once

#include <functional>
#include <memory>
#include <vector>

#include <tower/projectile/Projectile.h>

namespace termd {

class CVirus;

class ITower {
public:
    virtual ~ITower() {};

    virtual int getCost() const = 0;
    virtual int getSellValue() const = 0;
    virtual char getGraphic() const = 0;

    virtual bool update(
        std::function<void(std::unique_ptr<IProjectile>&& projectile)> spawnProjectile,
        const std::vector<std::unique_ptr<CVirus>>& viruses,
        const std::map<CCoordinate, std::vector<std::reference_wrapper<std::unique_ptr<CVirus>>>>& virusMap)
        = 0;
    virtual void updateEndOfWave() = 0;
};

}
