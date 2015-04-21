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

   // ui->centralWidget;
    //ui->tableWidget->setShowGrid(true);
   // for(int i = 0; i < 6; i++)
     //   ui->tableWidget->setColumnHidden(i, false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: setFileSysTab(QList<struct fileSystem> systems)
{
    int i = 0, j = 1;
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

        QString temp = info.dir;
     //   connect(ui->tableWidgetFileSys, SIGNAL(cellDoubleClicked(i,j)), this, SLOT(openDirection(temp)));
        i++;
    }
    QProcess().startDetached("/");
    return;
}

void MainWindow:: setSysInfoTab(struct systemInfo info)
{
    ui->labelProcInfo->setText(info.proc);
    ui->labelRAMInfo->setText(info.RAM);
    ui->labelOSNameInfo->setText(info.OSType);
    ui->labelOSVersionInfo->setText(info.OSVersion);
}
/*void openDirection(QString path)
{
    //start filebrowser
}*/
