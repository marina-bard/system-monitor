#include "mainwindow.h"
//#include "processmonitoring.h"

#include <QApplication>
#include <QObject>
#include <QThread>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

//to do dynamic memory allocation

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow *w = new MainWindow;

    FileSystemsInfo *fileSystemInfo = new FileSystemsInfo;
    fileSystemInfo->setSystemInfoList();

    SystemInfo *sysInfo = new SystemInfo;
    sysInfo->setProcInfo();
    sysInfo->setRAMInfo();
    sysInfo->setOSTypeInfo();
    sysInfo->setOSVersionInfo();

    ProcessInfo *proc = new ProcessInfo;
    proc->setProcInfoList();
    QList<struct procInfo> list;
    list = proc->getProcInfoList();



    w->setProcInfoTab(&list);
    w->setFixedSize(WIDTH,HEIGTH);
    w->setFileSysTab(fileSystemInfo->getSystemInfoList());
    w->setSysInfoTab(sysInfo->getSystemInfoStruct());
  //  w->setProcInfoTab(proc->getProcInfoList());

  //  QList<struct procInfo> processes;
  //  ProcessInfo *info = new ProcessInfo;
    ProcessesMonitoring *procMonithoring = new ProcessesMonitoring();
    QThread *procThread = new QThread;

    procMonithoring->moveToThread(procThread);

    QObject::connect(procThread, SIGNAL(started()), procMonithoring, SLOT(monitor()));

    QObject::connect(procMonithoring, SIGNAL(paramsChanged(procInfo*)), w, SLOT(updateProcInfoParams(procInfo*)));
    QObject::connect(procMonithoring, SIGNAL(processesChanged(struct procInfo*, bool)), w, SLOT(updateProcInfoTab(struct procInfo*, bool))); //paramethers

    QObject::connect(procMonithoring, SIGNAL(stopThread()), procThread, SLOT(quit()));

    QObject::connect(procThread, SIGNAL(finished()), procThread, SLOT(deleteLater()));

    FileSystemsMonitoring *fsMonitoring = new FileSystemsMonitoring();
    QThread *sysThread = new QThread;

    fsMonitoring->moveToThread(sysThread);

    QObject::connect(sysThread, SIGNAL(started()), fsMonitoring, SLOT(monitor()));

    QObject::connect(fsMonitoring, SIGNAL(systemsChanged(fileSystem*, bool)), w, SLOT(updateFileSysTab(fileSystem*, bool)));

    QObject::connect(fsMonitoring, SIGNAL(stopThread()), sysThread, SLOT(quit()));

    QObject::connect(sysThread, SIGNAL(finished()), sysThread, SLOT(deleteLater()));
    w->show();
    procThread->start();
    sysThread->start();

    return a.exec();
}
