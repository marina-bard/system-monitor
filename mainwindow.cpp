#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent, 0),
    ui(new Ui::MainWindow)
{    
    ui->setupUi(this);
    ui->mainToolBar->hide();
    ui->tabMenu->setCurrentIndex(0);
    ui->tableWidgetProcesses->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetFileSys->setEditTriggers(QAbstractItemView::NoEditTriggers);
    setCentralWidget(ui->tabMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setFileSysTab(QList<struct fileSystem> systems)
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
        i++;
    }
}

void MainWindow::updateFileSysTab(struct fileSystem* info, bool toDelete)
{
    int rowCount;
    int column = 1;

    mutex.lock();
    rowCount = ui->tableWidgetFileSys->rowCount();

    ui->tableWidgetFileSys->setSortingEnabled(false);
    if(toDelete)
    {
        for(int i = 0; i < rowCount; i++)
        {
            QString dir = ui->tableWidgetFileSys->item(i, column)->text();
            if(dir == info->dir)
                ui->tableWidgetFileSys->removeRow(i);
        }
    }
    else
    {
        ui->tableWidgetFileSys->insertRow(rowCount);
        ui->tableWidgetFileSys->setItem(rowCount, 0, new QTableWidgetItem(info->fsname));
        ui->tableWidgetFileSys->setItem(rowCount, 1, new QTableWidgetItem(info->dir));
        ui->tableWidgetFileSys->setItem(rowCount, 2, new QTableWidgetItem(info->type));
    }
    ui->tableWidgetFileSys->setSortingEnabled(true);
    mutex.unlock();
}

void MainWindow:: setProcInfoTab(QList<struct procInfo>* processes)
{
    int i = 0;
    struct procInfo info;
    //QList<struct procInfo> processes;
    QListIterator<struct procInfo> iter(*processes);
    iter.toFront();

    while(iter.hasNext())
    {
       info = iter.next();

       setProcInfoItem(i, info);

       pids.push_back(info.pid);
       i++;
    }

    ui->tableWidgetProcesses->verticalHeader()->hide();
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

void MainWindow::updateProcInfoTab(struct procInfo* process, bool toDelete)
{
    int rowCount;
    int column = 4;

    mutex.lock();
    rowCount = ui->tableWidgetProcesses->rowCount();

    if(toDelete)
    {

        for(int i = 0; i < rowCount; i++)
        {
            QString pid = ui->tableWidgetProcesses->item(i, column)->text();
            if(pid == QString("%1").arg(process->pid))
            {
                ui->tableWidgetProcesses->removeRow(i);
                break;
            }
        }
    }
    else
        setProcInfoItem(0, *process);
    mutex.unlock();
}

void MainWindow::updateProcInfoParams(struct procInfo* process)
{
    int rowCount;
    int column = 4;

    mutex.lock();
    rowCount = ui->tableWidgetProcesses->rowCount();
    for(int i = 0; i < rowCount; i++)
    {
        QString pid = ui->tableWidgetProcesses->item(i, column)->text();
        if(pid == QString("%1").arg(process->pid))
        {
            ui->tableWidgetProcesses->item(i,1)->setText(QString("%1").arg(process->cpuUsage));
            ui->tableWidgetProcesses->item(i,2)->setText(QString("%1").arg(process->memory));
            ui->tableWidgetProcesses->item(i,3)->setText(QString("%1").arg(process->rss));
            ui->tableWidgetProcesses->item(i,6)->setText(process->status);
            break;
        }
    }
    mutex.unlock();

}

void MainWindow::setProcInfoItem(int row, struct procInfo info)
{
    char* rss = (char*)malloc(sizeof(char) * MAX_SIZE);
    char* vMem = (char*)malloc(sizeof(char) * MAX_SIZE);

    sprintf(vMem, "%.3f Mib", info.memory);
    sprintf(rss, "%.3f Mib", info.rss);

    ui->tableWidgetProcesses->setSortingEnabled(false);
    ui->tableWidgetProcesses->insertRow(row);
    ui->tableWidgetProcesses->setItem(row, 0, new QTableWidgetItem(info.name));
    ui->tableWidgetProcesses->setItem(row, 1, new QTableWidgetItem(QString("%1").arg(info.cpuUsage)));
    ui->tableWidgetProcesses->setItem(row, 2, new QTableWidgetItem(vMem));
    ui->tableWidgetProcesses->setItem(row, 3, new QTableWidgetItem(rss));
    ui->tableWidgetProcesses->setItem(row, 4, new QTableWidgetItem(QString("%1").arg(info.pid)));
    ui->tableWidgetProcesses->setItem(row, 5, new QTableWidgetItem(QString("%1").arg(info.ppid)));
    ui->tableWidgetProcesses->setItem(row, 6, new QTableWidgetItem(info.status));
    ui->tableWidgetProcesses->setSortingEnabled(true);

    delete rss;
    delete vMem;
}

