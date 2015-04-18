#include "waveinfo.hpp"

namespace termd {

	Wave_info::Wave_info(int num_spawns) : wave(num_spawns, std::vector<int>()) {
	}

	int Wave_info::num_spawns() const {
		return wave.size();
	}

	std::vector<int>& Wave_info::operator[](int ix) {
		return wave[ix];
	}

}
