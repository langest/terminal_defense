#include "wavemanager.hpp"

namespace termd {

	WaveManager::WaveManager(int sr, int sc, const std::vector<std::vector<bool> > & t, std::string wave_info_file, VirusManager& vm) :
		wave_loader(wave_info_file),
		virus_loader(),
		vman(vm),
		size_r(sr),
		size_c(sc),
		towers(t),
		timer(0) {}

	bool WaveManager::spawn() {
		timer = 0;
		return wave_loader.next_wave();
	}

	bool WaveManager::update() {
		WaveInfo& wi = wave_loader.get_current_wave();
		if (!wi.has_spawns_left()) return false;
		++timer;
		if (timer%SPAWNRATE != 0) return true;

		Virus* vir;
		int vir_id;
		virus_ptr vp;
		int n_spawns = std::min(wi.num_spawns(), size_r); //Avoid division by zero, and only spawn as many spawns that fit on screen
		for (int i = 0; i < n_spawns; ++i) {
			try {
				vir_id = wi.get_next_in(i);
				wi.pop(i);
				if (vir_id == 0) continue; //Zero means no virus should spawn
				vir = virus_loader.get(vir_id);
			} catch (const std::invalid_argument &) {
				//TODO better error handling, at least logging errors to a file
				continue;
			}

			Coord start((size_r/(1+n_spawns)) * (i+1), size_c - 1);
			Path p(start, size_r, size_c, towers);
			virus_ptr v(new Virus(*vir, p));
			vman.add_virus(std::move(v));
		}
		return wi.has_spawns_left();
	}

	void WaveManager::set_size(int r, int c) {
		size_r = r;
		size_c = c;
	}

}
