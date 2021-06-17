#pragma once

#include <memory>
#include <set>
#include <vector>

#include <logging/Logger.h>
#include <virus/Virus.h>

namespace termd {

class CPlayer;

class CVirusManager {
	public:
		CVirusManager(CPlayer& player);

		bool update();
		void initInvasion(const std::set<CCoordinate>& startPositions, const std::set<CCoordinate>& endPositions, const std::map<CCoordinate, std::unique_ptr<ITower>>& towers);
		void finishInvasion();

		const std::vector<std::unique_ptr<CVirus>>& getViruses() const;

		void addVirus(std::unique_ptr<CVirus>&& virus);
		template <typename TDrawCall>
		void drawViruses(TDrawCall&& drawCall);

		bool hasNextWave() const;

	private:
		CPlayer& mPlayer;
		std::vector<std::unique_ptr<CVirus>> mViruses;
		CLogger mLogger;
};

template <typename TDrawCall>
void CVirusManager::drawViruses(TDrawCall&& drawCall) {
	for (const std::unique_ptr<CVirus>& virus: mViruses) {
		const char graphic = virus->getGraphic();
		const CCoordinate& position = virus->getPosition();
		drawCall(position, graphic);
	}
}

}
