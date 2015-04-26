#ifndef termd_projectile
#define termd_projectile

#include <memory>

#include "projectilebase.hpp"
#include "../../gui.hpp"
#include "../../coord.hpp"
#include "../../virus/virus.hpp"

namespace termd {
		
	class Projectile {
		private:

		protected:
			char gfx;
			int damage;
			Coord pos;
		public:
			Projectile(const Projectile_base &, Coord);
			virtual ~Projectile();

			virtual bool update() = 0;
			bool draw() const;

	};

	typedef std::unique_ptr<Projectile> proj_ptr;

}
#endif
