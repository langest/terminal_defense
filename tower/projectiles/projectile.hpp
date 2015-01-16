#ifndef termd_projectile
#define termd_projectile

#ifndef termd_memory
#define termd_memory
#include <memory>
#endif

#include "../../gui.hpp"
#include "../../coord.hpp"
#include "../../virus/virus.hpp"

namespace termd {
	typedef std::unique_ptr<Projectile> proj_ptr;
		
	class Projectile {
		private:

		protected:
			char gfx;
			Coord pos;
		public:
			Projectile(char, Coord);
			virtual ~Projectile();

			virtual bool update() = 0;
			bool draw() const;

	};

}
#endif
