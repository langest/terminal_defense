#pragma once

#include <vector>
#include <queue>
#include <algorithm>

namespace termd {

class WaveInfo {
	private:
		std::vector<std::queue<int> > wave;
	public:
		WaveInfo(int);
		WaveInfo(const WaveInfo&);
		WaveInfo& operator=(const WaveInfo&);

		bool has_spawns_left() const;
		int num_spawns() const;
		void pop(std::size_t);
		int get_next_in(std::size_t) const;
		void push_to(std::size_t, int);
};

}
