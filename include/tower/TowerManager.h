#pragma once

#include <map>
#include <functional>
#include <memory>

#include <tower/Tower.h>
#include <Coordinate.h>

namespace termd {

class CTowerManager {
	public:
		typedef std::function<void(const CCoordinate& position, char graphic)> TDrawCall;

		CTowerManager();

		void updateAllTowers();
		void updateAllTowersEndOfWave();

		bool isTowerAt(const CCoordinate& coordinate) const;
		const std::map<CCoordinate, std::unique_ptr<ITower>>& getAllTowers() const;

		bool placeTower(const CCoordinate& position, std::unique_ptr<ITower>&& tower);
		void drawAllTowers() const;

	private:
		std::map<CCoordinate, std::unique_ptr<ITower>> mTowers;
		TDrawCall mDrawCall;
};

}
