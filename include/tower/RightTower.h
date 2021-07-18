#pragma once

#include <memory>
#include <vector>

#include <Coordinate.h>
#include <tower/Tower.h>
#include <logging/Logger.h>

namespace termd {

class CRightTower : public ITower {
	public:
		CRightTower(const CCoordinate& position);

		int getCost() const;
		int getSellValue() const;
		char getGraphic() const;

		bool update(std::function<void(std::unique_ptr<IProjectile>&& projectile)> spawnProjectile, const std::vector<std::unique_ptr<CVirus>>& viruses);
		void updateEndOfWave();

	private:
		CCoordinate mPosition;
		const int mCost;
		const int mGraphic;
		int mUpdateCounter;

		CLogger mLogger;
};

}
