#ifndef termd_wave_info
#define termd_wave_info

#include <vector>

namespace termd {
	class Wave_info {
		private:
			std::vector<std::vector<int> > wave;
		public:
			Wave_info(int);

			int num_spawns() const;
			std::vector<int>& operator[](int);
	};
}

#endif
