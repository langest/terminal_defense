#include <tower/RightTower.h>

#include <tower/projectile/DirectionProjectile.h>

namespace termd {

CRightTower::CRightTower(const CCoordinate& position) :
		mPosition(position),
		mCost(10),
		mGraphic('E'),
		mUpdateCounter(0),
		mLogger(__FILE__) {
	mLogger.log("Creating Right Tower");
}

int CRightTower::getCost() const {
	return mCost;
}

int CRightTower::getSellValue() const {
	return this->getCost() / 2;
}

char CRightTower::getGraphic() const {
	return mGraphic;
}

bool CRightTower::update(
				std::function<void(std::unique_ptr<IProjectile>&& projectile)> spawnProjectile,
				const std::set<std::unique_ptr<CVirus>>& /* viruses */,
				const std::map<CCoordinate, std::set<std::reference_wrapper<std::unique_ptr<CVirus>>>>& /* virusMap */
) {
	if (0 == mUpdateCounter % 40) {
		mLogger.log("Spawning direction projectile");
		spawnProjectile(std::make_unique<CDirectionProjectile>(CDirectionProjectile::EDirection::Right, mPosition));
	}
	++mUpdateCounter;
	return true;
}

void CRightTower::updateEndOfWave() {}

}
