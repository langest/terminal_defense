#pragma once

#include <algorithm>
#include <map>
#include <set>

#include <Coordinate.h>
#include <logging/Logger.h>
#include <virus/Path.h>

namespace termd {

class CVirusManager;

class CVirus {
public:
    typedef int TVirusId;

    CVirus(
        int hp,
        int staminaIncrement,
        int reward,
        char graphic,
        const CCoordinate& startPosition,
        const std::set<CCoordinate>& endPositions,
        int numRows,
        int numCols,
        const std::map<CCoordinate, std::unique_ptr<ITower>>& towers);

    template <typename TDamagePlayerCall>
    bool update(TDamagePlayerCall&& damagePlayerCall);
    template <typename TRewardPlayerCall>
    void takeDamage(int damage, TRewardPlayerCall&& rewardPlayerCall);

    const CCoordinate& getPosition() const;
    char getGraphic() const;
    bool isActive() const;

private:
    bool isDestinationReached() const;

    bool mIsActive;
    int mHp;
    int mStamina;
    int mStaminaIncrement;
    int mReward;
    int mDamage;
    char mGraphic;
    CPath mPath;
    CLogger mLogger;
};

template <typename TDamagePlayerCall>
bool CVirus::update(TDamagePlayerCall&& damagePlayerCall)
{
    mLogger.log("Updating virus");
    if (!this->isActive()) {
        return false;
    }
    mStamina = mPath.step(mStamina + mStaminaIncrement);
    if (isDestinationReached()) {
        damagePlayerCall(mDamage);
        mIsActive = false;
        return false;
    }
    return true;
}

template <typename TRewardPlayerCall>
void CVirus::takeDamage(int damage, TRewardPlayerCall&& rewardPlayerCall)
{
    mLogger.log("Take damage start, mHp: %d", mHp);
    if (mHp <= 0) {
        return;
    }
    mHp = std::max(mHp - damage, 0);
    mLogger.log("Take damage after, mHp: %d", mHp);

    if (mHp <= 0) {
        rewardPlayerCall(mReward);
    }
}

class CVirusHandle {
public:
    CVirusHandle(CVirus::TVirusId virusId, CVirusManager& virusManager);
    ~CVirusHandle();

    CVirus& operator*();
    const CVirus& operator*() const;
    CVirus* operator->();
    const CVirus* operator->() const;

private:
    const CVirus::TVirusId mVirusId;
    CVirusManager& mVirusManager;
};

}
