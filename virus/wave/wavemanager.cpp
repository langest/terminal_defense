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
		if (timer%SPAWNRATE != 0) return true;
		const WaveInfo& wi = wave_loader.get_current_wave();

		Virus* vir;
		int vir_id;
		virus_ptr vp;
		int n_spawns = std::min(wi.num_spawns(), size_r); //Avoid division by zero, and only spawn as many spawns that fit on screen
		std::size_t longest_virus_spawn(0); //The longest virus spawn so we know if all viruses have spawned.
		for (int i = 0; i < n_spawns; ++i) {
			longest_virus_spawn = std::max(wi[i].size(), longest_virus_spawn);
			try {
				vir_id = wi[i][timer/SPAWNRATE];
				if (vir_id == 0) continue; //Zero means no virus should spawn
				vir = virus_loader.get(vir_id);
			} catch (const std::invalid_argument &) {
				//TODO better error handling, at least logging errors to a file
				continue;
			}

			Coord start((size_r/(size_r+1-n_spawns)) * i, size_c - 1);
			Path p(start, size_r, size_c, towers);
			virus_ptr v(new Virus(*vir, p));
			vman.add_virus(std::move(v));
		}
		++timer;
		return timer%SPAWNRATE <= longest_virus_spawn;
	}

}
