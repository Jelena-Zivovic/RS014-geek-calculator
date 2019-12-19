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
    void error_boxMsg(QString error_msg);
    void read_matrix(int indicator);
    Matrix A;
    Matrix B;


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

    void on_plusButton_clicked();

    void on_minusButton_clicked();

    void on_multiplyButton_clicked();


    void on_determinantButtonA_clicked();

    void on_determinantButtonB_clicked();

    void on_inverseButtonA_clicked();

    void on_inverseButtonB_clicked();

    void on_transposeButtonA_clicked();

    void on_transposeButtonB_clicked();

    void on_multiplyByButtonA_clicked();

    void on_multiplyByButtonB_clicked();

    void on_raisePowerButtonA_clicked();

    void on_raisePowerButtonB_clicked();

    void on_goFromMatrixToMainPageButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
