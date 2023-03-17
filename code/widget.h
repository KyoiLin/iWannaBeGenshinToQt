#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QIcon>
#include <QPainter>
#include <QTimer>
#include <QPixmap>
#include <QSoundEffect>
#include <QFile>
#include <QMetaEnum>
#include <QDebug>
#include <QRectF>
#include <QKeyEvent>
#include "config.h"
#include "kid.h"
#include "movestate.h"
#include "floor.h"
#include "bullet.h"
#include "save.h"
#include "tppoint.h"
#include "zhongli.h"
#include "helper.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void InitScene();
    //游戏界面设置
    void voiceSet();
    //游戏音效设置
    void moveConnect();
    //kid、boss动作模型绑定
    void timerSet();
    //部分计时器设置
    void timerConnect();
    //计时器绑定
    void signalConnect();
    //信号绑定
    void gamestart();
    void paintEvent(QPaintEvent *);
    void collisionDetection();
    void drawMap1(QPainter &painter);
    void drawMap2(QPainter &painter);
    void drawMap3(QPainter &painter);
    void resetscene();
    //读档
    void map1tomap2();
    void gameclear();

    void gamestop();
    void gamecontinue();

public:
    bool gamestate;
    enum MapNum{map1 = 1, map2, map3}mapstate;
    Q_ENUM(MapNum)

    QSoundEffect *bgm;
    QSoundEffect *bgm2;
    QSoundEffect *deathbgm;
    QSoundEffect *clear;

    QPixmap map;
    QPixmap gameoverpic;
    QPixmap gameclearpic;

    QRect textrect;

    Floor f1;
    Save *s;
    TPPoint *tp;
    kid player;
    enum state{live = 1, die}kidstate;
    zhongli z;

    //QTimer gametimer;
    QTimer detect_timer;
    //游戏主计时器
    QTimer movetimer_r;
    QTimer movetimer_l;
    QTimer movetimer_up;
    QTimer movetimer_down;
    //QTimer deathtimer;
    //kid动态计时器
    //QTimer bullettimer[Bullet_Num];
    //QTimer bullettimer;
    QTimer z_timer;
    QTimer z_hittimer;
    //boss计时器

    int death_update;

    helper *h;

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

signals:
    void cdOver();

public slots:
//    void bulletget(int n){
//        //bullettimer[n].start();
//    }
    void cdTimeOut(){
    }
};

#endif // WIDGET_H
