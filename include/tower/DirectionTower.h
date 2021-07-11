#pragma once

#include <tower/Tower.h>

namespace termd {

enum class EDirection {
	Up,
	Down,
	Left,
	Right
};

template <EDirection TDirection>
class CDirectionTower : public ITower {
	public:
		CDirectionTower();

		int getCost() const;
		int getSellValue() const;
		char getGraphic() const;

		bool update();
		void updateEndOfWave();

	private:
		const int mCost;
		const int mGraphic;
};

template<EDirection TDirection>
int CDirectionTower<TDirection>::getCost() const {
	return mCost;
}

template<EDirection TDirection>
int CDirectionTower<TDirection>::getSellValue() const {
	return mCost/2;
}

template<EDirection TDirection>
char CDirectionTower<TDirection>::getGraphic() const {
	return mGraphic;
}

template<EDirection TDirection>
bool CDirectionTower<TDirection>::update() {
	return true;
}

template<EDirection TDirection>
void CDirectionTower<TDirection>::updateEndOfWave() {
	return;
}

template <>
CDirectionTower<EDirection::Right>::CDirectionTower() : mCost(10), mGraphic('E') {
}

}
