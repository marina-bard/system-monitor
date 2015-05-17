#include "processmonitoring.h"
#include <unistd.h>


ProcessesMonitoring::ProcessesMonitoring(QObject *parent) : QObject(parent)
{

}

ProcessesMonitoring::~ProcessesMonitoring()
{
   emit stopThread();
}

void ProcessesMonitoring::monitor()
{
    ProcessInfo *proc = new ProcessInfo;
    QList<struct procInfo> oldProcesses;

    proc->setProcInfoList();
    oldProcesses = proc->getProcInfoList();

    while(true)
    {
        ProcessInfo *proc = new ProcessInfo;
        QList<struct procInfo> processes;

        proc->setProcInfoList();
        processes = proc->getProcInfoList();

        QListIterator<struct procInfo> iter(processes), iterOld(oldProcesses);
        iter.toBack();
        iterOld.toBack();

        if(processes.size() > oldProcesses.size())
        {
            while(iter.hasPrevious())
            {
                bool noMatches = true;
                info = iter.previous();
                iterOld.toBack();
                while(iterOld.hasPrevious())
                {
                    oldInfo = iterOld.previous();
                    if(info.pid == oldInfo.pid)
                    {
                        noMatches = false;
                        struct procInfo temp;
                        temp = info;
                      /*  if(info.rss != oldInfo.rss)
                        {
                            emit paramsChanged(&temp);
                            break;
                        }
                        if(info.memory != oldInfo.memory)
                        {
                            emit paramsChanged(&temp);
                            break;
                        }
                        if(info.cpuUsage != oldInfo.cpuUsage)
                        {
                            emit paramsChanged(&temp);
                            break;
                        }
                        if(info.status == oldInfo.status)
                            continue;
                        else
                        {
                            emit paramsChanged(&temp);
                            break;
                        }*/
                        break;
                    }
                }

                if(noMatches)
                {
                    struct procInfo temp;
                    temp = info;
                    emit processesChanged(&temp, false);
                    sleep(1);
                }
            }
        }
        else if(processes.size() < oldProcesses.size())
        {
            while(iterOld.hasPrevious())
            {
                bool noMatches = true;
                info = iterOld.previous();
                iter.toBack();
                while(iter.hasPrevious())
                {
                    oldInfo = iter.previous();
                    if(info.pid == oldInfo.pid)
                    {
                        noMatches = false;
                        struct procInfo temp;
                        temp = info;
                      /*  if(info.rss != oldInfo.rss)
                        {
                            emit paramsChanged(&temp);
                            sleep(1);
                            break;
                        }
                        if(info.memory != oldInfo.memory)
                        {
                            emit paramsChanged(&temp);
                            sleep(1);
                            break;
                        }
                        if(info.cpuUsage != oldInfo.cpuUsage)
                        {
                            emit paramsChanged(&temp);
                            sleep(1);
                            break;
                        }
                        if(info.status == oldInfo.status)
                            continue;
                        else
                        {
                            emit paramsChanged(&temp);
                            sleep(1);
                            break;
                        }*/
                        break;
                    }
                }

                if(noMatches)
                {
                    struct procInfo temp;
                    temp = info;
                    emit processesChanged(&temp, true);
                    sleep(1);
                }
            }
        }
        oldProcesses = processes;
        sleep(1);
    }
}
