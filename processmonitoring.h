#ifndef PROCESSESMONITORING_H
#define PROCESSESMONITORING_H

#include <QObject>
#include "processinfo.h"


class ProcessesMonitoring : public QObject
{
    Q_OBJECT
private:
   // ProcessInfo *proc;
   // QList<struct procInfo> *processes, *oldProcesses;
    struct procInfo info, oldInfo;
public:
    explicit ProcessesMonitoring(QObject *parent = 0);
    ~ProcessesMonitoring();

public slots:
    void monitor();

signals:
    void stopThread();
    void processesChanged(struct procInfo* temp, bool);
    void paramsChanged(struct procInfo* temp);
};

#endif // PROCESSESMONITORING_H
