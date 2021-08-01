#pragma once

#include <map>
#include <memory>

#include <Coordinate.h>
#include <tower/projectile/Projectile.h>

namespace termd {

class CDirectionProjectile : public IProjectile {
	public:

		enum class EDirection {
			Left,
			Right,
			Up,
			Down
		};

		CDirectionProjectile(EDirection direction, const CCoordinate& startPosition);

		const CCoordinate& getPosition() const;
		bool update(std::map<CCoordinate, std::vector<std::reference_wrapper<std::unique_ptr<CVirus>>>>& virusMap);
		char getGraphic() const;

	private:
		bool collideWithVirus(std::map<CCoordinate, std::vector<std::reference_wrapper<std::unique_ptr<CVirus>>>>& virusMap);

		const char mGraphic;
		const int mDamage;
		CCoordinate mPosition;
		const CCoordinate mDirection;
		unsigned int mUpdateCounter;
		bool mHasCollided;
};

}
