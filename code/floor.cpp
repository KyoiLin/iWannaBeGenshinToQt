#include "floor.h"
#include <QDebug>

Floor::Floor(QObject *parent) : QObject(parent)
{
    f_pic.load(FLOOR1);
    f_crashrect.setSize(QSize(f_pic.width(), f_pic.height()));
    f_x = 0;
    f_y = 600 + f_pic.height()/2 + 19;
    f_crashrect.moveTo(f_x, f_y);
    //qDebug() << f_crashrect.top();
}
