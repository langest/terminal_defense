#include <tower/projectile/ProjectileManager.h>

namespace termd {

CProjectileManager::CProjectileManager(std::function<bool(const CCoordinate& position)> isPositionValid)
    : mProjectiles()
    , mIsPositionValid(isPositionValid)
    , mLogger(__FILE__) {}

bool CProjectileManager::update(std::map<CCoordinate, std::vector<CVirusHandle>>& virusMap) {
    mLogger.log("Update");
    for (auto it = mProjectiles.begin(); it != mProjectiles.end();) {
        const bool keep = (*it)->update(virusMap);
        const bool hasValidPosition = mIsPositionValid((*it)->getPosition());
        if (!keep || !hasValidPosition) {
            it = mProjectiles.erase(it);
        } else {
            ++it;
        }
    }
    return mProjectiles.empty();
}

void CProjectileManager::addProjectile(std::unique_ptr<IProjectile>&& projectile) {
    mProjectiles.emplace(std::move(projectile));
}

}
