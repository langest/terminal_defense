#include <virus/Virus.h>

#include <Gui.h>

namespace termd {

CVirus::CVirus(
		int hp,
		int staminaIncrement,
		int reward,
		char graphic,
		const CCoordinate& startPosition,
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
	mPath(startPosition, numRows, numCols, towers) {}

void CVirus::update(){
	if(mHp <= 0) {
		return;
	}
	mStamina = mPath.step(mStamina + mStaminaIncrement);
}

bool CVirus::draw() const {
	return GUI::draw_gfx(getPosition(), mGraphic);
}

int CVirus::getReward() const {
	return mReward;
}

int CVirus::getDamage() const {
	return mDamage;
}

const CCoordinate& CVirus::getPosition() const{
	return mPath.getCurrentPosition();
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
