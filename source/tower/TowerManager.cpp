#include <tower/TowerManager.h>

namespace termd {

CTowerManager::CTowerManager(const TDrawCall& drawCall) :
	mTowers(),
	mDrawCall(drawCall),
	mLogger(__FILE__) {}

void CTowerManager::updateTowers() {
	for (auto it = mTowers.begin(); it != mTowers.end(); ) {
		bool keep = it->second->update();

		if (!keep) { // If tower is flagging removal, remove it
			it = mTowers.erase(it);
		} else {
			++it;
		}
	}
}

void CTowerManager::updateTowersEndOfWave() {
	for (auto it = mTowers.begin(); it != mTowers.end(); ++it) {
		it->second->updateEndOfWave();
	}
}

bool CTowerManager::isTowerAt(const CCoordinate& coordinate) const {
	return mTowers.find(coordinate) != mTowers.end();
}

const std::map<CCoordinate, std::unique_ptr<ITower>>& CTowerManager::getTowers() const {
	return mTowers;
}

bool CTowerManager::placeTower(const CCoordinate& position, std::unique_ptr<ITower>&& tower) {
	if(this->isTowerAt(position)) {
		return false;
	}
	mTowers.insert(std::make_pair<CCoordinate, std::unique_ptr<ITower>>(CCoordinate(position), std::move(tower)));
	return true;
}

void CTowerManager::drawTowers() const {
	for (auto it = mTowers.begin(); it != mTowers.end(); ++it) {
		const char graphic = it->second->getGraphic();
		mDrawCall(it->first, graphic);
	}
}

}
