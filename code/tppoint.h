#ifndef TPPOINT_H
#define TPPOINT_H

#include "config.h"
#include <QObject>
#include <QPixmap>
#include <QRect>

class TPPoint : public QObject
{
    Q_OBJECT
public:
    explicit TPPoint(QObject *parent = nullptr);
    bool tp_CollisionDetection(const QRect &kidrect);
    //和kid的碰撞检测
    void resetpos();
    //隐藏图标，主要用于场景切换
    void backpos();
    //恢复初始坐标

public:
    QPixmap tp_pic;
    int tpx;
    int tpy;
    QRect tp_crashrect;

signals:
    void mapchange();

public slots:
};

#endif // TPPOINT_H
