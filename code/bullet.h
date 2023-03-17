#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QPixmap>
#include <QSoundEffect>
#include <QRect>
#include <QTimer>
#include "config.h"

class bullet : public QObject
{
    Q_OBJECT
public:
    explicit bullet(QObject *parent = nullptr);
    void updateBulletPos();
    void resetstate();
    void posdetect();

public:
    QPixmap b_pic;
    int b_x;
    int b_y;
    QRect  b_crashrect;
    bool state;
    //子弹状态false-未发射 true-发射
    bool direction;
    //发射方向direction false-left true-right

signals:
    void out();
public slots:
};

#endif // BULLET_H
