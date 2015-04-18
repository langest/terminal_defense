#include "waveinfo.hpp"

namespace termd {

	WaveInfo::WaveInfo(int num_spawns) : wave(num_spawns, std::vector<int>()) {
	}

	WaveInfo::WaveInfo(const WaveInfo& src) : wave(src.wave) {
	}

	WaveInfo& WaveInfo::operator=(const WaveInfo& src) {
		wave = src.wave;
		return *this;
	}

	int WaveInfo::num_spawns() const {
		return wave.size();
	}

	std::vector<int>& WaveInfo::operator[](std::size_t ix) {
		return wave[ix];
	}

	const std::vector<int>& WaveInfo::operator[](std::size_t ix) const {
		return wave[ix];
	}

}
