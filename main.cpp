#include "mainwindow.h"
#include "filesystemsinfo.h"
#include "systeminfo.h"
//#include "structures.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow *w = new MainWindow;

    QList<struct fileSystem> list;
    struct systemInfo info;

    FileSystemsInfo *fileSystemInfo = new FileSystemsInfo;
    fileSystemInfo->setSystemInfoList();
    list = fileSystemInfo->getSystemInfoList();

    SystemInfo *sysInfo = new SystemInfo;
   // sysInfo->setStructInfo();
    sysInfo->setProcInfo();
    sysInfo->setRAMInfo();
    sysInfo->setOSTypeInfo();
    sysInfo->setOSVersionInfo();
    info = sysInfo->getSystemInfoStruct();

    w->setSysInfoTab(info);
    w->setFileSysTab(list);
    w->setFixedSize(685,510);
    w->show();

    return a.exec();
}
