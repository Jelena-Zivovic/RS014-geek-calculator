#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_commonCalculatorButton_clicked();

    void on_functionsButton_clicked();

    void on_backButtonCommonCalculator_clicked();

    void on_backButtonFunctions_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
