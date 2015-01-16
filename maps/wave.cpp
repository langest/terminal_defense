#include "wave.hpp"

namespace termd {

	Wave::Wave(VirusManager& vm) :
		virus_loader(),
		vman(vm) {}

	void Wave::spawn(int wave_number) {
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
			virus_ptr v(new Virus(*vir));
			v->move_to(Coord(1+ i, 50 + ((7*i) % 5)));
			vman.add_virus(std::move(v));
			id = (id + 1) % 2;
		}
	}

}
