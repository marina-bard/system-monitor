#ifndef PROCINFO
#define PROCINFO

#endif // PROCINFO

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
