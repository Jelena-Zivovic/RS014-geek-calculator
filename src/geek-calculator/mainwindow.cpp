#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Function.hpp"
#include "Matrix.hpp"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidgets->setCurrentWidget(ui->mainPage);
    ui->outputTextEdit->setReadOnly(true);
    ui->resultLineEdit->setReadOnly(true);


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_goToBasicCalculatorButton_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->clear();
    ui->outputTextEdit->clear();
    ui->stackedWidgets->setCurrentWidget(ui->commonCalculatorPage);
}

void MainWindow::on_goToFunctionsButton_clicked()
{
    ui->enteredFunctionLineEdit->clear();
    ui->lowerBoundLineEdit->clear();
    ui->upperBoundLineEdit->clear();
    ui->resultLineEdit->clear();
    ui->oneVariableRadioButton->setChecked(true);
    ui->stackedWidgets->setCurrentWidget(ui->functionsPage);

}
void MainWindow::on_goToMatrixButton_clicked()
{
    ui->stackedWidgets->setCurrentWidget(ui->matrixPage);
}



void MainWindow::on_goBackToMainPageButton_clicked()
{

    ui->stackedWidgets->setCurrentWidget(ui->mainPage);

}

void MainWindow::on_goBackToMainPage2_clicked()
{
    ui->stackedWidgets->setCurrentWidget(ui->mainPage);
}


void MainWindow::on_calculateValueButton_clicked()
{
    QString enteredText = ui->enterFunctionToCalculateValueTextEdit->toPlainText();

    try {
        Function function(enteredText);
        std::cout << "valid " << std::endl;
        ui->outputTextEdit->setText(QString::number(function.get_value()));
    } catch(const char *message) {
        ui->outputTextEdit->setText("input is not valid");
    }


}

void MainWindow::on_integralValueFunction_clicked()
{
    QString enteredText = ui->enteredFunctionLineEdit->text();
    int number_of_variables=1;
    if (ui->oneVariableRadioButton->isChecked()) {
        number_of_variables = 1;
    }
    else {
        number_of_variables = 2;
    }

    try {
        Function function(enteredText, number_of_variables);
        float lower_bound = ui->lowerBoundLineEdit->text().toFloat();
        float upper_bound = ui->upperBoundLineEdit->text().toFloat();
        float calculatedValue = function.integral(lower_bound, upper_bound);
        ui->resultLineEdit->setText(QString::number(calculatedValue));
    } catch(const char *message) {
        std::cout << "bla" << std::endl;
    }
}
/*
void MainWindow::on_enterDimensionButton_clicked()
{
    QString n_txt = ui->dimNLineEditA->text();
    QString m_txt = ui->dimMLineEditA->text();
    bool ok;
    int n = n_txt.toInt(&ok, 10);
    if(ok == false){
        QMessageBox msgBox;
        msgBox.setText("Morate uneti ispravan pozitivan broj");
        msgBox.exec();
        return;
    }
    int m = m_txt.toInt(&ok);
    if(ok == false){
        QMessageBox msgBox;
        msgBox.setText("Morate uneti ispravan pozitivan broj");
        msgBox.exec();
        return;
    }
    QString text = ui->matrixInputPlainTextEditA->toPlainText();
    ok = Matrix::check_matrix(text,static_cast<unsigned>(n),static_cast<unsigned>(m));
    if(ok == false){
        QMessageBox msgBox;
        msgBox.setText("Matrica nije dobro uneta");
        msgBox.exec();
        return;
    }
    Eigen::MatrixXd matrix = Matrix::parseText(text, static_cast<unsigned>(n),static_cast<unsigned>(m));
    std::cout << matrix << std::endl;
    std::cout << matrix.pow(2) << std::endl;
}*/

