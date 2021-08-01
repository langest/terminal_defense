#pragma once

#include <functional>
#include <memory>
#include <vector>

#include <tower/Tower.h>

namespace termd {

class Coordinate;

class CWall : public ITower {
	public:
		CWall();

		// ITower
		int getCost() const;
		int getSellValue() const;
		char getGraphic() const;
		bool update(
				std::function<void(std::unique_ptr<IProjectile>&& projectile)> spawnProjectile,
				const std::vector<std::unique_ptr<CVirus>>& viruses,
				const std::map<CCoordinate, std::vector<std::reference_wrapper<std::unique_ptr<CVirus>>>>& virusMap
);
		void updateEndOfWave();

	private:
		const int mCost;
		const char mGraphic;
};

}
