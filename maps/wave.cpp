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
		for (int i = 0; i < 5; ++i) {
			try {
				vir = virus_loader.get(id);
			} catch (const std::invalid_argument &) {
				continue;
			}
			Path p(Coord(size_r - (i*5%3) -1, size_c - 3 * i -1), size_r, size_c, towers);
			virus_ptr v(new Virus(*vir, p));
			vman.add_virus(std::move(v));
			id = (id + 1) % 2;
		}
	}

}
