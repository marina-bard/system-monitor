#ifndef FYLESYSTEMSTRUCT
#define FYLESYSTEMSTRUCT

#endif // FYLESYSTEMSTRUCT
#include <sys/types.h>

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
    size_t memory;

    QString status;
    char* name;
};
