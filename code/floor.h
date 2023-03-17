#ifndef FLOOR_H
#define FLOOR_H

#include <QObject>
#include <QPixmap>
#include <QRect>
#include "config.h"

class Floor : public QObject
{
    Q_OBJECT
public:
    explicit Floor(QObject *parent = nullptr);

public:
    QPixmap f_pic;
    QRect f_crashrect;
    int f_x;
    int f_y;

signals:

public slots:
};

#endif // FLOOR_H
