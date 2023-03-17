#include "zhongli.h"
//#include <QTime>
//#include <QtGlobal>

zhongli::zhongli(QObject *parent) : QObject(parent)
{
    zhongli_hp.setWidth(Zhongli_HP_WIDTH);
    zhongli_hp.setHeight(Zhongli_HP_HEIGHT);
    zhongli_hp.moveTo(Zhongli_HP_POS);
    pic.load(Zhongli_PIC);
    crashrect.setSize(QSize(pic.width(), pic.height()));
    zx = -pic.width();
    zy = -pic.height();
    crashrect.moveTo(zx, zy);
    hp = Zhongli_HP;
    move_direction = up;
    //设置默认移动方向向下
    b_recorder = 0;
    //设置小蓝球发射间隔
    shoot_recorder = 0;
    is_gethit = false;
    getHitCd = Zhongli_HitInterval;
    //设置boss受击间隔
    blueball = new BlueBall [BLUEBALL_NUM];

    zhongli_in = new QSoundEffect(this);
    zhongli_in->setSource(QUrl::fromLocalFile(Zhongli_IN));
    zhongli_in->setLoopCount(1);
    zhongli_in->setVolume(0.5);
    zhongli_out = new QSoundEffect(this);
    zhongli_out->setSource(QUrl::fromLocalFile(Zhongli_OUT));
    zhongli_out->setLoopCount(1);
    zhongli_out->setVolume(0.9);
    zhongli_hit = new QSoundEffect(this);
    zhongli_hit->setSource(QUrl::fromLocalFile(Zhongli_HIT));
    zhongli_hit->setLoopCount(1);
    zhongli_hit->setVolume(1.0);
    //boss语音设置
}

void zhongli::move(const QRect &floor){
    if(this->crashrect.intersects(floor)) move_direction = up;
    if(this->crashrect.top() <= 0) move_direction = down;
    //方向检测
    switch (move_direction) {
    case up:
        zy -= Zhongli_SPEED;
        break;
    case down:
        zy += Zhongli_SPEED;
        break;
    default:
        break;
    }
}

void zhongli::updatepos(){
    crashrect.moveTo(zx, zy);
}

void zhongli::resetpos(){
    zx = -pic.width();
    zy = -pic.height();
    crashrect.moveTo(zx, zy);
}

void zhongli::backpos(){
    zx = GAME_WIDTH - crashrect.width();
    zy = 100;
    crashrect.moveTo(zx, zy);
}

bool zhongli::CollisionDetection(const QRect &bullet){
    if(this->crashrect.intersects(bullet) && is_gethit == false){
        hp--;
        is_gethit = true;
        int hpwidth = zhongli_hp.width() - 88;
        zhongli_hp.setWidth(hpwidth);
        qDebug() << "hp" << hp;
        emit gethit();
        if(hp == 0) emit hp_null();
        return true;
    }else return false;
}

void zhongli::resethp(){
    zhongli_hp.setWidth(Zhongli_HP_WIDTH);
}

void zhongli::attack1(int kidx, int kidy){
    b_recorder++;
    if(b_recorder < BLUEBALL_INTERVAL) return;
    b_recorder = 0;
    for(int i = 0; i < BLUEBALL_NUM; i++){
        if(!blueball[i].is_shoot){
            blueball[i].is_shoot = true;
            blueball[i].setpos(zx, zy);
            blueball[i].calculate_path(kidx, kidy);
            //计算发射路径
            break;
        }
    }
}

void zhongli::reset_blueball(){
    for(int i = 0; i < BLUEBALL_NUM; i++){
        blueball[i].reset_shootstate();
    }
}

void zhongli::reset_blueballpos(){
    for(int i = 0; i< BLUEBALL_NUM; i++){
        blueball[i].resetpos();
    }
}


void zhongli::attack2(int kidx, int kidy){
    pinkball.p_recorder++;
    if(pinkball.p_recorder < PINKBALL_INTERVAL) return;
    pinkball.p_recorder = 0;
    pinkball.is_shoot = true;
    pinkball.calculate_path(kidx, kidy);
}


void zhongli::reset_pinkball(){
    pinkball.is_move = false;
    pinkball.is_shoot = false;
}

void zhongli::reset_pinkballpos(){
    pinkball.resetpos();
}

void zhongli::setdie(){
    this->hp = 1;
}
