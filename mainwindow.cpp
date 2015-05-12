#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "structures.h"
#include "filesystemsinfo.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent, 0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->hide();
    ui->tabMenu->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: setFileSysTab(QList<struct fileSystem> systems)
{
    int i = 0;
    struct fileSystem info;
    QListIterator<struct fileSystem> iter(systems);
    iter.toFront();

    while(iter.hasNext())
    {
        info = iter.next();
        ui->tableWidgetFileSys->insertRow(i);
        ui->tableWidgetFileSys->setItem(i, 0, new QTableWidgetItem(info.fsname));
        ui->tableWidgetFileSys->setItem(i, 1, new QTableWidgetItem(info.dir));
        ui->tableWidgetFileSys->setItem(i, 2, new QTableWidgetItem(info.type));

     //   QString temp = info.dir;
     //   connect(ui->tableWidgetFileSys, SIGNAL(cellDoubleClicked(i,j)), this, SLOT(openDirection(temp)));
        i++;
    }
   // QProcess().startDetached("/");
    return;
}

void MainWindow:: setProcInfoTab(QList<procInfo> processes)
{
    int i = 0;
    struct procInfo info;
    QListIterator<struct procInfo> iter(processes);
    iter.toFront();

    while(iter.hasNext())
    {
       info = iter.next();

       char* vMem = (char*)malloc(sizeof(char) * MAX_SIZE);
       sprintf(vMem, "%.3f Mib", info.memory);

       char* rss = (char*)malloc(sizeof(char) * MAX_SIZE);
       sprintf(rss, "%.3f Mib", info.rss);

       ui->tableWidgetProcesses->insertRow(i);
       ui->tableWidgetProcesses->setItem(i, 0, new QTableWidgetItem(info.name));
       ui->tableWidgetProcesses->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(info.cpuUsage)));
       ui->tableWidgetProcesses->setItem(i, 2, new QTableWidgetItem(vMem));
       ui->tableWidgetProcesses->setItem(i, 3, new QTableWidgetItem(rss));
       ui->tableWidgetProcesses->setItem(i, 4, new QTableWidgetItem(QString("%1").arg(info.pid)));
       ui->tableWidgetProcesses->setItem(i, 5, new QTableWidgetItem(QString("%1").arg(info.ppid)));
       ui->tableWidgetProcesses->setItem(i, 6, new QTableWidgetItem(info.status));
       i++;
    }

    ui->tableWidgetProcesses->verticalHeader()->hide();
    return;
}

void MainWindow:: setSysInfoTab(struct systemInfo info)
{
    char* temp = (char*)malloc(sizeof(char) * MAX_SIZE);
    sprintf(temp, "%.2f Gb", info.RAM);

    ui->labelProcInfo->setText(info.proc);
    ui->labelRAMInfo->setText(temp);
    ui->labelOSNameInfo->setText(info.OSType);
    ui->labelOSVersionInfo->setText(info.OSVersion);
}
