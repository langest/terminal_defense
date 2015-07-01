#include "projectilemanager.hpp"

namespace termd {

	ProjectileManager::ProjectileManager() :
		num_rows(0),
		num_cols(0) {}
	
	ProjectileManager::~ProjectileManager() {
		purge_projectiles();
	}

	void ProjectileManager::purge_projectiles() {
		projectiles.clear();
	}

	void ProjectileManager::set_size(int n_rows, int n_cols) {
		num_rows = n_rows;
		num_cols = n_cols;
	}
			
	void ProjectileManager::update() {
		Coord p;
		for (auto i = projectiles.begin(); i != projectiles.end(); ) {
			p = (*i)->get_pos();
			if((*i)->update() == false ||
				p.get_row() >= num_rows-1 ||
				p.get_col() >= num_cols-1 ||
				p.get_row() < 0 ||
				p.get_col() < 0) {
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
