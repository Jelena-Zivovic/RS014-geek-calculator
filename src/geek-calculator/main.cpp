#include "mainwindow.h"
#include <QScrollArea>
#include <mgl2/qmathgl.h>
#include <mgl2/mgl.h>

#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;




    w.show();
    return a.exec();
}
