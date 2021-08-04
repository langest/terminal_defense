#pragma once

#include <map>
#include <memory>

#include <Coordinate.h>
#include <tower/projectile/Projectile.h>
#include <virus/Virus.h>

namespace termd {

enum class EDirection {
	Left,
	Right,
	Up,
	Down
};

template <EDirection TDirection>
class CDirectionProjectile : public IProjectile {
public:

    CDirectionProjectile(const CCoordinate& startPosition);

    const CCoordinate& getPosition() const;
    bool update(std::map<CCoordinate, std::vector<std::reference_wrapper<std::unique_ptr<CVirus>>>>& virusMap);
    char getGraphic() const;

private:
    bool collideWithVirus(std::map<CCoordinate, std::vector<std::reference_wrapper<std::unique_ptr<CVirus>>>>& virusMap);
	CCoordinate getDirection() const;

    CCoordinate mPosition;
    unsigned int mUpdateCounter;
    bool mHasCollided;
};

template <>
struct SProjectileTraits<CDirectionProjectile<EDirection::Right>> {
	static const int mDamage = 3;
	static const int mGraphic = '>';
};

template <EDirection TDirection>
CDirectionProjectile<TDirection>::CDirectionProjectile(const CCoordinate& startPosition)
    : mPosition(startPosition)
    , mUpdateCounter(0)
    , mHasCollided(false)
{
}

template <EDirection TDirection>
const CCoordinate& CDirectionProjectile<TDirection>::getPosition() const
{
    return mPosition;
}

template <EDirection TDirection>
bool CDirectionProjectile<TDirection>::update(std::map<CCoordinate, std::vector<std::reference_wrapper<std::unique_ptr<CVirus>>>>& virusMap)
{
    if (mHasCollided) {
        return false;
    }

    if (4 < mUpdateCounter) {
        if (this->collideWithVirus(virusMap)) {
            return false;
        }

        mPosition += this->getDirection();

        if (this->collideWithVirus(virusMap)) {
            return false;
        }
        mUpdateCounter = 0;
    }
    ++mUpdateCounter;
    return true;
}

template <EDirection TDirection>
char CDirectionProjectile<TDirection>::getGraphic() const
{
    return SProjectileTraits<CDirectionProjectile<TDirection>>::mGraphic;
}

template <EDirection TDirection>
bool CDirectionProjectile<TDirection>::collideWithVirus(std::map<CCoordinate, std::vector<std::reference_wrapper<std::unique_ptr<CVirus>>>>& virusMap)
{
    auto it = virusMap.find(mPosition);
    if (it == virusMap.end()) {
        return false;
    }
    const std::vector<std::reference_wrapper<std::unique_ptr<CVirus>>>& viruses = it->second;
    if (!viruses.empty()) {
        const std::unique_ptr<CVirus>& virus = viruses.front();
        virus->takeDamage(SProjectileTraits<CDirectionProjectile<TDirection>>::mDamage);
        mHasCollided = true;
        return true;
    }
    return false;
}

template <>
CCoordinate CDirectionProjectile<EDirection::Right>::getDirection() const {
	return CCoordinate(0, 1);
}

}
