#ifndef termd_right_projectile
#define termd_right_projectile

#ifndef termd_vector
#define termd_vector
#include <vector>
#endif

#include "../../definitions"
#include "projectile.hpp"
#include "../../virus/virus.hpp"

namespace termd {
	
	class DirectionProjectile : public Projectile {
		private:
			const int col_spd;
			const int row_spd;

			const std::vector<virus_ptr>& viruses;

			Virus* hit() const;
			void move();

		protected:

		public:
			DirectionProjectile(Coord, const std::vector<virus_ptr>&, int cs = 1, int rs = 0);
			DirectionProjectile(const DirectionProjectile&) = delete;
			virtual ~DirectionProjectile();
			DirectionProjectile& operator=(const DirectionProjectile &) = delete;

			virtual bool update();
	};
}
#endif //termd_HomingProjectile
