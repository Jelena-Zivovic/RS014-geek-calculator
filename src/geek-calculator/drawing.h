#ifndef DRAWING_H
#define DRAWING_H

#include <QWidget>
#include <

class Drawing : public QWidget
{
    Q_OBJECT

public:
    enum Shape{Polygon, Rect, Elipse, }

private slots:
    void shapeChanged();

private:

};

#endif // DRAWING_H
