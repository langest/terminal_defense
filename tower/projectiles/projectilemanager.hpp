#ifndef termd_projectile_manager
#define termd_projectile_manager

#include "projectile.hpp"

class ProjectileManager {
	private:
		std::vector<Projectile*> projectiles;

		void purge_projectiles();
	public:
		~ProjectileManager();

		bool update();
		bool draw(GUI &);
		void add_rojectile(Projectile*);
};

#endif
