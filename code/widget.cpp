#include "widget.h"
#include <QSound>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    s = new Save;
    tp = new TPPoint;
    gameoverpic.load(GAME_OVER);
    gameclearpic.load(GAME_CLEAR);
    death_update = 0;
    kidstate = live;
    //设置kid初始状态为live
    mapstate = map1;
    //载入第一个地图

    voiceSet();
    moveConnect();
    timerSet();
    timerConnect();
    signalConnect();
    InitScene();
    gamestart();
}

Widget::~Widget()
{
    //gametimer.stop();
    detect_timer.stop();
    if(z_timer.isActive()) z_timer.stop();
    delete bgm;
    delete bgm2;
    delete deathbgm;
    delete clear;
}

void Widget::voiceSet(){
    bgm = new QSoundEffect(this);
    bgm->setSource(QUrl::fromLocalFile(GAME_BGM1));
    bgm->setLoopCount(QSoundEffect::Infinite);
    bgm->setVolume(0.7);
    bgm2 = new QSoundEffect(this);
    bgm2->setSource(QUrl::fromLocalFile(GAME_BGM2));
    bgm2->setLoopCount(QSoundEffect::Infinite);
    bgm2->setVolume(0.7);
    //设置游戏bgm
    deathbgm = new QSoundEffect(this);
    deathbgm->setSource(QUrl::fromLocalFile(GAME_OVER_BGM));
    deathbgm->setLoopCount(1);
    deathbgm->setVolume(0.9);
    //设置gameover界面bgm
    clear = new QSoundEffect(this);
    clear->setSource(QUrl::fromLocalFile(GAME_CLEAR_BGM));
    clear->setLoopCount(1);
    clear->setVolume(0.5);
    //gameclearBGM
}

void Widget::moveConnect(){
    connect(&movetimer_r, &QTimer::timeout, [=](){
        player.move_r();
        player.updatepos();
        update();
        //qDebug() << "x" << player.ox;
    });
    connect(&movetimer_l, &QTimer::timeout, [=](){
        player.move_l();
        player.updatepos();
        update();
        //qDebug() << "x" << player.ox;
    });
    connect(&movetimer_up, &QTimer::timeout, [=](){
        player.move_up();
        player.updatepos();
        update();
        //qDebug() << "y" << player.oy;
    });
    connect(&movetimer_down, &QTimer::timeout, [=](){
        player.move_fall(f1.f_crashrect);
        player.updatepos();
        update();
        //qDebug() << "y" << player.oy;
    });
    connect(&player, &kid::getfloor, &movetimer_down, &QTimer::stop);
    connect(&player, &kid::getmaxheight, [=](){
        movetimer_up.stop();
        movetimer_down.start();
    });
    //实现kid各种动作的动态以及移动
    connect(&z_timer, &QTimer::timeout, [=](){
        z.move(f1.f_crashrect);
        z.updatepos();
        update(z.crashrect);
        repaint(z.zhongli_hp);
        if(kidstate == live){
            z.attack1(player.ox, player.oy);
            for(int i = 0; i < BLUEBALL_NUM; i++){
                if(z.blueball[i].is_shoot){
                    z.blueball[i].move();
                    z.blueball[i].updatepos();
                    update(z.blueball[i].b_crashrect);
                }
            }
            z.attack2(player.ox, player.oy);
            if(z.pinkball.is_shoot && z.pinkball.is_move){
                z.pinkball.move();
                z.pinkball.updatepos();
                update(z.pinkball.b_crashrect);
            }
        }
        if(kidstate == die) {
            death_update++;
            if(death_update == ANI_INTERVAL){
                death_update = 0;
                update(player.crashRect);
            }
        }
    });
    //boss移动及技能释放
}

void Widget::timerSet(){
    movetimer_down.setInterval(GAME_RATE);
    //gametimer.setInterval(ANI_RATE);
    detect_timer.setInterval(OBJECT_RATE);
    //bullettimer.setInterval(OBJECT_RATE);
    //deathtimer.setInterval(ANI_RATE);
    z_hittimer.setInterval(Zhongli_GetHitCd);
}

void Widget::timerConnect(){
    //detect_timer绑定
    connect(&detect_timer, &QTimer::timeout, [=](){
        if(kidstate == live)
            collisionDetection();
        //实时进行碰撞检测
        for(int i = 0; i < Bullet_Num; i++){
            player.b_list[i].posdetect();
            if(player.b_list[i].state)
                player.b_list[i].updateBulletPos();
        }
        //kid子弹刷新
        update();
    });
//    //deathtimer绑定
//    //这里与gametimer的区别在于死亡时不再刷新碰撞体积检测，只实现死亡的角色动画
//    connect(&deathtimer, &QTimer::timeout, [=](){
//        update(player.crashRect);
//    });
    //ZhongliHitTimer绑定
    connect(&z_hittimer, &QTimer::timeout, [=](){
        z.getHitCd--;
        if(z.getHitCd == 0){
            z.is_gethit = false;
            z.getHitCd = Zhongli_HitInterval;
            //结束受击cd重置受击状态
            emit cdOver();
        }
    });
}

void Widget::signalConnect(){
    //kid死亡信号绑定
    connect(&player, &kid::death, [=](){
        //gametimer.stop();
        detect_timer.stop();
        z.reset_blueballpos();
        z.reset_blueball();
        z.reset_pinkball();
        z.reset_pinkballpos();
        //清除攻击
        //deathtimer.start();
        kidstate = die;
        if(bgm->isPlaying()) bgm->stop();
        if(bgm2->isPlaying()) bgm2->stop();
        player.deathvoice->play();
        deathbgm->play();
        update();
    });
    //传送点信号绑定，实现场景bgm转换
    connect(tp, &TPPoint::mapchange, [=](){
        bgm->stop();
        bgm2->play();
    });
    //gameclear信号绑定(boss血量为零)
    connect(&z, &zhongli::hp_null, [=](){
        z.zhongli_out->play();
        clear->play();
        bgm2->stop();
        gameclear();
    });
    //boss受击信号绑定
    connect(&z, &zhongli::gethit, [=](){
        qDebug() << "gethit";
        z_hittimer.start();
        z.zhongli_hit->play();
    });
    connect(this, &Widget::cdOver, [=](){
        z_hittimer.stop();
    });
    //存档点信号绑定
    connect(s, &Save::save, [=](){
        s->savevoice->play();
    });
}

void Widget::InitScene(){
    map.load(GAME_MAP);
    setFixedSize(GAME_WIDTH, GAME_HEIGHT);
    setWindowTitle(GAME_TITLE);
    setWindowIcon(QIcon(GAME_ICON));
    bgm->play();
    textrect.setSize(QSize(540, 120));
    textrect.moveTo(270, 120);
    //游戏场景设置
}

void Widget::gamestart(){
    gamestate = true;
    //gametimer.start();
    //游戏动画计时开始
    detect_timer.start();
    //碰撞检测开始
    //bullettimer.start();
}

void Widget::gamestop(){
    gamestate = false;
    switch (mapstate) {
    case map1:
        //gametimer.stop();
        detect_timer.stop();
        bgm->stop();
        break;
    case map2:
        //gametimer.stop();
        detect_timer.stop();
        bgm2->stop();
        z_timer.stop();
        break;
    default:
        break;
    }
}

void Widget::gamecontinue(){
    gamestate = true;
    switch (mapstate){
    case map1:
        //gametimer.start();
        detect_timer.start();
        bgm->play();
        break;
    case map2:
        //gametimer.start();
        detect_timer.start();
        bgm2->play();
        z_timer.start();
        break;
    default:
        break;
    }
}

void Widget::drawMap1(QPainter &painter){
    QFont font = painter.font();
    font.setPixelSize(25);
    painter.setFont(font);
    painter.drawText(rect(), Qt::AlignCenter, "方向键控制kid左右移动 shift跳跃 z射击 h打开帮助界面 esc退出");
    if(!s->save_state) painter.drawPixmap(s->s_crashrect.topLeft(), s->s_pic1);
    else{
        painter.drawPixmap(s->s_crashrect.topLeft(), s->s_pic2);
        s->time++;
        if(s->time == SAVE_TIME){
            s->save_state = false;
            s->time = 0;
        }
    }
    //绘制存档点
    painter.drawPixmap(tp->tp_crashrect.topLeft(), tp->tp_pic);
    //绘制传送点
}
//绘制map1

void Widget::drawMap2(QPainter &painter){
    painter.drawPixmap(z.crashrect.topLeft(), z.pic);
    //绘制boss
    painter.drawRect(z.zhongli_hp);
    painter.fillRect(z.zhongli_hp, Qt::red);
    painter.drawRect(HP_X, HP_Y, Zhongli_HP_WIDTH, Zhongli_HP_HEIGHT);
    for(int i = 0; i < BLUEBALL_NUM; i++){
        if(z.blueball[i].is_shoot)
            painter.drawPixmap(z.blueball[i].b_crashrect.topLeft(), z.blueball[i].pic);
    }
    //绘制boss技能1
    if(z.pinkball.is_shoot && !z.pinkball.is_move){
        z.pinkball.p_float++;
        z.pinkball.p_repeat++;
        if(z.pinkball.p_repeat >= PINKBALL_FLOAT_RATE){
            z.pinkball.p_repeat = 0;
            z.pinkball.is_float = !z.pinkball.is_float;
        }
        if(!z.pinkball.is_float){
            painter.drawPixmap(z.pinkball.b_crashrect.topLeft(), z.pinkball.pic);
            if(z.pinkball.p_float >= PINKBALL_FLOAT){
                z.pinkball.p_float = 0;
                z.pinkball.is_move = true;
            }
        }
    }
    if(z.pinkball.is_shoot && z.pinkball.is_move){
        z.pinkball.is_float = false;
        painter.drawPixmap(z.pinkball.b_crashrect.topLeft(), z.pinkball.pic);
    }
    //绘制boss技能2
}
//绘制map2

void Widget::drawMap3(QPainter &painter){
    painter.drawPixmap(rect(), gameclearpic, QRect());
}
//绘制map3，gameclear

void Widget::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(rect(), map, QRect());
    //绘制游戏背景
    painter.drawPixmap(f1.f_x, f1.f_y, f1.f_pic);
    //绘制游戏地面
    if(this->kidstate == die)
        painter.drawPixmap(rect(), gameoverpic, QRect());
    //kid死亡时绘制死亡提示
    switch (this->mapstate) {
    case map1:
        drawMap1(painter);
        break;
    case map2:
        drawMap2(painter);
        break;
    case map3:
        drawMap3(painter);
        break;
    default:
        break;
    }
    //绘制不同的游戏场景
    if(player.state->nowState){
        painter.drawPixmap(player.crashRect.topLeft(), player.state->pic1);
        player.ani_recorder++;
        if(player.ani_recorder == ANI_INTERVAL){
            player.ani_recorder = 0;
            player.state->nowState = !player.state->nowState;
        }
    }else{
        painter.drawPixmap(player.crashRect.topLeft(), player.state->pic2);
        player.ani_recorder++;
        if(player.ani_recorder == ANI_INTERVAL){
            player.ani_recorder = 0;
            player.state->nowState = !player.state->nowState;
        }
    }
    //实现角色动画
    for(int i = 0; i < Bullet_Num; i++){
        if(player.b_list[i].state)
                painter.drawPixmap(player.b_list[i].b_x, player.b_list[i].b_y,
                                   player.b_list[i].b_pic);
    }
    //绘制子弹
}

void Widget::gameclear(){
    this->mapstate = map3;
    z_timer.stop();
    z.resetpos();
    z.reset_blueballpos();
    z.reset_blueball();
    z.reset_pinkball();
    z.reset_pinkballpos();
    update();
}

void Widget::map1tomap2(){
    z_timer.start(Zhongli_RATE);
    //zhongli_in->play();
    s->resetpos();
    tp->resetpos();
    z.backpos();
    this->mapstate = map2;
    player.setposition(50, 600);
    player.updatepos();
    update();
}

void Widget::resetscene(){
    if(deathbgm->isPlaying()) deathbgm->stop();
    if(player.deathvoice->isPlaying()) player.deathvoice->stop();
    bgm->play();
    //重置bgm
    //deathtimer.stop();
    if(z_timer.isActive()) z_timer.stop();
    //gametimer.start();
    detect_timer.start();
    //重置计时器
    mapstate = map1;
    kidstate = live;
    s->backpos();
    tp->backpos();
    z.resetpos();
    z.reset_blueball();
    z.reset_blueballpos();
    z.reset_pinkball();
    z.reset_pinkballpos();
    z.hp = Zhongli_HP;
    z.resethp();
    //重置boss血量
    player.resetbulletstate();
    player.state = player.state->resetstate();
    player.setposition(s->readsave());
    player.updatepos();
    if(!player.collision_floor(f1.f_crashrect)){
        player.state = player.state->setstate_fall();
        movetimer_down.start();
    }
    update();
}

void Widget::collisionDetection(){
//    if(!player.collision_floor(f1.f_crashrect)){
//        player.state = player.state->setstate_fall();
//    }
    if(tp->tp_CollisionDetection(player.crashRect)){
        map1tomap2();
    }
    //kid和传送点的碰撞体积检测
    for(int i = 0; i < Bullet_Num; i++){
        if(player.b_list[i].state){
            s->getsave(player.b_list[i].b_crashrect, player.ox, player.oy);
            if(z.CollisionDetection(player.b_list[i].b_crashrect)){
                player.b_list[i].state = false;
            }
        }
    }
    //kid子弹的碰撞体积检测
    for(int j = 0; j < BLUEBALL_NUM; j++){
        if(z.blueball[j].is_shoot){
            player.deathjudge(z.blueball[j].b_crashrect);
        }
    }
    player.deathjudge(z.pinkball.b_crashrect);
    player.deathjudge(z.crashrect);
    //kid和boss的碰撞体积检测
}

void Widget::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Right:
        if(!event->isAutoRepeat()){
            if(kidstate == live) movetimer_r.start(GAME_RATE);
            player.state = player.state->pressR();
        }
            //qDebug() << 'R';
        break;
    case Qt::Key_Left:
        //qDebug() << 'L';
        if(!event->isAutoRepeat()){
            if(kidstate == live) movetimer_l.start(GAME_RATE);
            player.state = player.state->pressL();
        }
        break;
    case Qt::Key_Shift:
        if(!event->isAutoRepeat()){
            if(kidstate == live && player.jump_type < 2){
                qDebug() << "jump type" << player.jump_type;
                switch (player.jump_type) {
                case 0:
                    player.jumpvoice1->play();
                    break;
                case 1:
                    player.jumpvoice2->play();
                    break;
                default:
                    break;
                }
                player.jump_type++;
                player.jumppoint.setX(player.ox);
                player.jumppoint.setY(player.oy);
                movetimer_up.start(GAME_RATE);
            }
            player.state = player.state->pressShift();
        }
        break;
    case Qt::Key_Z:{
        qDebug() << "Z";
        if(kidstate == live){
            player.shootvoice->play();
            player.shoot();
        }
        break;
    }
    case Qt::Key_R:
        qDebug() << "R";
        resetscene();
        break;
    case Qt::Key_Escape:
        qDebug() << "esc";
        this->close();
        break;
    case Qt::Key_Q:
        qDebug() << "作者选择开挂";
        z.setdie();
        break;
    case Qt::Key_H:{
        h = new helper;
        h->show();
        break;
    }
    case Qt::Key_S:
        if(gamestate) gamestop();
        else gamecontinue();
        break;
    default:
        break;
    }
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Right:
        if(!event->isAutoRepeat()){
            movetimer_r.stop();
            player.state = player.state->releaseR();
        }
        //qDebug() << 'R release';
        break;
    case Qt::Key_Left:
        //qDebug() << 'L release';
        if(!event->isAutoRepeat()){
            movetimer_l.stop();
            player.state = player.state->releaseL();
        }
        break;
    case Qt::Key_Shift:{
        if(!event->isAutoRepeat()){
            qDebug() << "shift";
            if(movetimer_up.isActive()) movetimer_up.stop();
            if(!movetimer_down.isActive()) movetimer_down.start();
            player.state = player.state->releaseShift();
        }
    }
    default:
        break;
    }
}
