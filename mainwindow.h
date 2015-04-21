#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopServices>
#include <QDir>
#include <QProcess>
//#include "filesystemsinfo.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setFileSysTab(QList<struct fileSystem> list);
    void setSysInfoTab(struct systemInfo info);
private slots:
   // void openDirection(QString path);
private:
    Ui::MainWindow *ui;
    QList<struct fileSystem> systems;
};

#endif // MAINWINDOW_H
