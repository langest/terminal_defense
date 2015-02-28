#include "wave.hpp"

namespace termd {

	Wave::Wave(VirusManager& vm) :
		virus_loader(),
		vman(vm) {}

	void Wave::spawn(int wave_number, int size_r, int size_c, const std::vector<std::vector<bool> > & towers) {
		int id(0); //TODO read from wave definition instead
		// something like this ... for (int id : wavedefinition) ...
		Virus* vir;
		virus_ptr vp;
		for (int i = 0; i < 10; ++i) {
			try {
				vir = virus_loader.get(id);
			} catch (const std::invalid_argument &) {
				continue;
			}

			std::random_device rd;
			std::default_random_engine el(rd());
			std::uniform_int_distribution<int> uniform_dist(0, size_r-1);

			Coord start(uniform_dist(el), size_c - 1);
			Path p(start, size_r, size_c, towers);
			virus_ptr v(new Virus(*vir, p));
			vman.add_virus(std::move(v));
			id = (id + 1) % 2;
		}
	}

}
