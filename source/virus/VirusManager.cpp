#include <virus/VirusManager.h>

#include <algorithm>

#include <Player.h>

namespace termd {

CVirusManager::CVirusManager(CPlayer& p) : mPlayer(p) {}

bool CVirusManager::updateAllViruses() {
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
		return virus->isAlive() || virus->isDestinationReached();
	};

	mViruses.erase(
			std::remove_if(mViruses.begin(), mViruses.end(), isShouldBeRemoved),
			mViruses.end());

	return !mViruses.empty();
}

void CVirusManager::updateAllVirusesEndOfWave() {
	mViruses.clear();
}

const std::vector<std::unique_ptr<CVirus>>& CVirusManager::getAllViruses() const {
	return mViruses;
}

void CVirusManager::addVirus(std::unique_ptr<CVirus>&& virus) {
	mViruses.emplace_back(std::move(virus));
}

void CVirusManager::drawAllViruses() const {
	for (auto i = mViruses.begin(); i != mViruses.end(); ++i) {
		const bool success = (*i)->draw();
		if(!success) {
			//TODO debugging
		}
	}
}

bool CVirusManager::hasNextWave() const {
	return false;
}

}
