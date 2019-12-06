#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Function.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidgets->setCurrentIndex(0);
    ui->outputTextEdit->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_goToBasicCalculatorButton_clicked()
{
    ui->stackedWidgets->setCurrentIndex(1);
}

void MainWindow::on_goToFunctionsButton_clicked()
{
    ui->stackedWidgets->setCurrentIndex(2);
}

void MainWindow::on_goBackToMainPageButton_clicked()
{
    ui->stackedWidgets->setCurrentIndex(0);
}

void MainWindow::on_goBackToMainPage2_clicked()
{
    ui->stackedWidgets->setCurrentIndex(0);
}


void MainWindow::on_calculateValueButton_clicked()
{
    QString enteredText = ui->enterFunctionToCalculateValueTextEdit->toPlainText();

    try {
        Function function(enteredText);
        std::cout << "valid " << std::endl;
        ui->outputTextEdit->setText(QString::number(function.get_value()));
    } catch(const char *message) {
        std::cout << message << std::endl;
    }


}



















