#ifndef FYLESYSTEMSTRUCT
#define FYLESYSTEMSTRUCT

#endif // FYLESYSTEMSTRUCT
#include <sys/types.h>

#define DIVIDER 1048576
#define PAGE    4096

struct fileSystem
{
    QString fsname;
    QString dir;
    QString type;
};

struct systemInfo
{
    QString proc;
    float RAM;
    QString sysType;
    QString OSType;
    QString OSVersion;
};

struct procInfo
{
    // to include execution time
    pid_t pid;
    pid_t ppid;

    int cpuUsage;
    double memory;
    double rss;

    QString status;
    char* name;
};
