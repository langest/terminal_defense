#include <virus/Virus.h>

#include <Gui.h>

#include <virus/VirusManager.h>

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
    const std::map<CCoordinate, std::unique_ptr<ITower>>& towers)
    : mIsActive(true)
    , mHp(hp)
    , mStamina(0)
    , mStaminaIncrement(staminaIncrement)
    , mReward(reward)
    , mDamage(1)
    , mGraphic(graphic)
    , mPath(startPosition, endPositions, numRows, numCols, towers)
    , mLogger(__FILE__) {
    mLogger.log("Creating virus at position (%d, %d)", startPosition.getRow(), startPosition.getCol());
}

const CCoordinate& CVirus::getPosition() const {
    return mPath.getCurrentPosition();
}

char CVirus::getGraphic() const {
    return mGraphic;
}

bool CVirus::isActive() const {
    return 0 < mHp && mIsActive;
}

bool CVirus::isDestinationReached() const {
    return mPath.isDestinationReached();
}

CVirusHandle::CVirusHandle(CVirus::TVirusId virusId, CVirusManager& virusManager)
    : mVirusId(virusId)
    , mVirusManager(virusManager) {
    mVirusManager.createHandle(virusId);
}

CVirusHandle::~CVirusHandle() {
    mVirusManager.releaseHandle(mVirusId);
}

CVirus& CVirusHandle::operator*() {
    return mVirusManager.get(mVirusId);
}

const CVirus& CVirusHandle::operator*() const {
    return mVirusManager.get(mVirusId);
}

CVirus* CVirusHandle::operator->() {
    return &mVirusManager.get(mVirusId);
}

const CVirus* CVirusHandle::operator->() const {
    return &mVirusManager.get(mVirusId);
}

}
