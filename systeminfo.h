#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <stdio.h>
#include <QString>
#include "systeminfostruct.h"

#define CPU_INFO "/proc/cpuinfo"
#define MEM_INFO "/proc/meminfo"
#define OS_TYPE "/proc/sys/kernel/ostype"
#define OS_RELEASE "/proc/sys/kernel/osrelease"
#define MAX_SIZE 256
#define MODEL_NAME  "model name"
#define DIVIDER 1048576


class SystemInfo
{
private:
    FILE *file;
    struct systemInfo info;
public:
    SystemInfo();
    ~SystemInfo();

    void setStructInfo();
    void setUserInfo();
    void setProcInfo();
    void setRAMInfo();
    void setOSTypeInfo();
    void setOSVersionInfo();
    struct systemInfo getSystemInfoStruct();
};

#endif // SYSTEMINFO_H
