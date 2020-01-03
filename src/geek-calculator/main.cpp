#include "mainwindow.h"
#include <QScrollArea>
#include <mgl2/qmathgl.h>
#include <mgl2/mgl.h>
#include <QTime>
#include <QApplication>

/*
#include <QtDataVisualization>
#include <QtDataVisualization/Q3DSurface>
#include <QtGui/QImage>
#include <QtCore/qmath.h>

using namespace QtDataVisualization;*/


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    qsrand(static_cast<unsigned>(QTime(0,0,0).secsTo(QTime::currentTime())));

    w.showFullScreen();

    //w.show();
    return a.exec();
}
