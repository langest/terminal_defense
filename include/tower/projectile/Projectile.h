#pragma once

#include <memory>

#include <Coordinate>

namespace termd {

class CProjectile {
	public:
		Projectile(const Coordinate& coordinate);
		virtual ~Projectile();

		const CCoordinate& getPosition() const;
		bool update();
		bool draw() const;

	private:
		char graphic;
		int damage;
		CCoordinate pos;
};

}
