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
	
	class RightProjectile : public Projectile {
		private:
			std::vector<Virus*>& viruses;

			Virus* hit();
			void move();

		protected:

		public:
			RightProjectile(Coord, std::vector<Virus*>&);
			RightProjectile(const RightProjectile&) = delete;
			virtual ~RightProjectile();
			RightProjectile& operator=(const RightProjectile &) = delete;

			virtual bool update();
	};
}
#endif //termd_HomingProjectile
