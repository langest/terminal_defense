#include "projectilemanager.hpp"

namespace termd {
	
	ProjectileManager::~ProjectileManager() {
		purge_projectiles();
	}

	void ProjectileManager::purge_projectiles() {
		projectiles.clear();
	}

	void ProjectileManager::update() {
		for (auto i = projectiles.begin(); i != projectiles.end(); ) {
			if((*i)->update() == false) {
				//Projectile flags removal (probably a hit)
				i = projectiles.erase(i);
			} else {
				++i;
			}
		}
	}

	void ProjectileManager::draw_projectiles() const {
		auto it = projectiles.begin();
		auto end = projectiles.end();
		while (it != end) {
			(*it)->draw();
			++it;
		}
	}

	void ProjectileManager::add_projectile(proj_ptr&& p) {
		projectiles.push_back(std::move(p));
	}

	void ProjectileManager::end_of_wave() {
		purge_projectiles();
	}

	Projectile_base* ProjectileManager::get_projectile_base(int id) const {
		return projload.get_id(id);
	}


}
