#ifndef termd_projectile_manager
#define termd_projectile_manager

#include "projectile.hpp"
#include "projectileloader.hpp"

namespace termd {
	
	class ProjectileManager {
		private:
			Projectile_loader projload;
			std::vector<proj_ptr> projectiles;

			void purge_projectiles();
		public:
			~ProjectileManager();

			void update();
			void draw_projectiles() const;
			void add_projectile(proj_ptr&&);
			void end_of_wave();
			Projectile_base* get_projectile_base(int id) const;
	};

}
#endif
