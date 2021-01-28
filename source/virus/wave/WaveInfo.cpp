#include <virus/wave/WaveInfo.h>

namespace termd {

WaveInfo::WaveInfo(int num_spawns) : wave(num_spawns, std::queue<int>()) {
}

WaveInfo::WaveInfo(const WaveInfo& src) : wave(src.wave) {
}

WaveInfo& WaveInfo::operator=(const WaveInfo& src) {
	wave = src.wave;
	return *this;
}

bool WaveInfo::has_spawns_left() const {
	for (std::queue<int> q : wave) {
		if (q.size() > 0) return true;
	}
	return false;
}

int WaveInfo::num_spawns() const {
	return wave.size();
}

void WaveInfo::pop(std::size_t ix) {
	if (wave[ix].size() > 0)
		wave[ix].pop();
}

int WaveInfo::get_next_in(std::size_t ix) const {
	if (wave.size() <= 0) return 0;
	return wave[ix].front();
}

void WaveInfo::push_to(std::size_t ix, int id) {
	wave[ix].push(id);
}
}
