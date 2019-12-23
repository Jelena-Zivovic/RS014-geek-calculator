#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <Matrix.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:


    void on_goToBasicCalculatorButton_clicked();

    void on_goToFunctionsButton_clicked();

    void on_goBackToMainPageButton_clicked();

    void on_goBackToMainPage2_clicked();



    void on_calculateValueButton_clicked();

    void on_integralValueFunction_clicked();


    void on_goToMatrixButton_clicked();


    void on_enterDimensionButtonA_clicked();



    void on_enterDimensionButtonB_clicked();

    void on_matrixPlusButton_clicked();

    void on_matrixMinusButton_clicked();

    void on_matrixMultiplyButton_clicked();

    void on_determinantButtonA_clicked();

    //void on_determinantButtonB_clicked();

    void on_inverseButtonA_clicked();

    //void on_inverseButtonB_clicked();

    void on_transposeButtonA_clicked();

    //void on_transposeButtonB_clicked();

    void on_multiplyByButtonA_clicked();

    //void on_multiplyByButtonB_clicked();

    void on_raisePowerButtonA_clicked();

    //void on_raisePowerButtonB_clicked();

    void on_goFromMatrixToMainPageButton_clicked();

    void on_twoVariablesRadioButton_clicked();

    void on_oneVariableRadioButton_clicked();

    void on_clearIntegralTabButton_clicked();

    void on_goBackToMainPageButton_3_clicked();

    void on_clearDerivativeButton_clicked();

    void on_calculateDerivativeButton_clicked();

    void on_number1Button_clicked();

    void on_dotButton_clicked();

    void on_number2Button_clicked();

    void on_number3Button_clicked();

    void on_number4Button_clicked();

    void on_number5Button_clicked();

    void on_number6Button_clicked();

    void on_number7Button_clicked();

    void on_number8Button_clicked();

    void on_number9Button_clicked();

    void on_number0Button_clicked();

    void on_enterMatrixButtonA_clicked();

    void on_enterMatrixButtonB_clicked();

    void on_addMatrixButton_clicked();

    void on_clearMatrixButton_clicked();

    void on_matrixRankButton_clicked();

    void on_LUDecompButton_clicked();

    void on_plotFunctionButton_clicked();



    void on_backPlotButton_clicked();

    void on_clearPlotButton_clicked();

    void on_plusButton_clicked();

    void on_minusButton_clicked();

    void on_multiplyButton_clicked();

    void on_pushButton_5_clicked();

    void on_sinButton_clicked();

    void on_cosButton_clicked();

    void on_tanButton_clicked();

    void on_pushButton_6_clicked();

    void on_leftBracketButton_clicked();

    void on_rightBracketButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_clearCommonCalculatorButton_clicked();

    void on_deleteCharacterButton_clicked();

private:
    Ui::MainWindow *ui;
    void configureFunctionPage();
    void configureMatrixPage();
    void error_boxMsg(QString error_msg);
    void read_matrix(int indicator);
    Matrix A;
    Matrix B;
};
#endif // MAINWINDOW_H
