#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QObject>
#include <QPixmap>
#include <QRect>
#include <QDebug>
#include "config.h"

class ball : public QObject
{
    Q_OBJECT
public:
    QPixmap pic;
    int bx;
    int by;
    QRect b_crashrect;
    enum movedirection{nostraight = 1, straight}direction;
    //防止计算k值时分母为零的情况
    bool is_shoot;
    //发射状态

protected:
    int k;
    int b;
    //路径参数

public:
    explicit ball(QObject *parent = nullptr);
    void setpos(int x, int y);
    void updatepos();
    virtual void calculate_path(const int kid_x, const int kid_y);
    virtual void move();
    void reset_shootstate();
    //重置发射状态
    void resetpos();
    //重置坐标

signals:

public slots:
};

class BlueBall : public ball
{

public:
    BlueBall():ball(){
        pic.load(BLUEBALL_PATH);
        bx = 0;
        by = 0;
        b_crashrect.setSize(QSize(pic.width(), pic.height()));
        direction = nostraight;
        //主要用来防止计算k值时分母为零的情况
        is_shoot = false;
    }


signals:

public slots:
};

#include <QTime>
#include <QtGlobal>

class PinkBall : public ball
{
public:
    bool is_move;
    int p_recorder;
    //发射间隔
    bool is_float;
    int p_repeat;
    int p_float;
    //悬停时间

    PinkBall():ball() {
        pic.load(PINKBALL_PATH);
        bx = 0;
        by = 0;
        b_crashrect.setSize(QSize(pic.width(), pic.height()));
        b_crashrect.moveTo(bx, by);
        direction = straight;
        is_shoot = false;
        is_move = false;
        p_recorder = 0;
        is_float = false;
        p_repeat = 0;
        p_float = 0;
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    }

    void calculate_path(const int kid_x, const int kid_y);
    void move();
};

#endif // BALL_H
