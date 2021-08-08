#pragma once

#include <functional>
#include <map>
#include <memory>
#include <set>
#include <vector>

#include <Coordinate.h>
#include <logging/Logger.h>
#include <tower/projectile/Projectile.h>

namespace termd {

class CVirus;

class CProjectileManager {
public:
    CProjectileManager(std::function<bool(const CCoordinate& position)> isPositionValid);

    bool update(std::map<CCoordinate, std::vector<CVirusHandle>>& virusMap);
    void addProjectile(std::unique_ptr<IProjectile>&& projectile);
    template <typename TDrawCall>
    void draw(TDrawCall&& drawCall);

private:
    std::set<std::unique_ptr<IProjectile>> mProjectiles;
    std::function<bool(const CCoordinate& position)> mIsPositionValid;

    CLogger mLogger;
};

template <typename TDrawCall>
void CProjectileManager::draw(TDrawCall&& drawCall)
{
    mLogger.log("Drawing");
    for (const std::unique_ptr<IProjectile>& projectile : mProjectiles) {
        const char graphic = projectile->getGraphic();
        const CCoordinate& position = projectile->getPosition();
        drawCall(position, graphic);
    }
}

}
