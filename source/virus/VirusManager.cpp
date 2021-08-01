#include <virus/VirusManager.h>

#include <algorithm>

#include <Player.h>

namespace termd {

CVirusManager::CVirusManager(CPlayer& player, int numRows, int numCols) :
	mPlayer(player),
	mActiveViruses(),
	mDisabledViruses(),
	mWaveManager(numRows, numCols),
	mLogger(__FILE__) {}

bool CVirusManager::update(
		const std::set<CCoordinate>& startPositions,
		const std::set<CCoordinate>& endPositions,
		const std::map<CCoordinate, std::unique_ptr<ITower>>& towers) {
	mLogger.log("Update");

	for (std::unique_ptr<CVirus>& virus : mActiveViruses) {
		virus->update();

		if (virus->isDestinationReached()) {
			mPlayer.modifyControlPoints(-virus->getDamage());
			continue;
		}

		if (!virus->isAlive()) {
			mPlayer.modifyRam(virus->getReward());
		}
	}

	for (auto it = mActiveViruses.begin(); it != mActiveViruses.end(); ) {
		if (!(*it)->isAlive() || (*it)->isDestinationReached()) {
			mDisabledViruses.emplace_back(std::move(*it));
			it = mActiveViruses.erase(it);
		} else {
			++it;
		}
	}

	const bool moreVirusesIncoming = mWaveManager.update(
			std::bind(&CVirusManager::addVirus, this, std::placeholders::_1),
			startPositions,
			endPositions,
			towers
		);

	return !mActiveViruses.empty() || moreVirusesIncoming;
}

void CVirusManager::initInvasion() {
	mWaveManager.initWave();
}

void CVirusManager::finishInvasion() {
	mActiveViruses.clear();
	mDisabledViruses.clear();
}

const std::vector<std::unique_ptr<CVirus>>& CVirusManager::getActiveViruses() const {
	return mActiveViruses;
}

std::map<CCoordinate, std::vector<std::reference_wrapper<std::unique_ptr<CVirus>>>> CVirusManager::getCoordinateVirusMap() {
	std::map<CCoordinate, std::vector<std::reference_wrapper<std::unique_ptr<CVirus>>>> map;

	for (std::unique_ptr<CVirus>& v : mActiveViruses) {
		map[v->getPosition()].emplace_back(std::reference_wrapper(v));
	}

	return map;
}

bool CVirusManager::hasNextWave() const {
	return false;
}

void CVirusManager::addVirus(std::unique_ptr<CVirus>&& virus) {
	mActiveViruses.emplace_back(std::move(virus));
}


}
