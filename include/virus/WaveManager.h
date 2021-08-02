#pragma once

#include <queue>

#include <virus/Virus.h>

namespace termd {

class CWaveManager {
public:
    CWaveManager(int numRows, int numCols);
    void initWave();
    template <typename TSpawnCall>
    bool update(TSpawnCall,
        const std::set<CCoordinate>& startPositions,
        const std::set<CCoordinate>& endPositions,
        const std::map<CCoordinate, std::unique_ptr<ITower>>& towers);

private:
    const int mNumRows;
    const int mNumCols;
    unsigned int mUpdateCounter;
};

template <typename TSpawnCall>
bool CWaveManager::update(
    TSpawnCall spawnCall,
    const std::set<CCoordinate>& startPositions,
    const std::set<CCoordinate>& endPositions,
    const std::map<CCoordinate, std::unique_ptr<ITower>>& towers)
{
    if (160 < mUpdateCounter) {
        return false;
    }

    if (0 == mUpdateCounter % 20) {
        const int hp = 10;
        const int staminaIncrement = 40;
        const int reward = 10;
        const int graphic = 's';

        const int r = std::rand();
        const int n = r % startPositions.size();
        auto it = std::begin(startPositions);
        std::advance(it, n);
        const CCoordinate& startPosition = *it;

        spawnCall(std::make_unique<CVirus>(
            hp,
            staminaIncrement,
            reward,
            graphic,
            startPosition,
            endPositions,
            mNumRows,
            mNumCols,
            towers));
    }

    ++mUpdateCounter;

    return true;
}

}
