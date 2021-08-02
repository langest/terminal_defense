#include <tower/projectile/DirectionProjectile.h>

#include <virus/Virus.h>

namespace termd {

CCoordinate parseDirection(CDirectionProjectile::EDirection direction)
{
    switch (direction) {
    case CDirectionProjectile::EDirection::Left: {
        return CCoordinate(0, -1);
    }
    case CDirectionProjectile::EDirection::Right: {
        return CCoordinate(0, 1);
    }
    case CDirectionProjectile::EDirection::Up: {
        return CCoordinate(-1, 0);
    }
    case CDirectionProjectile::EDirection::Down: {
        return CCoordinate(1, 0);
    }
    }
    return CCoordinate();
}

CDirectionProjectile::CDirectionProjectile(EDirection direction, const CCoordinate& startPosition)
    : mGraphic('>')
    , mDamage(1)
    , mPosition(startPosition)
    , mDirection(parseDirection(direction))
    , mUpdateCounter(0)
    , mHasCollided(false)
{
}
const CCoordinate& CDirectionProjectile::getPosition() const
{
    return mPosition;
}

bool CDirectionProjectile::update(std::map<CCoordinate, std::vector<std::reference_wrapper<std::unique_ptr<CVirus>>>>& virusMap)
{
    if (mHasCollided) {
        return false;
    }

    if (7 < mUpdateCounter) {
        if (this->collideWithVirus(virusMap)) {
            return false;
        }

        mPosition += mDirection;

        if (this->collideWithVirus(virusMap)) {
            return false;
        }
        mUpdateCounter = 0;
    }
    ++mUpdateCounter;
    return true;
}

char CDirectionProjectile::getGraphic() const
{
    return mGraphic;
}

bool CDirectionProjectile::collideWithVirus(std::map<CCoordinate, std::vector<std::reference_wrapper<std::unique_ptr<CVirus>>>>& virusMap)
{
    auto it = virusMap.find(mPosition);
    if (it == virusMap.end()) {
        return false;
    }
    const std::vector<std::reference_wrapper<std::unique_ptr<CVirus>>>& viruses = it->second;
    if (!viruses.empty()) {
        const std::unique_ptr<CVirus>& virus = viruses.front();
        virus->takeDamage(mDamage);
        mHasCollided = true;
        return true;
    }
    return false;
}

}
