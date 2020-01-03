#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Function.hpp"
#include "Matrix.hpp"
#include <QMessageBox>
#include <mgl2/eval.h>
#include <mgl2/data.h>
#include <QtMath>

#include <QtDataVisualization/Q3DSurface>
using namespace QtDataVisualization;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidgets->setCurrentWidget(ui->mainPage);
    ui->outputTextEdit->setReadOnly(true);
    configureFunctionPage();
    configureMatrixPage();
    create_q3dsurface();
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
    ui->widget->hide();
    ui->plotWidget->show();
}
void MainWindow::configureMatrixPage()
{
    ui->ARadioButton->setChecked(true);
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

    ui->check1radioButton->hide();
    ui->check2radioButton->hide();
    ui->enterLabel1->hide();
    ui->enter1LineEdit->hide();
    ui->enterLabel2->hide();
    ui->enter2LineEdit->hide();
    ui->enterLabel3->hide();
    ui->enter3LineEdit->hide();
    ui->enterLabel4->hide();
    ui->enter4LineEdit->hide();
    ui->resultGeomtryLabel->hide();
    ui->resultGeometryLineEdit->hide();
    ui->resultGeometryButton->hide();
    ui->clearGeomtryButton->hide();
    ui->resultGeometryLineEdit->setReadOnly(true);
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
    ui->stackedWidgets->setCurrentWidget(ui->functionsPage);
    on_oneVariablePlottingRadioButton_clicked();
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
            //Changes color of function
            QPen pen;
            pen.setWidth(1);
            int r = qrand()%255;
            int g = qrand()%255;
            int b = qrand()%255;
            pen.setColor(QColor(r,g,b));
            int i=0;
            if(ui->combineMultiplyPlotsCheckBox->isChecked()){
                i=ui->plotWidget->graphCount();
            }

            ui->plotWidget->addGraph();
            ui->plotWidget->graph(i)->setData(x, y);
            ui->plotWidget->graph(i)->setPen(pen);
            ui->plotWidget->xAxis->setRange(xLeft, xRight);
            ui->plotWidget->yAxis->setRange(yLeft, yRight);

            ui->plotWidget->replot();


        }
        else {
            QSurfaceDataProxy *dataProxy = new QSurfaceDataProxy();
            QSurface3DSeries *dataSeries = new QSurface3DSeries(dataProxy);

            double xLeft = ui->xRangeLeftPlotDoubleSpinBox->value();
            double xRight = ui->xRangeRightPlotDoubleSpinBox->value();

            if (xLeft >= xRight) {
                error_boxMsg("invalid range for x");
                return;
            }

            double yLeft = ui->yLeftRangePlotDoubleSpinBox->value();
            double yRight = ui->yRangeRightPlotDoubleSpinBox->value();

            if (yLeft >= yRight) {
                error_boxMsg("invalid range for y");
                return;
            }


            double zLeft = ui->zLeftRangePlotDoubleSpinBox->value();
            double zRight = ui->zRangeRightPlotDoubleSpinBox->value();

            if (zLeft >= zRight) {
                error_boxMsg("invalid range for z");
                return;
            }

            int sampleCountX = 50;
            int sampleCountZ = 50;
            //range for X and Z axis
            float sampleMinX = float(xLeft);
            float sampleMaxX = float(xRight);
            float sampleMinZ = float(zLeft);
            float sampleMaxZ= float(zRight);
            float stepX =(sampleMaxX-sampleMinX)/ float(sampleCountX - 1);
            float stepZ = (sampleMaxZ-sampleMinZ) / float(sampleCountZ - 1);

            //setting range for axis

            modifier->axisX()->setRange(sampleMinX, sampleMaxX);
            modifier->axisZ()->setRange(sampleMinZ, sampleMaxZ);
            modifier->axisY()->setRange(float(yLeft),float(yRight));


            mglFormula formula(function.get_string_function().toUtf8().constData());

            QSurfaceDataArray *dataArray = new QSurfaceDataArray;
            dataArray->reserve(sampleCountZ);


            for (int i = 0 ; i < sampleCountZ ; i++) {
                QSurfaceDataRow *newRow = new QSurfaceDataRow(sampleCountX);
                // Keep values within range bounds, since just adding step can cause minor drift due
                // to the rounding errors.
                float z = qMin(sampleMaxZ, (i * stepZ + sampleMinZ));
                int index = 0;
                for (int j = 0; j < sampleCountX; j++) {
                    float x = qMin(sampleMaxX, (j * stepX + sampleMinX));
                    float y = formula.Calc(x,z);

                    (*newRow)[index++].setPosition(QVector3D(x, y, z));

                }
                *dataArray << newRow;
            }
            //setting a new color for new function
            int r = qrand()%255;
            int g = qrand()%255;
            int b = qrand()%255;

            if(!ui->combineMultiplyPlotsCheckBox->isChecked())
            {
                QList<QSurface3DSeries *> series = modifier->seriesList();
                for(auto s : series){
                    modifier->removeSeries(s);
                }
            }


            dataProxy->resetArray(dataArray);
            modifier->addSeries(dataSeries);
            modifier->seriesList().back()->setBaseColor(QColor(r,g,b));


        }

    } catch (const char *message) {
        std::cout << message << std::endl;
    }

}

void MainWindow::create_q3dsurface(){
       graph = new Q3DSurface();
       graph->setAxisX(new QValue3DAxis);
       graph->setAxisY(new QValue3DAxis);
       graph->setAxisZ(new QValue3DAxis);
       QWidget *container = QWidget::createWindowContainer(graph);
       ui->hLayout->addWidget(container,1);
       Q3DSurface *tmp(graph);
       modifier = tmp;
       modifier->setAxisX(new QValue3DAxis);
       modifier->setAxisY(new QValue3DAxis);
       modifier->setAxisZ(new QValue3DAxis);
       modifier->axisX()->setLabelFormat("%.2f");
       modifier->axisZ()->setLabelFormat("%.2f");
}

void MainWindow::on_backPlotButton_clicked()
{
    ui->stackedWidgets->setCurrentWidget(ui->mainPage);
}

void MainWindow::on_clearPlotButton_clicked()
{
    ui->enterFunctionPlottingLineEdit->clear();
    ui->plotWidget->clearGraphs();
    ui->plotWidget->replot();
    /*
    if (ui->oneVariablePlottingRadioButton->isChecked()) {
        ui->xRangeLeftPlotDoubleSpinBox->setValue(0);
        ui->xRangeRightPlotDoubleSpinBox->setValue(1);
        ui->yLeftRangePlotDoubleSpinBox->setValue(0);
        ui->yRangeRightPlotDoubleSpinBox->setValue(1);
    }
    if (ui->twoVariablesPlottingRadioButton->isChecked()) {
        ui->xRangeLeftPlotDoubleSpinBox->setValue(-1);
        ui->xRangeRightPlotDoubleSpinBox->setValue(1);
        ui->yLeftRangePlotDoubleSpinBox->setValue(-1);
        ui->yRangeRightPlotDoubleSpinBox->setValue(1);
        ui->zLeftRangePlotDoubleSpinBox->setValue(-1);
        ui->zRangeRightPlotDoubleSpinBox->setValue(1);
    }*/
    QList<QSurface3DSeries *> series = modifier->seriesList();
    for(auto s : series){
        modifier->removeSeries(s);
    }

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

void MainWindow::on_oneVariablePlottingRadioButton_clicked()
{
    ui->widget->hide();
    ui->plotWidget->show();
    ui->zLabelRange->hide();
    ui->zLeftRangePlotDoubleSpinBox->hide();
    ui->zRangeRightPlotDoubleSpinBox->hide();
    ui->zFromLabel->hide();
    ui->zToLabel->hide();
    ui->xRangeLeftPlotDoubleSpinBox->setValue(0);
    ui->xRangeRightPlotDoubleSpinBox->setValue(1);
    ui->yLeftRangePlotDoubleSpinBox->setValue(0);
    ui->yRangeRightPlotDoubleSpinBox->setValue(1);
    ui->plotWidget->xAxis->setLabel("x");
    ui->plotWidget->yAxis->setLabel("y");
}

void MainWindow::on_twoVariablesPlottingRadioButton_clicked()
{
    ui->xRangeLeftPlotDoubleSpinBox->setValue(-1);
    ui->xRangeRightPlotDoubleSpinBox->setValue(1);
    ui->yLeftRangePlotDoubleSpinBox->setValue(-1);
    ui->yRangeRightPlotDoubleSpinBox->setValue(1);
    ui->zLeftRangePlotDoubleSpinBox->setValue(-1);
    ui->zRangeRightPlotDoubleSpinBox->setValue(1);

    ui->zFromLabel->show();
    ui->zToLabel->show();
    ui->zLabelRange->show();
    ui->zLeftRangePlotDoubleSpinBox->show();
    ui->zRangeRightPlotDoubleSpinBox->show();
    ui->plotWidget->hide();
    ui->widget->show();
}
void MainWindow::on_goToGeometryButton_clicked()
{
    clearLayout(ui->verticalGeometryLayout);
    ui->stackedWidgets->setCurrentWidget(ui->geometryPage);

}

void MainWindow::on_goToMainPageFromGeometryButton_clicked()
{
    ui->stackedWidgets->setCurrentWidget(ui->mainPage);
}


void MainWindow::clear_geometry_page(){
    on_clearGeomtryButton_clicked();
    ui->enterLabel1->hide();
    ui->enterLabel2->hide();
    ui->enterLabel3->hide();
    ui->enterLabel4->hide();
    ui->enter1LineEdit->hide();
    ui->enter2LineEdit->hide();
    ui->enter3LineEdit->hide();
    ui->enter4LineEdit->hide();

}
bool MainWindow::check_enter_geometry(int i){
    if(ui->enter1LineEdit->text().isNull()){
        return false;
    }
    if(i == 1)
        return true;
    if(ui->enter2LineEdit->text().isNull()){
        return false;
    }
    if(i == 2)
        return true;
    if(ui->enter3LineEdit->text().isNull()){
        return false;
    }
    if(i == 3)
        return true;
    if(ui->enter4LineEdit->text().isNull()){
        return false;
    }
    return true;
}

void MainWindow::on_circleButton_clicked()
{
    clear_geometry_page();
    ui->check1radioButton->setText("Circumreference");
    ui->check2radioButton->setText("Area");
    ui->check1radioButton->show();
    ui->check2radioButton->show();
    ui->resultGeomtryLabel->show();
    ui->resultGeometryButton->show();
    ui->resultGeometryLineEdit->show();
    ui->clearGeomtryButton->show();

    disconnect(ui->check1radioButton, 0, 0, 0);
    disconnect(ui->check2radioButton, 0, 0, 0);

    connect(ui->check1radioButton, &QPushButton::clicked, this, &MainWindow::circleCheck1RadioButton);
    connect(ui->check2radioButton, &QPushButton::clicked, this, &MainWindow::circleCheck2RadioButton);

    ui->check1radioButton->setChecked(true);
    circleCheck1RadioButton();
}
void MainWindow::circleCheck1RadioButton(){
    clear_geometry_page();
    ui->enterLabel1->setText("Radius ");
    ui->enterLabel1->show();
    ui->enter1LineEdit->show();
    ui->resultGeometryButton->setText("Result");

    disconnect(ui->resultGeometryButton, 0, 0, 0);
    connect(ui->resultGeometryButton, &QPushButton::clicked, this, &MainWindow::calculateCircumreferenceCircle);
}
void MainWindow::circleCheck2RadioButton(){
    clear_geometry_page();
    ui->enterLabel1->setText("Radius ");
    ui->enterLabel1->show();
    ui->enter1LineEdit->show();

    disconnect(ui->resultGeometryButton, 0, 0, 0);
    connect(ui->resultGeometryButton, &QPushButton::clicked, this, &MainWindow::calculateAreaCircle);

}
void MainWindow::calculateCircumreferenceCircle(){
    if(!check_enter_geometry(1)){
        error_boxMsg("Enter radisu");
        return;
    }
    QString radius = ui->enter1LineEdit->text();
    bool ok;
    double r = radius.toDouble(&ok);
    if(!ok){
        error_boxMsg("Radius must be a number");
        return;
    }
    double o = 2*r*M_PI;
    ui->resultGeometryLineEdit->setText(QString::number(o));
}
void MainWindow::calculateAreaCircle(){
    if(!check_enter_geometry(1)){
        error_boxMsg("Enter radisu");
        return;
    }
    QString radius = ui->enter1LineEdit->text();
    bool ok;
    double r = radius.toDouble(&ok);
    if(!ok){
        error_boxMsg("Radius must be a number");
        return;
    }
    double p = r*r*M_PI;
    ui->resultGeometryLineEdit->setText(QString::number(p));
}

void MainWindow::on_clearGeomtryButton_clicked()
{
    ui->enter1LineEdit->clear();
    ui->enter2LineEdit->clear();
    ui->enter3LineEdit->clear();
    ui->enter4LineEdit->clear();
    ui->resultGeometryLineEdit->clear();
}

void MainWindow::on_parallelogramButton_clicked()
{
    clear_geometry_page();
    ui->check1radioButton->setText("Circumreference");
    ui->check2radioButton->setText("Area");
    ui->check1radioButton->show();
    ui->check2radioButton->show();
    ui->resultGeomtryLabel->show();
    ui->resultGeometryButton->show();
    ui->resultGeometryLineEdit->show();
    ui->clearGeomtryButton->show();

    disconnect(ui->check1radioButton, 0, 0,0);
    disconnect(ui->check2radioButton, 0, 0,0);
    connect(ui->check1radioButton, &QPushButton::clicked, this, &MainWindow::parallelogramCheck1RadioButton);
    connect(ui->check2radioButton, &QPushButton::clicked, this, &MainWindow::parallelogramCheck2RadioButton);

    ui->check1radioButton->setChecked(true);
    parallelogramCheck1RadioButton();
}
void MainWindow::parallelogramCheck1RadioButton(){
    clear_geometry_page();
    ui->enterLabel1->setText("Side a");
    ui->enterLabel1->show();
    ui->enterLabel2->setText("Side b");
    ui->enterLabel2->show();
    ui->enter1LineEdit->show();
    ui->enter2LineEdit->show();

    disconnect(ui->resultGeometryButton,0,0,0);
    connect(ui->resultGeometryButton, &QPushButton::clicked, this, &MainWindow::calculateCircumreferenceParallelogram);

}
void MainWindow::parallelogramCheck2RadioButton(){
    clear_geometry_page();
    ui->enterLabel1->setText("Base");
    ui->enterLabel1->show();
    ui->enterLabel2->setText("Height");
    ui->enterLabel2->show();
    ui->enter1LineEdit->show();
    ui->enter2LineEdit->show();

    disconnect(ui->resultGeometryButton,0,0,0);
    connect(ui->resultGeometryButton, &QPushButton::clicked, this, &MainWindow::calculateAreaParallelogram);

}
void MainWindow::calculateCircumreferenceParallelogram(){
    if(!check_enter_geometry(2)){
        error_boxMsg("Enter sides");
        return;
    }
    QString A = ui->enter1LineEdit->text();
    bool ok;
    double a = A.toDouble(&ok);
    if(!ok){
        error_boxMsg("Side a must be a number");
        return;
    }
    QString B= ui->enter2LineEdit->text();
    double b = B.toDouble(&ok);
    if(!ok){
        error_boxMsg("Side b must be a number");
        return;
    }

    double o = (a+b)*2;
    ui->resultGeometryLineEdit->setText(QString::number(o));
}
void MainWindow::calculateAreaParallelogram(){
    if(!check_enter_geometry(2)){
        error_boxMsg("Enter base and height");
        return;
    }
    QString b = ui->enter1LineEdit->text();
    bool ok;
    double base = b.toDouble(&ok);
    if(!ok){
        error_boxMsg("Base a must be a number");
        return;
    }
    QString h = ui->enter2LineEdit->text();
    double height = h.toDouble(&ok);
    if(!ok){
        error_boxMsg("Height b must be a number");
        return;
    }

    double p = base*height;
    ui->resultGeometryLineEdit->setText(QString::number(p));
}


void MainWindow::on_rectangleButton_clicked()
{
    clear_geometry_page();
    ui->check1radioButton->setText("Circumreference");
    ui->check2radioButton->setText("Area");
    ui->check1radioButton->show();
    ui->check2radioButton->show();
    ui->resultGeomtryLabel->show();
    ui->resultGeometryButton->show();
    ui->resultGeometryLineEdit->show();
    ui->clearGeomtryButton->show();

    disconnect(ui->check1radioButton,0,0,0);
    disconnect(ui->check2radioButton,0,0,0);
    connect(ui->check1radioButton, &QPushButton::clicked, this, &MainWindow::parallelogramCheck1RadioButton);
    connect(ui->check2radioButton, &QPushButton::clicked, this, &MainWindow::parallelogramCheck2RadioButton);

    ui->check1radioButton->setChecked(true);
    parallelogramCheck1RadioButton();

}

void MainWindow::on_trapezoidButton_clicked()
{
    clear_geometry_page();
    ui->check1radioButton->setText("Circumreference");
    ui->check2radioButton->setText("Area");
    ui->check1radioButton->show();
    ui->check2radioButton->show();
    ui->resultGeomtryLabel->show();
    ui->resultGeometryButton->show();
    ui->resultGeometryLineEdit->show();
    ui->clearGeomtryButton->show();

    disconnect(ui->check1radioButton,0,0,0);
    disconnect(ui->check2radioButton,0,0,0);
    connect(ui->check1radioButton, &QPushButton::clicked, this, &MainWindow::trapezoidCheck1RadioButton);
    connect(ui->check2radioButton, &QPushButton::clicked, this, &MainWindow::trapezoidCheck2RadioButton);

    ui->check1radioButton->setChecked(true);
    trapezoidCheck1RadioButton();
}
void MainWindow::trapezoidCheck1RadioButton(){
    clear_geometry_page();
    ui->enterLabel1->setText("Base a");
    ui->enterLabel2->setText("Base b");
    ui->enterLabel3->setText("Side c");
    ui->enterLabel4->setText("Side d");
    ui->enterLabel1->show();
    ui->enterLabel2->show();
    ui->enterLabel3->show();
    ui->enterLabel4->show();
    ui->enter1LineEdit->show();
    ui->enter2LineEdit->show();
    ui->enter3LineEdit->show();
    ui->enter4LineEdit->show();

    disconnect(ui->resultGeometryButton, 0,0,0);
    connect(ui->resultGeometryButton, &QPushButton::clicked, this, &MainWindow::calculateTrapezoid);
}
void MainWindow::trapezoidCheck2RadioButton(){
    clear_geometry_page();
    ui->enterLabel1->setText("Base a");
    ui->enterLabel2->setText("Base b");
    ui->enterLabel3->setText("Height");
    ui->enterLabel1->show();
    ui->enterLabel2->show();
    ui->enterLabel3->show();
    ui->enter1LineEdit->show();
    ui->enter2LineEdit->show();
    ui->enter3LineEdit->show();

    disconnect(ui->resultGeometryButton,0,0,0);
    connect(ui->resultGeometryButton, &QPushButton::clicked, this, &MainWindow::calculateTrapezoid);
}
void MainWindow::calculateTrapezoid(){
    if(ui->check1radioButton->isChecked()){
        if(!check_enter_geometry(4)){
            error_boxMsg("Enter sides");{
                if(!check_enter_geometry(3)){
                    error_boxMsg("Enter sides");
                    return;
                 }
            }
            return;
         }
    }
    QString a_txt = ui->enter1LineEdit->text();
    bool ok;
    double a = a_txt.toDouble(&ok);
    if(!ok){
        error_boxMsg("Side a must be a number");
        return;
    }
    QString b_txt = ui->enter2LineEdit->text();
    double b = b_txt.toDouble(&ok);
    if(!ok){
        error_boxMsg("Side b must be a number");
        return;
    }
    QString c_txt = ui->enter3LineEdit->text();
    double c = c_txt.toDouble(&ok);
    if(!ok){
        if(ui->check1radioButton->isChecked()){
            error_boxMsg("Side c must be a number");
        }
        else{
            error_boxMsg("Height must be a number");
        }
        return;
    }
    double d=0;
    if(ui->check1radioButton->isChecked()){
        QString D = ui->enter4LineEdit->text();
        d = D.toDouble(&ok);
        if(!ok){
            error_boxMsg("Side d must be a number");
            return;
        }
    }
    if(ui->check1radioButton->isChecked()){
        double o = a+b+c+d;
        ui->resultGeometryLineEdit->setText(QString::number(o));
    }else{
        double p = (a+b)*c/2;
        ui->resultGeometryLineEdit->setText(QString::number(p));
    }
}

void MainWindow::on_triangleButton_clicked()
{
    clear_geometry_page();
    ui->check1radioButton->setText("Circumreference");
    ui->check2radioButton->setText("Area");
    ui->check1radioButton->show();
    ui->check2radioButton->show();
    ui->resultGeomtryLabel->show();
    ui->resultGeometryButton->show();
    ui->resultGeometryLineEdit->show();
    ui->clearGeomtryButton->show();

    disconnect(ui->check1radioButton, 0,0,0);
    disconnect(ui->check2radioButton, 0,0,0);
    connect(ui->check1radioButton, &QPushButton::clicked, this, &MainWindow::triangleCheck12RadioButton);
    connect(ui->check2radioButton, &QPushButton::clicked, this, &MainWindow::triangleCheck12RadioButton);


    ui->check1radioButton->setChecked(true);
    triangleCheck12RadioButton();

}
void MainWindow::triangleCheck12RadioButton(){
    clear_geometry_page();
    ui->enterLabel1->setText("Side a");
    ui->enterLabel2->setText("Side b");
    ui->enterLabel3->setText("Side c");
    ui->enterLabel1->show();
    ui->enterLabel2->show();
    ui->enterLabel3->show();
    ui->enter1LineEdit->show();
    ui->enter2LineEdit->show();
    ui->enter3LineEdit->show();

    disconnect(ui->resultGeometryButton,0,0,0);
    connect(ui->resultGeometryButton, &QPushButton::clicked, this, &MainWindow::calculateTriangle);
}
void MainWindow::calculateTriangle(){

    if(!check_enter_geometry(3)){
        error_boxMsg("Enter sides");
        return;
     }

    QString A = ui->enter1LineEdit->text();
    bool ok;
    double a = A.toDouble(&ok);
    if(!ok){
        error_boxMsg("Side a must be a number");
        return;
    }
    QString B = ui->enter2LineEdit->text();
    double b = B.toDouble(&ok);
    if(!ok){
        error_boxMsg("Side b must be a number");
        return;
    }
    QString C = ui->enter3LineEdit->text();
    double c = C.toDouble(&ok);
    if(!ok){
        error_boxMsg("Side c must be a number");
        return;
    }
    double o = a+b+c;
    double s = o/2;
    double p = sqrt(s*(s-a)*(s-b)*(s-c));
    if(ui->check1radioButton->isChecked()){
        ui->resultGeometryLineEdit->setText(QString::number(o));
    }else{
        ui->resultGeometryLineEdit->setText(QString::number(p));

    }
}

void MainWindow::on_squareButton_clicked()
{
    clear_geometry_page();
    ui->check1radioButton->setText("Circumreference");
    ui->check2radioButton->setText("Area");
    ui->check1radioButton->show();
    ui->check2radioButton->show();
    ui->resultGeomtryLabel->show();
    ui->resultGeometryButton->show();
    ui->resultGeometryLineEdit->show();
    ui->clearGeomtryButton->show();


    disconnect(ui->check1radioButton, 0,0,0);
    disconnect(ui->check2radioButton, 0,0,0);
    connect(ui->check1radioButton, &QPushButton::clicked, this, &MainWindow::squareCheck12RadioButton);
    connect(ui->check2radioButton, &QPushButton::clicked, this, &MainWindow::squareCheck12RadioButton);


    ui->check1radioButton->setChecked(true);
    squareCheck12RadioButton();
}
void MainWindow::squareCheck12RadioButton(){
    clear_geometry_page();
    ui->enterLabel1->setText("Side a");
    ui->enterLabel1->show();
    ui->enter1LineEdit->show();

    disconnect(ui->resultGeometryButton,0,0,0);
    connect(ui->resultGeometryButton, &QPushButton::clicked, this, &MainWindow::calculateSquare);
}
void MainWindow::calculateSquare(){
    if(!check_enter_geometry(1)){
        error_boxMsg("Enter data");
        return;
    }
    QString a_txt = ui->enter1LineEdit->text();
    bool ok;
    double a = a_txt.toDouble(&ok);
    if(!ok){
        error_boxMsg("Enter side a");
        return;
    }
    double o = 4*a;
    double p = a*a;
    if(ui->check1radioButton->isChecked()){
        ui->resultGeometryLineEdit->setText(QString::number(o));
    }else{
        ui->resultGeometryLineEdit->setText(QString::number(p));

    }
}

void MainWindow::on_coneButton_clicked()
{
    clear_geometry_page();
    ui->check1radioButton->setText("Area");
    ui->check2radioButton->setText("Volume");
    ui->check1radioButton->show();
    ui->check2radioButton->show();
    ui->resultGeomtryLabel->show();
    ui->resultGeometryButton->show();
    ui->resultGeometryLineEdit->show();
    ui->clearGeomtryButton->show();


    disconnect(ui->check1radioButton, 0,0,0);
    disconnect(ui->check2radioButton, 0,0,0);
    connect(ui->check1radioButton, &QPushButton::clicked, this, &MainWindow::coneCheck12RadioButton);
    connect(ui->check2radioButton, &QPushButton::clicked, this, &MainWindow::coneCheck12RadioButton);


    ui->check1radioButton->setChecked(true);
    coneCheck12RadioButton();
}
void MainWindow::coneCheck12RadioButton(){
    clear_geometry_page();
    if(ui->check1radioButton->isChecked()){
        ui->enterLabel2->setText("Degenerate s");
    }else{
        ui->enterLabel2->setText("Height h");
    }
    ui->enterLabel2->show();
    ui->enter1LineEdit->show();
    ui->enterLabel1->setText("Radius r");
    ui->enterLabel1->show();
    ui->enter2LineEdit->show();

    disconnect(ui->resultGeometryButton,0,0,0);
    connect(ui->resultGeometryButton, &QPushButton::clicked, this, &MainWindow::calculateCone);
}
void MainWindow::calculateCone(){
    if(!check_enter_geometry(2)){
        error_boxMsg("Enter data");
        return;
    }
    QString r_txt = ui->enter1LineEdit->text();
    bool ok;
    double r = r_txt.toDouble(&ok);
    if(!ok){
        error_boxMsg("Enter radisu r");
        return;
    }
    QString sh_txt = ui->enter2LineEdit->text();
    double sh = sh_txt.toDouble(&ok);
    if(!ok){
        if(ui->check1radioButton->isChecked()){
         error_boxMsg("Enter degenerate s");
        }else{
         error_boxMsg("Enter height s");
        }
        return;
    }
    double p = M_PI * r *(r+sh);
    double v = r*r*M_PI * sh/3;
    if(ui->check1radioButton->isChecked()){
        ui->resultGeometryLineEdit->setText(QString::number(p));
    }else{
        ui->resultGeometryLineEdit->setText(QString::number(v));

    }
}


void MainWindow::on_cubeButton_clicked()
{
    clear_geometry_page();
    ui->check1radioButton->setText("Area");
    ui->check2radioButton->setText("Volume");
    ui->check1radioButton->show();
    ui->check2radioButton->show();
    ui->resultGeomtryLabel->show();
    ui->resultGeometryButton->show();
    ui->resultGeometryLineEdit->show();
    ui->clearGeomtryButton->show();


    disconnect(ui->check1radioButton, 0,0,0);
    disconnect(ui->check2radioButton, 0,0,0);
    connect(ui->check1radioButton, &QPushButton::clicked, this, &MainWindow::cubeCheck12RadioButton);
    connect(ui->check2radioButton, &QPushButton::clicked, this, &MainWindow::cubeCheck12RadioButton);


    ui->check1radioButton->setChecked(true);
    cubeCheck12RadioButton();
}
void MainWindow::cubeCheck12RadioButton(){
    clear_geometry_page();
    ui->enterLabel1->setText("Side a");
    ui->enterLabel1->show();
    ui->enter1LineEdit->show();

    disconnect(ui->resultGeometryButton,0,0,0);
    connect(ui->resultGeometryButton, &QPushButton::clicked, this, &MainWindow::calculateCube);
}
void MainWindow::calculateCube(){
    if(!check_enter_geometry(1)){
        error_boxMsg("Enter data");
        return;
    }
    QString a_txt = ui->enter1LineEdit->text();
    bool ok;
    double a = a_txt.toDouble(&ok);
    if(!ok){
        error_boxMsg("Enter side a");
        return;
    }

    double p = 6*a*a;
    double v = a*a*a;
    if(ui->check1radioButton->isChecked()){
        ui->resultGeometryLineEdit->setText(QString::number(p));
    }else{
        ui->resultGeometryLineEdit->setText(QString::number(v));

    }
}


void MainWindow::on_cylinderButton_clicked()
{
    clear_geometry_page();
    ui->check1radioButton->setText("Area");
    ui->check2radioButton->setText("Volume");
    ui->check1radioButton->show();
    ui->check2radioButton->show();
    ui->resultGeomtryLabel->show();
    ui->resultGeometryButton->show();
    ui->resultGeometryLineEdit->show();
    ui->clearGeomtryButton->show();


    disconnect(ui->check1radioButton, 0,0,0);
    disconnect(ui->check2radioButton, 0,0,0);
    connect(ui->check1radioButton, &QPushButton::clicked, this, &MainWindow::cylinderCheck12RadioButton);
    connect(ui->check2radioButton, &QPushButton::clicked, this, &MainWindow::cylinderCheck12RadioButton);


    ui->check1radioButton->setChecked(true);
    cylinderCheck12RadioButton();
}
void MainWindow::cylinderCheck12RadioButton(){
    clear_geometry_page();
    ui->enterLabel1->setText("Radius r");
    ui->enterLabel1->show();
    ui->enter1LineEdit->show();
    ui->enterLabel2->setText("Height h");
    ui->enterLabel2->show();
    ui->enter2LineEdit->show();

    disconnect(ui->resultGeometryButton,0,0,0);
    connect(ui->resultGeometryButton, &QPushButton::clicked, this, &MainWindow::calculateCylinder);
}
void MainWindow::calculateCylinder(){
    if(!check_enter_geometry(2)){
        error_boxMsg("Enter data");
        return;
    }
    QString r_txt = ui->enter1LineEdit->text();
    bool ok;
    double r = r_txt.toDouble(&ok);
    if(!ok){
        error_boxMsg("Enter radisu");
        return;
    }
    QString h_txt = ui->enter2LineEdit->text();
    double h = h_txt.toDouble(&ok);
    if(!ok){
        error_boxMsg("Enter height");
        return;
    }

    double p = 2*r*M_PI*(r+h);
    double v = r*r*h*M_PI;
    if(ui->check1radioButton->isChecked()){
        ui->resultGeometryLineEdit->setText(QString::number(p));
    }else{
        ui->resultGeometryLineEdit->setText(QString::number(v));

    }
}

void MainWindow::on_sphereButton_clicked()
{
    clear_geometry_page();
    ui->check1radioButton->setText("Area");
    ui->check2radioButton->setText("Volume");
    ui->check1radioButton->show();
    ui->check2radioButton->show();
    ui->resultGeomtryLabel->show();
    ui->resultGeometryButton->show();
    ui->resultGeometryLineEdit->show();
    ui->clearGeomtryButton->show();


    disconnect(ui->check1radioButton, 0,0,0);
    disconnect(ui->check2radioButton, 0,0,0);
    connect(ui->check1radioButton, &QPushButton::clicked, this, &MainWindow::sphereCheck12RadioButton);
    connect(ui->check2radioButton, &QPushButton::clicked, this, &MainWindow::sphereCheck12RadioButton);


    ui->check1radioButton->setChecked(true);
    sphereCheck12RadioButton();
}
void MainWindow::sphereCheck12RadioButton(){
    clear_geometry_page();
    ui->enterLabel1->setText("Radius r");
    ui->enterLabel1->show();
    ui->enter1LineEdit->show();

    disconnect(ui->resultGeometryButton,0,0,0);
    connect(ui->resultGeometryButton, &QPushButton::clicked, this, &MainWindow::calculateSphere);
}
void MainWindow::calculateSphere(){
    if(!check_enter_geometry(1)){
        error_boxMsg("Enter data");
        return;
    }
    QString r_txt = ui->enter1LineEdit->text();
    bool ok;
    double r = r_txt.toDouble(&ok);
    if(!ok){
        error_boxMsg("Enter radisu");
        return;
    }

    double p = 4*r*r*M_PI;
    double v = 4*(r*r*r*M_PI)/3;
    if(ui->check1radioButton->isChecked()){
        ui->resultGeometryLineEdit->setText(QString::number(p));
    }else{
        ui->resultGeometryLineEdit->setText(QString::number(v));

    }
}


