#pragma once

#include <vector>

#include <virus/Virus.h>
#include <tower/projectile/ProjectileBase.h>
#include <tower/projectile/Projectile.h>

namespace termd {

class DirectionProjectile : public Projectile {
	public:
		DirectionProjectile(const Direction_projectile_base&, Coordinate start, const std::vector<virus_ptr>&);
		DirectionProjectile(const DirectionProjectile&) = delete;
		virtual ~DirectionProjectile();
		DirectionProjectile& operator=(const DirectionProjectile &) = delete;

		virtual bool update();

	private:
		const int col_spd;
		const int row_spd;
		const Coordinate start_pos;
		const int range; //Euclidian distance that the projectile can travel

		CVirus& checkIfVirusHit() const;
		void move();

};

}
