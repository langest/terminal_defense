#pragma once

#include <string>

namespace termd {

// TODO add build flag to disable logging
class CLogger {
public:
    CLogger(const std::string& name);

    void log(const char* format, ...);
    void logError(const char* format, ...);

private:
    std::string buildLogMessage(const char logLevel, const char* message);

    const std::string mName;
};

}
