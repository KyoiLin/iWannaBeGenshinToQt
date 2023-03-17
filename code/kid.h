#ifndef KID_H
#define KID_H

#include <QObject>
#include <QRect>
#include <QTimer>
#include <QPoint>
#include <QSoundEffect>
#include "movestate.h"
#include "config.h"
#include "bullet.h"

class kid: public QObject
{
    Q_OBJECT
public:
    QPixmap pic;
    QRect crashRect;
    MoveState *state;
    int ox;
    int oy;
    QPoint jumppoint;
    int jump_type;
    //跳跃状态 0-非跳跃状态 1-一段跳 2-二段跳
    bullet b_list[Bullet_Num];
    QSoundEffect *jumpvoice1;
    QSoundEffect *jumpvoice2;
    QSoundEffect *shootvoice;
    QSoundEffect *deathvoice;
    int ani_recorder;


public:
    explicit kid();
    void updatepos();
    void setposition(int x, int y);
    void setposition(QPoint p);
    void move_r();
    void move_l();
    void move_up();
    void move_fall(const QRect &floor);
    bool collision_floor(const QRect& floor);
    void shoot();
    void deathjudge(const QRect &r);
    void resetbulletstate();

signals:
    void getfloor();
    void getmaxheight();
    void death();
    void bulletshoot(int n);

public slots:
};


#endif // KID_H
