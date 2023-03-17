#ifndef ZHONGLI_H
#define ZHONGLI_H

#include <QObject>
#include <QPixmap>
#include <QRectF>
#include <QRect>
#include <QDebug>
#include <QSoundEffect>
#include "config.h"
#include "ball.h"

class zhongli : public QObject
{
    Q_OBJECT
public:
    explicit zhongli(QObject *parent = nullptr);
    ~zhongli(){
        delete [] blueball;
    }

    void move(const QRect &floor);
    void updatepos();
    bool CollisionDetection(const QRect &bullet);
    //和kid子弹的碰撞检测
    void resethp();
    //重置血条
    void resetpos();
    //重置坐标
    void backpos();
    //重新初始化坐标

    void attack1(int kidx, int kidy);
    void reset_blueball();
    //重置所有小蓝球发射状态
    void reset_blueballpos();
    //重置所有小蓝球坐标

    void attack2(int kidx, int kidy);
    void reset_pinkball();
    void reset_pinkballpos();

    void setdie();
    //管理员操作，设计者是个屑打不过干脆把boss改成一血（）

public:
    QRect zhongli_hp;
    //血条
    QPixmap pic;
    int zx;
    int zy;
    QRect crashrect;
    int hp;
    bool is_gethit;
    int getHitCd;
    //受击间隔时间1s
    enum direction{up = 1, down}move_direction;
    BlueBall *blueball;
    PinkBall pinkball;
    int shoot_recorder;
    int b_recorder;
    //小蓝球发射间隔
    QSoundEffect *zhongli_in;
    QSoundEffect *zhongli_out;
    QSoundEffect *zhongli_hit;

signals:
    void gethit();
    void hp_null();
    void attack2end();

public slots:

};

#endif // ZHONGLI_H
