#include <virus/VirusManager.h>

#include <algorithm>

#include <Player.h>

namespace termd {

CVirusManager::CVirusManager(CPlayer& player, int numRows, int numCols)
    : mPlayer(player)
    , mViruses()
    , mWaveManager(numRows, numCols)
    , mNextId(0)
    , mLogger(__FILE__) {}

bool CVirusManager::update(
    const std::set<CCoordinate>& startPositions,
    const std::set<CCoordinate>& endPositions,
    const std::map<CCoordinate, std::unique_ptr<ITower>>& towers) {
    mLogger.log("Update");

    for (auto& it : mViruses) {
        std::unique_ptr<CVirus>& virus = it.second;
        virus->update([this](int damage) { mPlayer.modifyControlPoints(-damage); });
    }

    mLogger.log("Update wave manager");
    const bool moreVirusesIncoming = mWaveManager.update(
        std::bind(&CVirusManager::addVirus, this, std::placeholders::_1),
        startPositions,
        endPositions,
        towers);

    mLogger.log("Update done");
    return !mViruses.empty() || moreVirusesIncoming || this->hasOpenHandle();
}

void CVirusManager::initInvasion() {
    mWaveManager.initWave();
}

void CVirusManager::finishInvasion() {
    if (this->hasOpenHandle()) {
        mLogger.logError("Finishing invasion even though handles are open!");
    }
    mViruses.clear();
}

std::map<CCoordinate, std::vector<CVirusHandle>> CVirusManager::getCoordinateVirusMap() {
    std::map<CCoordinate, std::vector<CVirusHandle>> map;

    for (const auto& it : mViruses) {
        const CVirus::TVirusId virusId = it.first;
        const CCoordinate position = it.second->getPosition();
        map[position].emplace_back(CVirusHandle(virusId, *this));
    }

    return map;
}

bool CVirusManager::hasNextWave() const {
    return false;
}

void CVirusManager::createHandle(CVirus::TVirusId id) {
    ++mVirusHandleCounters[id];
}

void CVirusManager::releaseHandle(CVirus::TVirusId id) {
    --mVirusHandleCounters[id];
}

const CVirus& CVirusManager::get(CVirus::TVirusId virusId) const {
    return this->get(virusId);
}

CVirus& CVirusManager::get(CVirus::TVirusId virusId) {
    return *mViruses[virusId];
}

void CVirusManager::addVirus(std::unique_ptr<CVirus>&& virus) {
    mViruses.emplace(mNextId++, std::move(virus));
}

bool CVirusManager::hasOpenHandle() {
    for (auto& it : mVirusHandleCounters) {
        const int counter = it.second;
        if (0 < counter) {
            return true;
        }
    }
    return false;
}

}
