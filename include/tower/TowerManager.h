#pragma once

#include <map>
#include <functional>
#include <memory>

#include <Coordinate.h>
#include <logging/Logger.h>
#include <tower/Tower.h>

namespace termd {

class CTowerManager {
	public:
		typedef std::function<void(const CCoordinate& position, char graphic)> TDrawCall;

		CTowerManager(const TDrawCall& drawCall);

		void updateTowers();
		void updateTowersEndOfWave();

		bool isTowerAt(const CCoordinate& coordinate) const;
		const std::map<CCoordinate, std::unique_ptr<ITower>>& getTowers() const;

		bool placeTower(const CCoordinate& position, std::unique_ptr<ITower>&& tower);
		void drawTowers() const;

	private:
		std::map<CCoordinate, std::unique_ptr<ITower>> mTowers;
		TDrawCall mDrawCall;
		CLogger mLogger;
};

}
