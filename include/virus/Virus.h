#pragma once

#include <map>
#include <set>

#include <Coordinate.h>
#include <logging/Logger.h>
#include <virus/Path.h>

namespace termd {

class CVirus {
	public:
		CVirus(
			int hp,
			int staminaIncrement,
			int reward,
			char graphic,
			const CCoordinate& startPosition,
			const std::set<CCoordinate>& endPositions,
			int numRows,
			int numCols,
			const std::map<CCoordinate, std::unique_ptr<ITower>>& towers
		);

		void update();

		int getReward() const;
		int getDamage() const;
		const CCoordinate& getPosition() const;
		char getGraphic() const;
		bool isAlive() const;
		bool isDestinationReached() const;
		void takeDamage(int damage);

	private:
		int mHp;
		int mStamina;
		int mStaminaIncrement;
		int mReward;
		int mDamage;
		char mGraphic;
		CPath mPath;
		CLogger mLogger;
};

}
