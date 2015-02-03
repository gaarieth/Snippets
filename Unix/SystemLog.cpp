
#include "SystemLog.h"
#include <syslog.h>

SystemLog::SystemLog(const char* applicationName)
{
    openlog(applicationName, LOG_PID, LOG_USER);
    operator<<("Started");
}

SystemLog::~SystemLog()
{
    operator<<("Stopped");
    closelog();
}

void SystemLog::operator<<(const char* msg)
{
    syslog(LOG_NOTICE, "%s", msg);
}
