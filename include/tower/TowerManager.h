#pragma once

#include <map>
#include <memory>

#include <Coordinate.h>
#include <logging/Logger.h>
#include <tower/Tower.h>

namespace termd {

class CTowerManager {
	public:
		CTowerManager();

		void updateTowers();
		void updateTowersEndOfWave();

		bool isTowerAt(const CCoordinate& coordinate) const;
		const std::map<CCoordinate, std::unique_ptr<ITower>>& getTowers() const;

		bool placeTower(const CCoordinate& position, std::unique_ptr<ITower>&& tower);
		template <typename TDrawCall>
		void drawTowers(TDrawCall&& drawCall);

	private:
		std::map<CCoordinate, std::unique_ptr<ITower>> mTowers;
		CLogger mLogger;
};

template <typename TDrawCall>
void CTowerManager::drawTowers(TDrawCall&& drawCall) {
	for (const auto& pair: mTowers) {
		const CCoordinate& position = pair.first;
		const char graphic = pair.second->getGraphic();
		drawCall(position, graphic);
	}
}

}
