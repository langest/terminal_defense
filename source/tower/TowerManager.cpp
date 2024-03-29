#include <tower/TowerManager.h>

namespace termd {

CTowerManager::CTowerManager(std::function<bool(const CCoordinate& position)> isPositionValid)
    : mTowers()
    , mProjectileManager(isPositionValid)
    , mLogger(__FILE__) {}

void CTowerManager::update(std::map<CCoordinate, std::vector<CVirusHandle>>& virusMap) {
    mLogger.log("Update");
    for (auto it = mTowers.begin(); it != mTowers.end();) {
        auto spawnProjectile = [this](std::unique_ptr<IProjectile>&& projectile) {
            this->mProjectileManager.addProjectile(std::move(projectile));
        };
        bool keep = it->second->update(spawnProjectile, virusMap);

        if (!keep) { // If tower is flagging removal, remove it
            it = mTowers.erase(it);
        } else {
            ++it;
        }
    }
    mProjectileManager.update(virusMap);
}

void CTowerManager::initInvasion() {
    for (auto it = mTowers.begin(); it != mTowers.end(); ++it) {
        it->second->updateStartOfWave();
    }
}

void CTowerManager::finishInvasion() {
    for (auto it = mTowers.begin(); it != mTowers.end(); ++it) {
        it->second->updateEndOfWave();
    }
}

bool CTowerManager::isTowerAt(const CCoordinate& coordinate) const {
    return mTowers.find(coordinate) != mTowers.end();
}

const std::map<CCoordinate, std::unique_ptr<ITower>>& CTowerManager::getTowers() const {
    return mTowers;
}

bool CTowerManager::placeTower(const CCoordinate& position, std::unique_ptr<ITower>&& tower) {
    if (this->isTowerAt(position)) {
        return false;
    }
    mTowers.insert(std::make_pair<CCoordinate, std::unique_ptr<ITower>>(CCoordinate(position), std::move(tower)));
    return true;
}

}
