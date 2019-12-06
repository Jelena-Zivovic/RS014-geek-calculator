#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackWidgets->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_commonCalculatorButton_clicked()
{
    ui->stackWidgets->setCurrentIndex(1);
}

void MainWindow::on_functionsButton_clicked()
{
    ui->stackWidgets->setCurrentIndex(2);
}





void MainWindow::on_backButtonCommonCalculator_clicked()
{
    ui->stackWidgets->setCurrentIndex(0);
}

void MainWindow::on_backButtonFunctions_clicked()
{
    ui->stackWidgets->setCurrentIndex(0);
}
