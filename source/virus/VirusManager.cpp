#include <virus/VirusManager.h>

#include <algorithm>

#include <Player.h>

namespace termd {

CVirusManager::CVirusManager(CPlayer& player) :
	mPlayer(player),
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

void CVirusManager::initInvasion(const std::set<CCoordinate>& startPositions, const std::set<CCoordinate>& endPositions, const std::map<CCoordinate, std::unique_ptr<ITower>>& towers) {
	const int r = std::rand();
	const int n = r % startPositions.size();
	auto it = std::begin(startPositions);
	std::advance(it,n);
	const CCoordinate& startPosition = *it;
	mViruses.emplace_back(std::make_unique<CVirus>(10, 40, 1, 'v', startPosition, endPositions, 10,10, towers));
}

void CVirusManager::finishInvasion() {
	mViruses.clear();
}

const std::vector<std::unique_ptr<CVirus>>& CVirusManager::getViruses() const {
	return mViruses;
}

void CVirusManager::addVirus(std::unique_ptr<CVirus>&& virus) {
	mViruses.emplace_back(std::move(virus));
}

bool CVirusManager::hasNextWave() const {
	return false;
}

}
