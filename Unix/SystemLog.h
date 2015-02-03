
#pragma once

struct SystemLog
{
    explicit SystemLog(const char* applicationName);

    ~SystemLog();

    void operator<<(const char* message);
};
