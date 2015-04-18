#ifndef termd_wave_info
#define termd_wave_info

#include <vector>

namespace termd {
	class WaveInfo {
		private:
			std::vector<std::vector<int> > wave;
		public:
			WaveInfo(int);
			WaveInfo(const WaveInfo&);
			WaveInfo& operator=(const WaveInfo&);

			int num_spawns() const;
			std::vector<int>& operator[](std::size_t);
			const std::vector<int>& operator[](std::size_t) const;
	};
}

#endif
