#ifndef termd_right_projectile
#define termd_right_projectile

#include <vector>

#include "../../definitions"
#include "../../virus/virus.hpp"
#include "projectilebase.hpp"
#include "projectile.hpp"

namespace termd {
	
	class DirectionProjectile : public Projectile {
		private:
			const int col_spd;
			const int row_spd;
			const Coord start_pos;
			const int range; //Euclidian distance that the projectile can travel

			const std::vector<virus_ptr>& viruses;

			Virus* hit() const;
			void move();

		protected:

		public:
			DirectionProjectile(const Direction_projectile_base&, Coord start, const std::vector<virus_ptr>&);
			DirectionProjectile(const DirectionProjectile&) = delete;
			virtual ~DirectionProjectile();
			DirectionProjectile& operator=(const DirectionProjectile &) = delete;

			virtual bool update();
	};
}
#endif //termd_HomingProjectile
