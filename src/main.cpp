#include "mainwindow.h"
#include "parser.tab.hpp"
#include <QApplication>
#include <iostream>
#include "Function.hpp"

int main(int argc, char **argv){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    std::string func = "sin(cos(x))";

    try {
        Function f(func);
        std::cout << "valid function" << std::endl;
    } catch (const char **message) {
        std::cout << message << std::endl;
    }


    return a.exec();
    
    return 0;
}
