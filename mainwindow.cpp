#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->hide();
    ui->tabMenu->setCurrentIndex(0);
    //ui->tableWidget->setShowGrid(true);
   // for(int i = 0; i < 6; i++)
     //   ui->tableWidget->setColumnHidden(i, false);
}

MainWindow::~MainWindow()
{
    delete ui;
}
