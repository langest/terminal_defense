#ifndef termd_projectile_manager
#define termd_projectile_manager

#include "projectile.hpp"

class ProjectileManager {
	private:
		std::vector<Projectile*> projectiles;

		void purge_projectiles();
	public:
		~ProjectileManager();

		void update();
		void draw_projectiles(GUI &);
		void add_projectile(Projectile*);
};

#endif
