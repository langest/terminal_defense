#pragma once

#include <map>
#include <memory>
#include <vector>

#include <Coordinate.h>
#include <logging/Logger.h>
#include <tower/Tower.h>
#include <tower/projectile/ProjectileManager.h>

namespace termd {

class CVirusHandle;

class CTowerManager {
public:
    CTowerManager(std::function<bool(const CCoordinate& position)> isPositionValid);

    void update(std::map<CCoordinate, std::vector<CVirusHandle>>& virusMap);
    void initInvasion();
    void finishInvasion();

    bool isTowerAt(const CCoordinate& coordinate) const;
    const std::map<CCoordinate, std::unique_ptr<ITower>>& getTowers() const;

    bool placeTower(const CCoordinate& position, std::unique_ptr<ITower>&& tower);
    template <typename TDrawCall>
    void draw(TDrawCall&& drawCall);

private:
    std::map<CCoordinate, std::unique_ptr<ITower>> mTowers;
    CProjectileManager mProjectileManager;
    CLogger mLogger;
};

template <typename TDrawCall>
void CTowerManager::draw(TDrawCall&& drawCall)
{
    for (const auto& pair : mTowers) {
        const CCoordinate& position = pair.first;
        const char graphic = pair.second->getGraphic();
        drawCall(position, graphic);
    }
    mProjectileManager.draw(drawCall);
}

}
