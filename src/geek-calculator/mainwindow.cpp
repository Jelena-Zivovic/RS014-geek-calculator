#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Function.hpp"
#include "Matrix.hpp"
#include <QMessageBox>
#include <mgl2/eval.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidgets->setCurrentWidget(ui->mainPage);
    ui->outputTextEdit->setReadOnly(true);
    configureFunctionPage();

    //ui->resultLineEdit->setReadOnly(true);
    ui->matrixOutputPlainTextEdit->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::configureFunctionPage()
{
    ui->secondLowerBoundLabel->hide();
    ui->secondLowerBoundLineEdit->hide();
    ui->secondUpperBoundLabel->hide();
    ui->secondUpperBoundLineEdit->hide();
    ui->resultIntegralLineEdit->setReadOnly(true);
    ui->resultDerivativeLineEdit->setReadOnly(true);
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
    ui->firstLowerBoundLineEdit->clear();
    ui->firstUpperBoundLineEdit->clear();
    ui->resultIntegralLineEdit->clear();
    ui->enterFunctionDerivativeLineEdit->clear();
    ui->resultDerivativeLineEdit->clear();
    ui->enterPointLineEdit->clear();
    ui->oneVariableRadioButton->setChecked(true);
    ui->firstDerivativeRadioButton->setChecked(true);
    ui->functionsTab->setCurrentIndex(0);
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

    try
    {
        Function function(enteredText);
        std::cout << "valid " << std::endl;
        ui->outputTextEdit->setText(QString::number(function.get_value()));
    }
    catch (const char *message)
    {
        ui->outputTextEdit->setText("input is not valid");
    }
}

void MainWindow::on_integralValueFunction_clicked()
{

    QString enteredText = ui->enteredFunctionLineEdit->text();
    int number_of_variables = 1;
    if (ui->oneVariableRadioButton->isChecked())
    {
        number_of_variables = 1;
    }
    else
    {
        number_of_variables = 2;
    }

    try
    {
        Function function(enteredText, number_of_variables);

        if (number_of_variables == 1)
        {
            float lower_bound = ui->firstLowerBoundLineEdit->text().toFloat();
            float upper_bound = ui->firstUpperBoundLineEdit->text().toFloat();
            float calculatedValue = function.oneVariableIntegral(lower_bound, upper_bound);
            ui->resultIntegralLineEdit->setText(QString::number(calculatedValue));
        }
        else
        {
            float firstLowerBound = ui->firstLowerBoundLineEdit->text().toFloat();
            float firstUpperBound = ui->firstUpperBoundLineEdit->text().toFloat();
            float secondLowerBound = ui->secondLowerBoundLineEdit->text().toFloat();
            float secondUpperBound = ui->secondUpperBoundLineEdit->text().toFloat();
            float calculatedValue = function.twoVariableIntegral(firstLowerBound, firstUpperBound, secondLowerBound, secondUpperBound);
            ui->resultIntegralLineEdit->setText(QString::number(calculatedValue));
        }
    }
    catch (const char *message)
    {
        std::cout << "bla" << std::endl;
    }
}
void MainWindow::on_enterDimensionButtonA_clicked()
{
    read_matrix(1);
}
void MainWindow::read_matrix(int indicator)
{
    QString n_txt;
    QString m_txt;
    if (indicator == 1)
    {
        n_txt = ui->dimNLineEditA->text();
        m_txt = ui->dimMLineEditA->text();
    }
    else
    {
        n_txt = ui->dimNLineEditB->text();
        m_txt = ui->dimMLineEditB->text();
    }
    bool ok;
    unsigned n, m;
    n = static_cast<unsigned>(n_txt.toInt(&ok));
    if (ok == false)
    {
        error_boxMsg("Dimension n of matrix needs to be a unsigned number");
        return;
    }
    m = static_cast<unsigned>(m_txt.toInt(&ok));
    if (ok == false)
    {
        error_boxMsg("Dimension m of matrix needs to be a unsigned number");
        return;
    }
    QString text;
    if (indicator == 1)
    {
        text = ui->matrixInputPlainTextEditA->toPlainText();
    }
    else
    {
        text = ui->matrixInputPlainTextEditB->toPlainText();
    }
    ok = Matrix::check_matrix(text, n, m);
    if (ok == false)
    {
        error_boxMsg("Matrix format need to be " + n_txt + "x" + m_txt + " numbers");
        if (indicator == 1)
        {
            ui->matrixInputPlainTextEditA->clear();
        }
        else
        {
            ui->matrixInputPlainTextEditB->clear();
        }
        return;
    }
    Eigen::MatrixXd _matrix = Matrix::parseText(text, n, m);
    Matrix matrix(_matrix);
    if (indicator == 1)
    {
        A = matrix;
        ui->matrixOutputPlainTextEdit->appendPlainText("A: ");
        ui->matrixOutputPlainTextEdit->appendPlainText(A.matrix_format());
    }
    else
    {
        B = matrix;
        ui->matrixOutputPlainTextEdit->appendPlainText("B: ");
        ui->matrixOutputPlainTextEdit->appendPlainText(B.matrix_format());
    }
}
void MainWindow::error_boxMsg(QString error_msg)
{
    QMessageBox msgBox;
    msgBox.setText(error_msg);
    msgBox.exec();
    return;
}

void MainWindow::on_enterDimensionButtonB_clicked()
{
    read_matrix(0);
}

void MainWindow::on_plusButton_clicked()
{
    if (ui->matrixInputPlainTextEditA->toPlainText().isEmpty() || ui->matrixInputPlainTextEditB->toPlainText().isEmpty())
    {
        return;
    }
    if (A.rows() == B.rows() && A.cols() == B.cols() && A.rows() != 0)
    {
        Matrix plus = A + B;
        ui->matrixOutputPlainTextEdit->appendPlainText("A+B: ");
        ui->matrixOutputPlainTextEdit->appendPlainText(plus.matrix_format());
    }
}

void MainWindow::on_minusButton_clicked()
{
    if (ui->matrixInputPlainTextEditA->toPlainText().isEmpty() || ui->matrixInputPlainTextEditB->toPlainText().isEmpty())
    {
        return;
    }
    if (A.rows() == B.rows() && A.cols() == B.cols() && A.rows() != 0)
    {
        Matrix minus = A - B;
        ui->matrixOutputPlainTextEdit->appendPlainText("A-B: ");
        ui->matrixOutputPlainTextEdit->appendPlainText(minus.matrix_format());
    }
}

void MainWindow::on_multiplyButton_clicked()
{
    if (ui->matrixInputPlainTextEditA->toPlainText().isEmpty() || ui->matrixInputPlainTextEditB->toPlainText().isEmpty())
    {
        return;
    }
    if (A.cols() == B.rows() && A.rows() != 0 && B.rows() != 0)
    {
        Matrix multiply = A * B;
        ui->matrixOutputPlainTextEdit->appendPlainText("A*B: ");
        ui->matrixOutputPlainTextEdit->appendPlainText(multiply.matrix_format());
    }
}

void MainWindow::on_determinantButtonA_clicked()
{
    if (ui->matrixInputPlainTextEditA->toPlainText().isEmpty())
    {
        return;
    }
    if (A.rows() == 0)
    {
        return;
    }

    double det = A.det();
    QString det_txt = QString::number(det);
    ui->matrixOutputPlainTextEdit->appendPlainText("Determant of A: " + det_txt);
}

void MainWindow::on_determinantButtonB_clicked()
{
    if (ui->matrixInputPlainTextEditB->toPlainText().isEmpty())
    {
        return;
    }
    if (B.rows() == 0)
    {
        return;
    }

    double det = B.det();
    QString det_txt = QString::number(det);
    ui->matrixOutputPlainTextEdit->appendPlainText("Determant of B: " + det_txt);
}

void MainWindow::on_inverseButtonA_clicked()
{
    if (ui->matrixInputPlainTextEditA->toPlainText().isEmpty())
    {
        return;
    }
    if (A.rows() == 0)
    {
        return;
    }
    if (A.det() == 0)
    {
        ui->matrixOutputPlainTextEdit->appendPlainText("No inverse for A");
        return;
    }

    Matrix inv = A.inv();
    ui->matrixOutputPlainTextEdit->appendPlainText("Inverse of A: ");
    ui->matrixOutputPlainTextEdit->appendPlainText(inv.matrix_format());
}

void MainWindow::on_inverseButtonB_clicked()
{
    if (ui->matrixInputPlainTextEditB->toPlainText().isEmpty())
    {
        return;
    }
    if (B.rows() == 0)
    {
        return;
    }
    if (B.det() == 0)
    {
        ui->matrixOutputPlainTextEdit->appendPlainText("No inverse for B");
        return;
    }

    Matrix inv = B.inv();
    ui->matrixOutputPlainTextEdit->appendPlainText("Inverse of B: ");
    ui->matrixOutputPlainTextEdit->appendPlainText(inv.matrix_format());
}

void MainWindow::on_transposeButtonA_clicked()
{
    if (ui->matrixInputPlainTextEditA->toPlainText().isEmpty())
    {
        return;
    }
    if (A.rows() == 0)
    {
        return;
    }

    Matrix transpose = A.transpose();
    ui->matrixOutputPlainTextEdit->appendPlainText("Transpose of A: ");
    ui->matrixOutputPlainTextEdit->appendPlainText(transpose.matrix_format());
}

void MainWindow::on_transposeButtonB_clicked()
{
    if (ui->matrixInputPlainTextEditB->toPlainText().isEmpty())
    {
        return;
    }
    if (B.rows() == 0)
    {
        return;
    }

    Matrix transpose = B.transpose();
    ui->matrixOutputPlainTextEdit->appendPlainText("Transpose of A: ");
    ui->matrixOutputPlainTextEdit->appendPlainText(transpose.matrix_format());
}

void MainWindow::on_multiplyByButtonA_clicked()
{
    if (ui->multiplyBylineEditA->text().isEmpty())
    {
        return;
    }
    QString num_txt = ui->multiplyBylineEditA->text();
    bool ok;
    double num = num_txt.toDouble(&ok);
    if (ok == false)
    {
        error_boxMsg("Multiply must be a number");
        return;
    }
    Matrix tmp = A * num;
    ui->matrixOutputPlainTextEdit->appendPlainText("A*" + num_txt + ": ");
    ui->matrixOutputPlainTextEdit->appendPlainText(tmp.matrix_format());
}

void MainWindow::on_multiplyByButtonB_clicked()
{
    if (ui->multiplBylineEditB->text().isEmpty())
    {
        return;
    }
    QString num_txt = ui->multiplBylineEditB->text();
    bool ok;
    double num = num_txt.toDouble(&ok);
    if (ok == false)
    {
        error_boxMsg("Multiply must be a number");
        return;
    }
    Matrix tmp = B * num;
    ui->matrixOutputPlainTextEdit->appendPlainText("B*" + num_txt + ": ");
    ui->matrixOutputPlainTextEdit->appendPlainText(tmp.matrix_format());
}

void MainWindow::on_raisePowerButtonA_clicked()
{
    if (ui->raisePowerlineEditA->text().isEmpty())
    {
        return;
    }
    if(A.rows() != A.cols()){
        return;
    }
    QString num_txt = ui->raisePowerlineEditA->text();
    bool ok;
    double num = num_txt.toDouble(&ok);
    if (ok == false)
    {
        error_boxMsg("Multiply must be a number");
        return;
    }
    Matrix tmp = A.pow(num);
    ui->matrixOutputPlainTextEdit->appendPlainText("B^" + num_txt + ": ");
    ui->matrixOutputPlainTextEdit->appendPlainText(tmp.matrix_format());
}
void MainWindow::on_raisePowerButtonB_clicked()
{
    if (ui->raisePowerlineEditB->text().isEmpty())
    {
        return;
    }
    if(B.rows() != B.cols()){
        return;
    }
    QString num_txt = ui->raisePowerlineEditB->text();
    bool ok;
    double num = num_txt.toDouble(&ok);
    if (ok == false)
    {
        error_boxMsg("Multiply must be a number");
        return;
    }
    Matrix tmp = B.pow(num);
    ui->matrixOutputPlainTextEdit->appendPlainText("B^" + num_txt + ": ");
    ui->matrixOutputPlainTextEdit->appendPlainText(tmp.matrix_format());
}

void MainWindow::on_goFromMatrixToMainPageButton_clicked()
{
    ui->stackedWidgets->setCurrentWidget(ui->mainPage);
}

void MainWindow::on_twoVariablesRadioButton_clicked()
{
    ui->secondLowerBoundLabel->show();
    ui->secondLowerBoundLineEdit->show();
    ui->secondUpperBoundLabel->show();
    ui->secondUpperBoundLineEdit->show();
}

void MainWindow::on_oneVariableRadioButton_clicked()
{
    ui->secondLowerBoundLabel->hide();
    ui->secondLowerBoundLineEdit->hide();
    ui->secondUpperBoundLabel->hide();
    ui->secondUpperBoundLineEdit->hide();
}

void MainWindow::on_clearIntegralTabButton_clicked()
{
    ui->enteredFunctionLineEdit->clear();
    ui->firstLowerBoundLineEdit->clear();
    ui->firstUpperBoundLineEdit->clear();
    ui->secondLowerBoundLineEdit->clear();
    ui->secondUpperBoundLineEdit->clear();
    ui->resultIntegralLineEdit->clear();
}


void MainWindow::on_goBackToMainPageButton_3_clicked()
{
    ui->stackedWidgets->setCurrentWidget(ui->mainPage);
}

void MainWindow::on_clearDerivativeButton_clicked()
{
    ui->enterFunctionDerivativeLineEdit->clear();
    ui->enterPointLineEdit->clear();
    ui->resultDerivativeLineEdit->clear();
}

void MainWindow::on_calculateDerivativeButton_clicked()
{
    QString enteredText = ui->enterFunctionDerivativeLineEdit->text();

    try {
       Function function(enteredText);

       float point = ui->enterPointLineEdit->text().toFloat();
       float result;

       if (ui->firstDerivativeRadioButton->isChecked()) {
           result = function.firstDerivative(point);
       }
       else {
           result = function.secondDerivative(point);
       }

       ui->resultDerivativeLineEdit->setText(QString::number(result));

    } catch (const char *message) {
        std::cout << message << std::endl;
    }
}
