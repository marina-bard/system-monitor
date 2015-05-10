#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopServices>
#include <QDir>
#include <QProcess>
//#include "filesystemsinfo.h"

#define MAX_SIZE    256

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    QList<struct fileSystem> systems;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setFileSysTab(QList<struct fileSystem> list);
    void setSysInfoTab(struct systemInfo info);
    void setProcInfoTab(QList<struct procInfo> list);

private slots:
   // void openDirection(QString path);
};

#endif // MAINWINDOW_H
