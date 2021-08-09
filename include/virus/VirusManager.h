#pragma once

#include <map>
#include <memory>
#include <set>
#include <vector>

#include <logging/Logger.h>
#include <virus/Virus.h>
#include <virus/WaveManager.h>

namespace termd {

class CPlayer;
class ITower;

class CVirusManager {
public:
    CVirusManager(CPlayer& player, int numRows, int numCols);

    bool update(
        const std::set<CCoordinate>& startPositions,
        const std::set<CCoordinate>& endPositions,
        const std::map<CCoordinate, std::unique_ptr<ITower>>& towers);
    void initInvasion();
    void finishInvasion();

    std::map<CCoordinate, std::vector<CVirusHandle>> getCoordinateVirusMap();

    template <typename TDrawCall>
    void draw(TDrawCall&& drawCall);

    bool hasNextWave() const;

    // Used by CVirusHandle
    void createHandle(CVirus::TVirusId id);
    void releaseHandle(CVirus::TVirusId id);
    const CVirus& get(CVirus::TVirusId virusId) const;
    CVirus& get(CVirus::TVirusId virusId);

private:
    void addVirus(std::unique_ptr<CVirus>&& virus);
    bool hasOpenHandle();

    CPlayer& mPlayer;
    std::map<CVirus::TVirusId, std::unique_ptr<CVirus>> mViruses;
    std::map<CVirus::TVirusId, int> mVirusHandleCounters;
    CWaveManager mWaveManager;
    int mNextId;
    CLogger mLogger;
};

template <typename TDrawCall>
void CVirusManager::draw(TDrawCall&& drawCall) {
    for (auto it = mViruses.begin(); it != mViruses.end(); ++it) {
        if (!it->second->isActive()) {
            continue;
        }
        const char graphic = it->second->getGraphic();
        const CCoordinate& position = it->second->getPosition();
        drawCall(position, graphic);
    }
}

}
