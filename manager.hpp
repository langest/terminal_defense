#ifndef termd_manager
#define termd_manager

#include "gui.hpp"

class Manager {
	public:
		virtual ~Manager();

		virtual bool update() = 0;
		virtual bool draw(GUI &) = 0;
};

#endif
