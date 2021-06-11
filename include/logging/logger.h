#pragma once

#include <string>

namespace termd {

// TODO add build flag to disable logging
class CLogger {
	public:
		CLogger(const std::string& name);

		void log(const std::string& message);
		void logError(const std::string& message);
	private:
		std::string mName;
};

}
