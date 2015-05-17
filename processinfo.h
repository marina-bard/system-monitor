#ifndef PROCESSINFO_H
#define PROCESSINFO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <QString>
#include <QList>
#include "procinfo.h"

#define DIVIDER 1048576
#define PAGE    4096

#define PID_MAX "/proc/sys/kernel/pid_max"
#define PROC    "/proc/"
#define STAT    "/stat"
#define MAX_SIZE 256


class ProcessInfo
{
private:
    int maxPid;
    QList <struct procInfo> processes;
public:
    ProcessInfo();
    ~ProcessInfo();

    int setMaxPid();
    void setProcInfoList();
    struct procInfo setProcInfoStruct(FILE *stat);
    QList <struct procInfo> getProcInfoList();
    char* changeNameFormat(char* string);
    double changeMemoryFormat(size_t memSize);
    double changeRSSFormat(size_t rss);
};

#endif // PROCESSINFO_H
