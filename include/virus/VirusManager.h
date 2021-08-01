#pragma once

#include <memory>
#include <set>
#include <vector>

#include <logging/Logger.h>
#include <virus/Virus.h>
#include <virus/WaveManager.h>

namespace termd {

class ITower;
class CPlayer;

class CVirusManager {
	public:
		CVirusManager(CPlayer& player, int numRows, int numCols);

		bool update(
			const std::set<CCoordinate>& startPositions,
			const std::set<CCoordinate>& endPositions,
			const std::map<CCoordinate, std::unique_ptr<ITower>>& towers
			);
		void initInvasion();
		void finishInvasion();

		const std::vector<std::unique_ptr<CVirus>>& getViruses() const;
		std::map<CCoordinate, std::vector<std::reference_wrapper<std::unique_ptr<CVirus>>>> getCoordinateVirusMap();

		template <typename TDrawCall>
		void draw(TDrawCall&& drawCall);

		bool hasNextWave() const;

	private:
		void addVirus(std::unique_ptr<CVirus>&& virus);

		CPlayer& mPlayer;
		std::vector<std::unique_ptr<CVirus>> mViruses;
		CWaveManager mWaveManager;
		CLogger mLogger;
};

template <typename TDrawCall>
void CVirusManager::draw(TDrawCall&& drawCall) {
	for (const std::unique_ptr<CVirus>& virus: mViruses) {
		const char graphic = virus->getGraphic();
		const CCoordinate& position = virus->getPosition();
		drawCall(position, graphic);
	}
}

}
