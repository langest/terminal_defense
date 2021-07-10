#include <virus/Virus.h>

#include <Gui.h>

namespace termd {

CVirus::CVirus(
		int hp,
		int staminaIncrement,
		int reward,
		char graphic,
		const CCoordinate& startPosition,
		const std::set<CCoordinate>& endPositions,
		int numRows,
		int numCols,
		const std::map<CCoordinate, std::unique_ptr<ITower>>& towers
		) :
	mHp(hp),
	mStamina(0),
	mStaminaIncrement(staminaIncrement),
	mReward(reward),
	mDamage(1),
	mGraphic(graphic),
	mPath(startPosition, endPositions, numRows, numCols, towers),
	mLogger(__FILE__) {
		mLogger.log("Creating virus at position (%d, %d)", startPosition.getRow(), startPosition.getCol());
	}

void CVirus::update(){
	if(mHp <= 0) {
		mLogger.log("Virus out of hp");
		return;
	}
	mStamina = mPath.step(mStamina + mStaminaIncrement);
}

int CVirus::getReward() const {
	return mReward;
}

int CVirus::getDamage() const {
	return mDamage;
}

const CCoordinate& CVirus::getPosition() const {
	return mPath.getCurrentPosition();
}

char CVirus::getGraphic() const {
	return mGraphic;
}

bool CVirus::isAlive() const {
	return 0 <= mHp;
}

bool CVirus::isDestinationReached() const {
	return mPath.isDestinationReached();
}

void CVirus::takeDamage(int damage) {
	mHp -= damage;
}


}
