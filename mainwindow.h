#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdio.h>
#include <QList>
#include <QMutex>
//#include "mythread.h"
#include "processmonitoring.h"
#include "filesystemsmonitoring.h"
#include "systeminfo.h"

#define MAX_SIZE    256
#define WIDTH       685
#define HEIGTH      510

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    QList<struct fileSystem> systems;
    QList<int> pids;
    QMutex mutex;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setFileSysTab(QList<struct fileSystem> systems);
    void setSysInfoTab(struct systemInfo info);
    void setProcInfoItem(int row, struct procInfo info);

public slots:
    void updateFileSysTab(struct fileSystem* info, bool toDelete);
    void updateProcInfoTab(struct procInfo* process, bool toDelete);
    void updateProcInfoParams(struct procInfo* process);
    void setProcInfoTab(QList<struct procInfo>* processes);

signals:
    void finishedProcessUpdating();
};

#endif // MAINWINDOW_H
