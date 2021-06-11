#include <logging/logger.h>

#include <fstream>

namespace {

class CFileLogger {
	private:
		CFileLogger();
		~CFileLogger();
	public:
		static CFileLogger& getInstance();

		CFileLogger(const CFileLogger&) = delete;
		CFileLogger& operator=(const CFileLogger&) = delete;

		void log(const std::string& message);
		void logError(const std::string& message);
	private:
		std::ofstream mInfoLogStream;
		std::ofstream mErrorLogStream;
};

CFileLogger::CFileLogger() {
	mInfoLogStream.open("/tmp/termd_info.log");
	mErrorLogStream.open("/tmp/termd_error.log");
}

CFileLogger::~CFileLogger() {
	mInfoLogStream.close();
	mErrorLogStream.close();
}

CFileLogger& CFileLogger::getInstance() {
	static CFileLogger log;
	return log;
}

void CFileLogger::log(const std::string& message) {
	mInfoLogStream << message;
	mInfoLogStream.flush();
}

void CFileLogger::logError(const std::string& message) {
	mErrorLogStream << message;
	mErrorLogStream.flush();
}

}

namespace termd {

CLogger::CLogger(const std::string& name) : mName(name) {}

void CLogger::log(const std::string& message) {
	// TODO prettier code and log timestamp
	::CFileLogger& fileLogger = ::CFileLogger::getInstance();
	fileLogger.log("[");
	fileLogger.log(__DATE__);
	fileLogger.log(__TIME__);
	fileLogger.log("] ");
	fileLogger.log("[");
	fileLogger.log(mName);
	fileLogger.log("] [I]: ");
	fileLogger.log(message);
}

void CLogger::logError(const std::string& message) {
	// TODO prettier code and log timestamp
	::CFileLogger& fileLogger = ::CFileLogger::getInstance();
	fileLogger.logError("[");
	fileLogger.logError(__DATE__);
	fileLogger.logError(__TIME__);
	fileLogger.logError("] ");
	fileLogger.logError("[");
	fileLogger.logError(mName);
	fileLogger.logError("] [I]: ");
	fileLogger.logError(message);
}

}
