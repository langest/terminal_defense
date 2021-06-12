#include <logging/logger.h>

#include <filesystem>
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
	static CFileLogger fileLogger;
	return fileLogger;
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

CLogger::CLogger(const std::string& file) : mName(std::filesystem::path(file).filename()) {}

void CLogger::log(const std::string& message) {
	const std::string m = this->buildLogMessage('I', message);

	CFileLogger& fileLogger = CFileLogger::getInstance();
	fileLogger.log(m);
}

void CLogger::logError(const std::string& message) {
	const std::string m = this->buildLogMessage('E', message);

	CFileLogger& fileLogger = CFileLogger::getInstance();
	fileLogger.logError(m);
}

std::string CLogger::buildLogMessage(const char logLevel, const std::string& message) {
	const int bufferSize = 256;
	char m[bufferSize];
	snprintf(
		m,
		bufferSize,
		"[%s %s][%s][%c]: %s\n",
		__DATE__,
		__TIME__,
		mName.c_str(),
		logLevel,
		message.c_str()
	);
	return std::string(m);
}

}
