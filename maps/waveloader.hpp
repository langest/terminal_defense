#ifndef termd_wave_loader
#define termd_wave_loader

#include <vector>

namespace termd {
	class Wave_loader {
		private:
			std::vector<Wave_info> loaded_waves;
		public:
			Wave_loader();

			Wave_info* get_wave(int) const;
	};
}

#endif
