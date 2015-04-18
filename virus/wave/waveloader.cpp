#include "waveloader.hpp"

Wave_loader::Wave_loader(std::string info_loction) : current_wave(0) {
	
}

Wave_loader::has_next() const {
	return current_wave < loaded_waves.size();
}

const Wave_info& Wave_loader::get_next_wave() const {
	return loaded_waves[current_wave++];
}
