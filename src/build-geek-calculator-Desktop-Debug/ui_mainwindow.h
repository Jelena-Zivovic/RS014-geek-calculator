/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidgets;
    QWidget *mainPage;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalBoxMainPage;
    QPushButton *goToBasicCalculatorButton;
    QPushButton *goToFunctionsButton;
    QWidget *commonCalculatorPage;
    QPushButton *goBackToMainPageButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *enterFunctionToCalculateValueTextEdit;
    QPushButton *calculateValueButton;
    QTextEdit *outputTextEdit;
    QWidget *functionsPage;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *goBackToMainPage2;
    QLabel *enterFunctionLabel;
    QLineEdit *enteredFunctionLineEdit;
    QPushButton *integralValueFunction;
    QLineEdit *resultLineEdit;
    QLabel *resultLabel;
    QLineEdit *lowerBoundLineEdit;
    QLineEdit *upperBoundLineEdit;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidgets = new QStackedWidget(centralwidget);
        stackedWidgets->setObjectName(QString::fromUtf8("stackedWidgets"));
        stackedWidgets->setGeometry(QRect(100, 30, 521, 421));
        mainPage = new QWidget();
        mainPage->setObjectName(QString::fromUtf8("mainPage"));
        horizontalLayoutWidget = new QWidget(mainPage);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(50, 110, 381, 80));
        horizontalBoxMainPage = new QHBoxLayout(horizontalLayoutWidget);
        horizontalBoxMainPage->setObjectName(QString::fromUtf8("horizontalBoxMainPage"));
        horizontalBoxMainPage->setContentsMargins(0, 0, 0, 0);
        goToBasicCalculatorButton = new QPushButton(horizontalLayoutWidget);
        goToBasicCalculatorButton->setObjectName(QString::fromUtf8("goToBasicCalculatorButton"));

        horizontalBoxMainPage->addWidget(goToBasicCalculatorButton);

        goToFunctionsButton = new QPushButton(horizontalLayoutWidget);
        goToFunctionsButton->setObjectName(QString::fromUtf8("goToFunctionsButton"));

        horizontalBoxMainPage->addWidget(goToFunctionsButton);

        stackedWidgets->addWidget(mainPage);
        commonCalculatorPage = new QWidget();
        commonCalculatorPage->setObjectName(QString::fromUtf8("commonCalculatorPage"));
        goBackToMainPageButton = new QPushButton(commonCalculatorPage);
        goBackToMainPageButton->setObjectName(QString::fromUtf8("goBackToMainPageButton"));
        goBackToMainPageButton->setGeometry(QRect(190, 260, 89, 25));
        layoutWidget = new QWidget(commonCalculatorPage);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 0, 441, 179));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        enterFunctionToCalculateValueTextEdit = new QTextEdit(layoutWidget);
        enterFunctionToCalculateValueTextEdit->setObjectName(QString::fromUtf8("enterFunctionToCalculateValueTextEdit"));

        verticalLayout->addWidget(enterFunctionToCalculateValueTextEdit);

        calculateValueButton = new QPushButton(layoutWidget);
        calculateValueButton->setObjectName(QString::fromUtf8("calculateValueButton"));

        verticalLayout->addWidget(calculateValueButton);

        outputTextEdit = new QTextEdit(layoutWidget);
        outputTextEdit->setObjectName(QString::fromUtf8("outputTextEdit"));

        verticalLayout->addWidget(outputTextEdit);

        stackedWidgets->addWidget(commonCalculatorPage);
        functionsPage = new QWidget();
        functionsPage->setObjectName(QString::fromUtf8("functionsPage"));
        verticalLayoutWidget = new QWidget(functionsPage);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(220, 360, 82, 27));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        goBackToMainPage2 = new QPushButton(verticalLayoutWidget);
        goBackToMainPage2->setObjectName(QString::fromUtf8("goBackToMainPage2"));

        verticalLayout_2->addWidget(goBackToMainPage2);

        enterFunctionLabel = new QLabel(functionsPage);
        enterFunctionLabel->setObjectName(QString::fromUtf8("enterFunctionLabel"));
        enterFunctionLabel->setGeometry(QRect(180, 0, 201, 20));
        enterFunctionLabel->setMinimumSize(QSize(201, 0));
        enterFunctionLabel->setStyleSheet(QString::fromUtf8("text-align: right;"));
        enteredFunctionLineEdit = new QLineEdit(functionsPage);
        enteredFunctionLineEdit->setObjectName(QString::fromUtf8("enteredFunctionLineEdit"));
        enteredFunctionLineEdit->setGeometry(QRect(142, 20, 211, 25));
        integralValueFunction = new QPushButton(functionsPage);
        integralValueFunction->setObjectName(QString::fromUtf8("integralValueFunction"));
        integralValueFunction->setGeometry(QRect(220, 100, 89, 25));
        resultLineEdit = new QLineEdit(functionsPage);
        resultLineEdit->setObjectName(QString::fromUtf8("resultLineEdit"));
        resultLineEdit->setGeometry(QRect(230, 190, 171, 25));
        resultLabel = new QLabel(functionsPage);
        resultLabel->setObjectName(QString::fromUtf8("resultLabel"));
        resultLabel->setGeometry(QRect(130, 190, 67, 17));
        lowerBoundLineEdit = new QLineEdit(functionsPage);
        lowerBoundLineEdit->setObjectName(QString::fromUtf8("lowerBoundLineEdit"));
        lowerBoundLineEdit->setGeometry(QRect(150, 60, 113, 25));
        upperBoundLineEdit = new QLineEdit(functionsPage);
        upperBoundLineEdit->setObjectName(QString::fromUtf8("upperBoundLineEdit"));
        upperBoundLineEdit->setGeometry(QRect(390, 60, 113, 25));
        label = new QLabel(functionsPage);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 60, 111, 20));
        label_2 = new QLabel(functionsPage);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(290, 60, 91, 17));
        stackedWidgets->addWidget(functionsPage);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidgets->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        goToBasicCalculatorButton->setText(QApplication::translate("MainWindow", "basic", nullptr));
        goToFunctionsButton->setText(QApplication::translate("MainWindow", "functions", nullptr));
        goBackToMainPageButton->setText(QApplication::translate("MainWindow", "back", nullptr));
        calculateValueButton->setText(QApplication::translate("MainWindow", "calculate value", nullptr));
        goBackToMainPage2->setText(QApplication::translate("MainWindow", "back", nullptr));
        enterFunctionLabel->setText(QApplication::translate("MainWindow", "Enter function below:", nullptr));
        integralValueFunction->setText(QApplication::translate("MainWindow", "integral", nullptr));
        resultLabel->setText(QApplication::translate("MainWindow", "result:", nullptr));
        label->setText(QApplication::translate("MainWindow", "lower bound:", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "upper bound:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
