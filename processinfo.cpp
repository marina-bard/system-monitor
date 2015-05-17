#include "processinfo.h"

ProcessInfo::ProcessInfo()
{

}

ProcessInfo::~ProcessInfo()
{

}

int ProcessInfo :: setMaxPid()
{
    int pid;
    FILE *pidMaxFile;
    pidMaxFile = fopen(PID_MAX, "r");
    fscanf(pidMaxFile, "%d", &pid);
    fclose(pidMaxFile);
    return pid;
}

void ProcessInfo :: setProcInfoList()
{
    if(!processes.empty())
        processes.clear();

    maxPid = setMaxPid();

    FILE *statFile;
    char *procDir;

    procDir = (char*)malloc(sizeof(char) * MAX_SIZE);

    for(int i = maxPid; i > 0; i--)
    {
        sprintf(procDir, "/proc/%d/stat", i);
        statFile = fopen(procDir, "r");
        if(statFile != NULL)
        {
            processes.push_back(setProcInfoStruct(statFile));
            fclose(statFile);
        }
        procDir[6] = '\0';
    }

   // delete procDir;
    return;
}

struct procInfo ProcessInfo :: setProcInfoStruct(FILE *stat)
{
    char status;
    struct procInfo info;
    size_t vTemp;
    size_t rssTemp;

    info.name = (char*)malloc(sizeof(char) * MAX_SIZE);

    fscanf(stat, "%d %s %c %d %*d %*d %*d %*u %*u %*lu %*lu %*lu %*lu %*lu %*lu %*ld %*ld %*ld %*ld %*ld %*ld %*llu %lu %ld",
           &(info.pid), info.name, &status, &(info.ppid), &vTemp, &rssTemp);

    info.name = changeNameFormat(info.name);

    info.memory = changeMemoryFormat(vTemp);
    info.rss = changeRSSFormat(rssTemp);

    info.cpuUsage = 0;
    // to do calculation of cpu usage

    switch(status)
    {
    case 'R':
        info.status = "Running";
        break;
    case 'S':
        info.status = "Sleeping";
        break;
    case 'D':
        info.status = "Waiting";
        break;
    case 'Z':
        info.status = "Zombie";
        break;
    case 'T':
        info.status = "Stopped";
        break;
    case 't':
        info.status = "Tracing stop";
        break;
    case 'X':
        info.status = "Dead";
        break;
    case 'x':
        info.status = "Dead";
        break;
    case 'W':
        info.status = "Waking";
        break;
    }

    return info;
}

QList <struct procInfo> ProcessInfo :: getProcInfoList()
{
    return processes;
}

char* ProcessInfo :: changeNameFormat(char* string)
{
    int i = 0;
    int length = strlen(string);
    for(int j = 1; j < length; i++, j++)
    {
        if(string[j] == ')')
            break;
        string[i] = string[j];
    }
    string[i] = '\0';
    return string;
}

double ProcessInfo :: changeMemoryFormat(size_t memSize)
{
    double temp;
    temp = memSize;
    return (temp / DIVIDER);
}

double ProcessInfo :: changeRSSFormat(size_t rss)
{
    double temp = rss;
    return (temp * PAGE / DIVIDER);
}

