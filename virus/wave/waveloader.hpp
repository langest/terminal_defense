#ifndef termd_wave_loader
#define termd_wave_loader

#include <vector>
#include <string>

namespace termd {
	class Wave_loader {
		private:
			int current_wave;
			std::vector<Wave_info> loaded_waves;
		public:
			Wave_loader(std::string, info_location);

			bool has_next() const;
			const Wave_info& get_next_wave() const;
	};
}

#endif
