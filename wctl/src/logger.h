#include <stdio.h>

#include "currenttime.h"

#ifndef _INCL_LOGGER
#define _INCL_LOGGER

#define MAX_LOG_LENGTH          250

#define LOG_LEVEL_INFO          0x01
#define LOG_LEVEL_DEBUG         0x02
#define LOG_LEVEL_ERROR         0x04
#define LOG_LEVEL_FATAL         0x08

#define LOG_LEVEL_ALL           (LOG_LEVEL_INFO | LOG_LEVEL_DEBUG | LOG_LEVEL_ERROR | LOG_LEVEL_FATAL)

class Logger
{
public:
    static Logger & getInstance() {
        static Logger instance;
        return instance;
    }

private:
    Logger() {}

    FILE *          lfp;
    int             loggingLevel;

    CurrentTime     currentTime;

    int             logMessage(int logLevel, bool addCR, const char * fmt, va_list args);

public:
    ~Logger();

    void        initLogger(char * pszLogFileName, int logLevel);
    void        closeLogger();

    int         getLogLevel();
    void        setLogLevel(int logLevel);
    bool        isLogLevel(int logLevel);

    void        newline();
    int         logInfo(const char * fmt, ...);
    int         logDebug(const char * fmt, ...);
    int         logDebugNoCR(const char * fmt, ...);
    int         logError(const char * fmt, ...);
    int         logFatal(const char * fmt, ...);
};

#endif