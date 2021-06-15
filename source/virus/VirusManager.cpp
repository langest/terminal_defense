#include <virus/VirusManager.h>

#include <algorithm>

#include <Player.h>

namespace termd {

CVirusManager::CVirusManager(CPlayer& p) :
	mPlayer(p),
	mInts(),
	mViruses(),
	mLogger(__FILE__) {}

bool CVirusManager::update() {
	mLogger.log("Update");
	for (std::unique_ptr<CVirus>& virus : mViruses) {
		virus->update();

		if (virus->isDestinationReached()) {
			mPlayer.modifyControlPoints(-virus->getDamage());
			continue;
		}

		if (!virus->isAlive()) {
			mPlayer.modifyRam(virus->getReward());
		}
	}

	const auto isShouldBeRemoved = [](const std::unique_ptr<CVirus>& virus) {
		return !virus->isAlive() || virus->isDestinationReached();
	};

	mViruses.erase(
			std::remove_if(mViruses.begin(), mViruses.end(), isShouldBeRemoved),
			mViruses.end());

	return !mViruses.empty();
}

void CVirusManager::initInvasion(const std::map<CCoordinate, std::unique_ptr<ITower>>& towers) {
	mViruses.emplace_back(std::make_unique<CVirus>(10, 40, 1, 'v', CCoordinate(5, 5), 10,10, towers));
}

void CVirusManager::finishInvasion() {
	mViruses.clear();
}

const std::vector<std::unique_ptr<int>>& CVirusManager::getViruses() const {
	return mInts;
	//return mViruses;
}

void CVirusManager::addVirus(std::unique_ptr<CVirus>&& virus) {
	mViruses.emplace_back(std::move(virus));
}

void CVirusManager::drawViruses() const {
	for (auto i = mViruses.begin(); i != mViruses.end(); ++i) {
		(*i)->draw();
	}
}

bool CVirusManager::hasNextWave() const {
	return false;
}

}
