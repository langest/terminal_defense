#pragma once

#include <map>

#include <Coordinate.h>
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
			int numRows,
			int numCols,
			const std::map<CCoordinate, std::unique_ptr<ITower>>& towers
		);

		void update();
		bool draw() const;

		int getReward() const;
		int getDamage() const;
		const CCoordinate& getPosition() const;
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
};

class CVirusFactory {
	public:
		CVirus static createVirus(int hp, int stamina, int reward, const CCoordinate& startPosition, const std::map<CCoordinate, std::unique_ptr<ITower>> towers);
};

}
