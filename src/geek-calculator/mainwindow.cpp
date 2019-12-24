#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Function.hpp"
#include "Matrix.hpp"
#include <QMessageBox>
#include <mgl2/eval.h>
#include <mgl2/data.h>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidgets->setCurrentWidget(ui->mainPage);
    ui->outputTextEdit->setReadOnly(true);
    configureFunctionPage();
    configureMatrixPage();
    configureGeometryPage();

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
void MainWindow::configureMatrixPage()
{
    ui->ARadioButton->setChecked(1);
    ui->matrixOutputPlainTextEdit->setReadOnly(true);
    ui->matrixInputPlainTextEditA->clear();
    ui->matrixInputPlainTextEditB->clear();
    ui->dimMLineEditA->clear();
    ui->dimNLineEditA->clear();
    ui->dimMLineEditB->clear();
    ui->dimNLineEditB->clear();
    ui->multiplyBylineEditA->clear();
    ui->raisePowerlineEditA->clear();
    ui->matrixOutputPlainTextEdit->clear();
    ui->matrixInputPlainTextEditB->hide();
    ui->matrixInputPlainTextEditA->hide();
    ui->enterMatrixButtonA->hide();
    ui->enterMatrixButtonB->hide();
}

void MainWindow::configureGeometryPage() {

    QPixmap imageCircle(":/images/circle.png");
    QIcon circleButtonIcon(imageCircle);
    ui->circleButton->setIcon(circleButtonIcon);

    QPixmap imageParallelogram(":/images/parallelogram.jpg");
    QIcon parallelogramButtonIcon(imageParallelogram);
    ui->parallelogramButton->setIcon(parallelogramButtonIcon);

    QPixmap imageRectangle(":/images/rectangle.png");
    QIcon rectangleButtonIcon(imageRectangle);
    ui->rectangleButton->setIcon(rectangleButtonIcon);

    QPixmap imageTrapezoid(":/images/trapezoid.webp");
    QIcon trapezoidButtonIcon(imageTrapezoid);
    ui->trapezoidButton->setIcon(trapezoidButtonIcon);

    QPixmap imageTriangle(":/images/triangle.jpg");
    QIcon triangleButtonIcon(imageTriangle);
    ui->triangleButton->setIcon(triangleButtonIcon);

    QPixmap imageCone(":/images/cone.png");
    QIcon coneButtonIcon(imageCone);
    ui->coneButton->setIcon(coneButtonIcon);

    QPixmap imageCube(":/images/cube.jpg");
    QIcon cubeButtonIcon(imageCube);
    ui->cubeButton->setIcon(cubeButtonIcon);

    QPixmap imageCylinder(":/images/cylinder.jpeg");
    QIcon cylinderButtonIcon(imageCylinder);
    ui->cylinderButton->setIcon(cylinderButtonIcon);

    QPixmap imageSquare(":/images/square.png");
    QIcon squareButtonIcon(imageSquare);
    ui->squareButton->setIcon(squareButtonIcon);

    QPixmap imageSphere(":/images/sphere.jpeg");
    QIcon sphereButtonIcon(imageSphere);
    ui->sphereButton->setIcon(sphereButtonIcon);




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
    ui->oneVariablePlottingRadioButton->setChecked(true);
    ui->functionsTab->setCurrentIndex(0);
    ui->xRangeLeftPlotDoubleSpinBox->setValue(-1);
    ui->xRangeRightPlotDoubleSpinBox->setValue(1);
    ui->yLeftRangePlotDoubleSpinBox->setValue(-1);
    ui->yRangeRightPlotDoubleSpinBox->setValue(1);
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
        double value = function.get_value();
        //std::cout << value << std::endl;
        ui->outputTextEdit->setText(QString::number(value));
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
    QString n_txt;
    QString m_txt;

    n_txt = ui->dimNLineEditA->text();
    m_txt = ui->dimMLineEditA->text();

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
    Matrix tmp(n,m);
    A = tmp;
    ui->enterMatrixButtonA->show();
    ui->matrixInputPlainTextEditA->show();
}
void MainWindow::read_matrix(int indicator)
{
    unsigned n,m;
    if(indicator==1){
        n = A.rows();
        m = A.cols();
    }else{
        n=B.rows();
        m = B.cols();
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
    bool ok = Matrix::check_matrix(text, n, m);
    if (ok == false)
    {
        error_boxMsg("Matrix format need to be " + QString::number(n) + "x" + QString::number(m) + " numbers");
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

    Eigen::MatrixXd _matrix = Matrix::parseText(text, n,m);
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
    QString n_txt;
    QString m_txt;

    n_txt = ui->dimNLineEditB->text();
    m_txt = ui->dimMLineEditB->text();

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
    Matrix tmp(n,m);
    B = tmp;
    ui->enterMatrixButtonB->show();
    ui->matrixInputPlainTextEditB->show();
}

void MainWindow::on_matrixPlusButton_clicked()
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

void MainWindow::on_matrixMinusButton_clicked()
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

void MainWindow::on_matrixMultiplyButton_clicked()
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
    if(ui->ARadioButton->isChecked())
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
    else
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
}

/*
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
}*/

void MainWindow::on_inverseButtonA_clicked()
{
    if(ui->ARadioButton->isChecked())
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
    else
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
}
/*
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
}*/

void MainWindow::on_transposeButtonA_clicked()
{
    if(ui->ARadioButton->isChecked())
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
    else
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
        ui->matrixOutputPlainTextEdit->appendPlainText("Transpose of B: ");
        ui->matrixOutputPlainTextEdit->appendPlainText(transpose.matrix_format());
    }
}
/*
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
}*/

void MainWindow::on_multiplyByButtonA_clicked()
{
    if(ui->ARadioButton->isChecked())
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
    else
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
        Matrix tmp = B * num;
        ui->matrixOutputPlainTextEdit->appendPlainText("B*" + num_txt + ": ");
        ui->matrixOutputPlainTextEdit->appendPlainText(tmp.matrix_format());
    }
}
/*
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
}*/

void MainWindow::on_raisePowerButtonA_clicked()
{
    if(ui->ARadioButton->isChecked())
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
        ui->matrixOutputPlainTextEdit->appendPlainText("A^" + num_txt + ": ");
        ui->matrixOutputPlainTextEdit->appendPlainText(tmp.matrix_format());
    }
    else
    {
        if (ui->raisePowerlineEditA->text().isEmpty())
        {
            return;
        }
        if(B.rows() != B.cols()){
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
        Matrix tmp = B.pow(num);
        ui->matrixOutputPlainTextEdit->appendPlainText("B^" + num_txt + ": ");
        ui->matrixOutputPlainTextEdit->appendPlainText(tmp.matrix_format());
    }
}
/*
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
}*/

void MainWindow::on_goFromMatrixToMainPageButton_clicked()
{
    configureMatrixPage();
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

void MainWindow::on_dotButton_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("."));
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
}

void MainWindow::on_number1Button_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("1"));
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);

}



void MainWindow::on_number2Button_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("2"));
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
}

void MainWindow::on_number3Button_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("3"));
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
}

void MainWindow::on_number4Button_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("4"));
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
}

void MainWindow::on_number5Button_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("5"));
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
}

void MainWindow::on_number6Button_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("6"));
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
}

void MainWindow::on_number7Button_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("7"));
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
}

void MainWindow::on_number8Button_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("8"));
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
}

void MainWindow::on_number9Button_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("9"));
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
}

void MainWindow::on_number0Button_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("0"));
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
}

void MainWindow::on_enterMatrixButtonA_clicked()
{
    read_matrix(1);
}

void MainWindow::on_enterMatrixButtonB_clicked()
{
    read_matrix(2);
}

void MainWindow::on_addMatrixButton_clicked()
{
    ui->dimMLabelB->show();
    ui->dimNLabelB->show();
    ui->dimMLineEditB->show();
    ui->dimNLineEditB->show();
    ui->enterDimensionButtonB->show();
    ui->matrixPlusButton->show();
    ui->matrixMinusButton->show();
    ui->matrixMultiplyButton->show();
}

void MainWindow::on_clearMatrixButton_clicked()
{
    ui->matrixInputPlainTextEditA->clear();
    ui->matrixInputPlainTextEditB->clear();
    ui->dimMLineEditA->clear();
    ui->dimNLineEditA->clear();
    ui->dimMLineEditB->clear();
    ui->dimNLineEditB->clear();
    ui->multiplyBylineEditA->clear();
    ui->raisePowerlineEditA->clear();
    ui->matrixOutputPlainTextEdit->clear();

}



void MainWindow::on_matrixRankButton_clicked()
{
    if(ui->ARadioButton->isChecked())
    {
        if (ui->matrixInputPlainTextEditA->toPlainText().isEmpty())
        {
            return;
        }
        if (A.rows() == 0)
        {
            return;
        }

        long rank  = A.rank();
        ui->matrixOutputPlainTextEdit->appendPlainText("Rank of A: ");
        ui->matrixOutputPlainTextEdit->appendPlainText(QString::number(rank));
    }
    else
    {
        if (ui->matrixInputPlainTextEditB->toPlainText().isEmpty())
        {
            return;
        }
        if (B.rows() == 0)
        {
            return;
        }

        long rank  = B.rank();
        ui->matrixOutputPlainTextEdit->appendPlainText("Rank of B: ");
        ui->matrixOutputPlainTextEdit->appendPlainText(QString::number(rank));
    }
}

void MainWindow::on_LUDecompButton_clicked()
{
    if(ui->ARadioButton->isChecked())
    {
        if (ui->matrixInputPlainTextEditA->toPlainText().isEmpty())
        {
            return;
        }
        if (A.rows() == 0)
        {
            return;
        }

        Matrix L = A.getL();
        Matrix U = A.getU();
        ui->matrixOutputPlainTextEdit->appendPlainText("LU decomposition of A: ");
        ui->matrixOutputPlainTextEdit->appendPlainText(L.matrix_format() + "x\n" + U.matrix_format());
    }
    else
    {
        if (ui->matrixInputPlainTextEditB->toPlainText().isEmpty())
        {
            return;
        }
        if (B.rows() == 0)
        {
            return;
        }

        Matrix L = B.getL();
        Matrix U = B.getU();
        ui->matrixOutputPlainTextEdit->appendPlainText("LU decomposition of B: ");
        ui->matrixOutputPlainTextEdit->appendPlainText(L.matrix_format() + "x\n" + U.matrix_format());
    }
}

void MainWindow::on_plotFunctionButton_clicked()
{
    QString enteredFunction = ui->enterFunctionPlottingLineEdit->text();
    int number_of_variables = ui->oneVariablePlottingRadioButton->isChecked() ? 1 : 2;

    try {
        Function function(enteredFunction, number_of_variables);

        if (number_of_variables == 1) {
            double xLeft = ui->xRangeLeftPlotDoubleSpinBox->value();
            double xRight = ui->xRangeRightPlotDoubleSpinBox->value();

            if (xLeft >= xRight) {
                error_boxMsg("invalid range for x");
                return;
            }

            double yLeft = ui->yLeftRangePlotDoubleSpinBox->value();
            double yRight = ui->yRangeRightPlotDoubleSpinBox->value();

            if (yLeft >= yRight) {
                error_boxMsg("invalid range for x");
                return;
            }

            int number_of_points = static_cast<int>((xRight-xLeft)/0.02);

            QVector<double> x(number_of_points), y(number_of_points);

            double h = (xRight-xLeft) / static_cast<double>(number_of_points-1);

            mglFormula formula(function.get_string_function().toUtf8().constData());

            for (int i = 0; i < number_of_points; i++) {
                x[i] = xLeft + h*i;
                y[i] = formula.Calc(x[i]);
            }


            ui->plotWidget->addGraph();
            ui->plotWidget->graph(0)->setData(x, y);

            ui->plotWidget->xAxis->setRange(xLeft, xRight);
            ui->plotWidget->yAxis->setRange(yLeft, yRight);

            ui->plotWidget->replot();


        }
        else {

        }

    } catch (const char *message) {
        std::cout << message << std::endl;
    }

}



void MainWindow::on_backPlotButton_clicked()
{
    ui->stackedWidgets->setCurrentWidget(ui->mainPage);
}

void MainWindow::on_clearPlotButton_clicked()
{
    ui->enterFunctionPlottingLineEdit->clear();
    ui->plotWidget->clearGraphs();
    ui->xRangeLeftPlotDoubleSpinBox->setValue(-1);
    ui->xRangeRightPlotDoubleSpinBox->setValue(1);
    ui->yLeftRangePlotDoubleSpinBox->setValue(-1);
    ui->yRangeRightPlotDoubleSpinBox->setValue(1);
}

void MainWindow::on_plusButton_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("+"));
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
}

void MainWindow::on_minusButton_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("-"));
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
}

void MainWindow::on_multiplyButton_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("*"));
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("/"));
    ui->enterFunctionToCalculateValueTextEdit->moveCursor(QTextCursor::End);
}

void MainWindow::on_sinButton_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("sin("));



}

void MainWindow::on_cosButton_clicked()
{
     ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("cos("));
}

void MainWindow::on_tanButton_clicked()
{
     ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("tan("));
}

void MainWindow::on_pushButton_6_clicked()
{
     ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("ctan("));
}

void MainWindow::on_leftBracketButton_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("("));
}

void MainWindow::on_rightBracketButton_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString(")"));
}

void MainWindow::on_pushButton_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("^"));
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("exp("));
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("ln("));
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("log("));
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString(","));
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("abs("));
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("^2"));
}

void MainWindow::on_clearCommonCalculatorButton_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->clear();
    ui->outputTextEdit->clear();
}

void MainWindow::on_deleteCharacterButton_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->textCursor().deletePreviousChar();
}

void MainWindow::on_pushButton_10_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("sqrt("));
}

void MainWindow::on_asinButton_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("asin("));
}

void MainWindow::on_pushButton_11_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("acos("));
}

void MainWindow::on_pushButton_12_clicked()
{
    ui->enterFunctionToCalculateValueTextEdit->insertPlainText(QString("atan("));
}

void MainWindow::on_goToGeometryButton_clicked()
{
    ui->stackedWidgets->setCurrentWidget(ui->geometryPage);

}

void MainWindow::on_goToMainPageFromGeometryButton_clicked()
{
    ui->stackedWidgets->setCurrentWidget(ui->mainPage);
}

void MainWindow::on_triangleButton_clicked()
{

}

void MainWindow::on_circleButton_clicked()
{
    QWidget *w = new QWidget(this);
    QHBoxLayout *horizontalLayout = new QHBoxLayout(w);
    horizontalLayout->setSpacing(30);
    horizontalLayout->setObjectName("radiusHorizontalLayout");


    QLabel *message = new QLabel("enter radius:");
    horizontalLayout->addWidget(message);
    QLineEdit *lineEdit = new QLineEdit();
    lineEdit->setObjectName("enterRadiusCircleLineEdit");
    horizontalLayout->addWidget(lineEdit);


    //connect(okButton, &QPushButton::clicked, this, &MainWindow::okButtonClickedCircle);

    ui->verticalGeometryLayout->addWidget(w);

    QWidget *w1 = new QWidget(this);

    QHBoxLayout *horizontalLayout1 = new QHBoxLayout(w1);

    QPushButton *areaButton = new QPushButton("area");
    areaButton->setObjectName("areaCircleButton");
    areaButton->setCursor(QCursor(Qt::PointingHandCursor));
    areaButton->setFixedSize(QSize(151, 25));
    connect(areaButton, &QPushButton::clicked, this, &MainWindow::calculateAreaCircleButton_clicked);
    horizontalLayout1->addWidget(areaButton);

    QPushButton *circumferenceButton = new QPushButton("circumference");
    circumferenceButton->setObjectName("circumferenceCircleButton");
    circumferenceButton->setCursor(QCursor(Qt::PointingHandCursor));
    circumferenceButton->setFixedSize(QSize(151, 25));
    connect(circumferenceButton, &QPushButton::clicked, this, &MainWindow::calculatecircumferenceCircleButton_clicked);
    horizontalLayout1->addWidget(circumferenceButton);

    ui->verticalGeometryLayout->addWidget(w1);

    QWidget *w2 = new QWidget(this);

    QHBoxLayout *horizontalLayout2 = new QHBoxLayout(w2);

    QLabel *resultMessage = new QLabel("result:");
    resultMessage->setContentsMargins(0, 0, 0, 0);
    horizontalLayout2->addWidget(resultMessage);

    QLineEdit *resultCircleLineEdit = new QLineEdit();
    resultCircleLineEdit->setObjectName("resultCircleLineEdit");
    resultCircleLineEdit->setReadOnly(true);
    horizontalLayout2->addWidget(resultCircleLineEdit);

    ui->verticalGeometryLayout->addWidget(w2);

    QWidget *w3 = new QWidget(this);

    QHBoxLayout *horizontalLayout3 = new QHBoxLayout(w3);

    QPushButton *clearButton = new QPushButton("clear");
    clearButton->setFixedSize(QSize(151, 25));
    clearButton->setObjectName("clearCircleButton");
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::clearCircleButton_clicked);
    horizontalLayout3->addWidget(clearButton);

    ui->verticalGeometryLayout->addWidget(w3);

}

void MainWindow::calculateAreaCircleButton_clicked() {
    QLineEdit *enter = ui->geometryPage->findChild<QLineEdit*>("enterRadiusCircleLineEdit");

    if (enter == nullptr) {
        exit(1);
    }

    QLineEdit *result = ui->geometryPage->findChild<QLineEdit*>("resultCircleLineEdit");

    if (result == nullptr) {
        exit(1);
    }

    bool ok;
    double radius = enter->text().toDouble(&ok);

    if (!ok) {
        result->setText("radius is not valid");
    }
    else {
        result->setText(QString::number(radius*radius*M_PI));
    }






}

void MainWindow::calculatecircumferenceCircleButton_clicked() {
    QLineEdit *enter = ui->geometryPage->findChild<QLineEdit*>("enterRadiusCircleLineEdit");

    if (enter == nullptr) {
        exit(1);
    }

    QLineEdit *result = ui->geometryPage->findChild<QLineEdit*>("resultCircleLineEdit");

    if (result == nullptr) {
        exit(1);
    }

    bool ok;
    double radius = enter->text().toDouble(&ok);

    if (!ok) {
        result->setText("radius is not valid");
    }
    else {
        result->setText(QString::number(2*radius*M_PI));
    }
}

void MainWindow::clearCircleButton_clicked() {
    QLineEdit *enter = ui->geometryPage->findChild<QLineEdit*>("enterRadiusCircleLineEdit");

    if (enter == nullptr) {
        exit(1);
    }

    enter->clear();

    QLineEdit *result = ui->geometryPage->findChild<QLineEdit*>("resultCircleLineEdit");

    if (result == nullptr) {
        exit(1);
    }

    result->clear();
}


