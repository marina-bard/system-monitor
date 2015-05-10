#include "mainwindow.h"
#include "filesystemsinfo.h"
#include "systeminfo.h"
#include "processinfo.h"
//#include "structures.h"
#include <QApplication>

#define WIDTH   685
#define HEIGTH  510

//to do dynamic memory allocation

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow *w = new MainWindow;

    QList<struct fileSystem> list;
    FileSystemsInfo *fileSystemInfo = new FileSystemsInfo;
    fileSystemInfo->setSystemInfoList();
    list = fileSystemInfo->getSystemInfoList();

    struct systemInfo info;
    SystemInfo *sysInfo = new SystemInfo;
    sysInfo->setProcInfo();
    sysInfo->setRAMInfo();
    sysInfo->setOSTypeInfo();
    sysInfo->setOSVersionInfo();
    info = sysInfo->getSystemInfoStruct();

    QList<struct procInfo> procList;
    ProcessInfo *proc = new ProcessInfo;
    proc->setProcInfoList();
    procList = proc->getProcInfoList();

    w->setProcInfoTab(procList);
    w->setSysInfoTab(info);
    w->setFileSysTab(list);
    w->setFixedSize(WIDTH,HEIGTH);
    w->show();

    return a.exec();
}
