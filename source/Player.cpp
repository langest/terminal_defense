#include <Player.h>

#include <algorithm>

namespace termd {

CPlayer::CPlayer(int maxRam, int maxControlPoints)
    : mRam(maxRam)
    , mRamMax(maxRam)
    , mControlPoints(maxControlPoints)
    , mControlPointsMax(maxControlPoints) {}

bool CPlayer::isAlive() const {
    return 0 < mControlPoints;
}

int CPlayer::getRam() const {
    return mRam;
}
int CPlayer::getControlPoints() const {
    return mControlPoints;
}

void CPlayer::modifyControlPoints(int delta) {
    mControlPoints += delta;
    mControlPoints = std::max(mControlPoints, mControlPointsMax);
}

void CPlayer::modifyRam(int delta) {
    mRam += delta;
    mRam = std::max(mRam, mRamMax);
}

}
