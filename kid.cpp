#include "kid.h"
#include "movestate.h"
#include <QDebug>
#include <QSound>
#include <list>

kid::kid()
{
    pic.load(Kid);
    jumpvoice1 = new QSoundEffect();
    jumpvoice1->setSource(QUrl::fromLocalFile(JUMP_SOUND));
    jumpvoice1->setLoopCount(1);
    jumpvoice1->setVolume(1.0);
    jumpvoice2 = new QSoundEffect();
    jumpvoice2->setSource(QUrl::fromLocalFile(JUMP_SOUND2));
    jumpvoice2->setLoopCount(1);
    jumpvoice2->setVolume(1.0);
    //设置跳跃音效
    shootvoice = new QSoundEffect(this);
    shootvoice->setSource(QUrl::fromLocalFile(SHOOT_SOUND));
    shootvoice->setLoopCount(1);
    shootvoice->setVolume(0.2);
    //设置射击音效
    deathvoice = new QSoundEffect(this);
    deathvoice->setSource(QUrl::fromLocalFile(DEATH_BGM));
    deathvoice->setLoopCount(1);
    deathvoice->setVolume(1.0);
    //设置死亡界面bgm
    state = new Standright();
    crashRect.setSize(QSize(pic.width(), pic.height()));
    this->ox = 300;
    this->oy = 600;
    crashRect.moveTo(ox, oy);
    jumppoint.setX(ox);
    jumppoint.setY(oy);
    this->jump_type = 0;
    MoveState::initMoveState(1, new Standleft());
    MoveState::initMoveState(2, state);
    MoveState::initMoveState(3, new Moveleft());
    MoveState::initMoveState(4, new Moveright());
    MoveState::initMoveState(5, new Jumpleft());
    MoveState::initMoveState(6, new Jumpright());
    MoveState::initMoveState(7, new Fallleft());
    MoveState::initMoveState(8, new Fallright());
    MoveState::initMoveState(9, new Jumpleftdouble());
    MoveState::initMoveState(10, new Jumprightdouble());
    MoveState::initMoveState(11, new Death());
    connect(this, &kid::getfloor, [=](){
        //qDebug() << "cao";
        state = state->backtostand();
    });
    connect(this, &kid::getmaxheight, [=](){
        //qDebug() << "gan";
        state = state->releaseShift();
    });
    ani_recorder = 0;
}

void kid::setposition(int x, int y){
    this->ox = x;
    this->oy = y;
}

void kid::setposition(QPoint p){
    this->ox = p.x();
    this->oy = p.y();
}

void kid::updatepos(){
    this->crashRect.moveTo(ox, oy);
}

void kid::move_r(){
    if(this->ox+this->crashRect.width() < GAME_WIDTH) this->ox += SPEED;
    //边界检测
}

void kid::move_l(){
    if(this->ox > 0) this->ox -= SPEED;
    //边界检测
}

void kid::move_up(){
    if(this->jumppoint.y() - this->oy <= MAX_JUMP_HEIGHT) this->oy -= JUMP;
    //最大高度检测
    else {
        qDebug() << "get max height";
        emit getmaxheight();
    }
}

void kid::move_fall(const QRect &floor){
    //qDebug() << floor;
    //qDebug() << "x" << ox << "y" << oy;
    if(!collision_floor(floor)) this->oy += SPEED;
    //边界检测
    else {
        jump_type = 0;
        qDebug() << "getfloor";
        emit getfloor();
    }
}

bool kid::collision_floor(const QRect &floor){
    return this->crashRect.intersects(floor);
}

void kid::shoot(){
    qDebug() << "shoot";
    for(int i = 0; i < Bullet_Num; i++){
        if(!b_list[i].state){
            b_list[i].state = true;
            b_list[i].direction = this->state->getdirection();
            if(b_list[i].direction){
                b_list[i].b_x = this->ox + this->crashRect.width();
            }else b_list[i].b_x = this->ox - this->crashRect.width() + 50;
            b_list[i].b_y = this->oy + this->crashRect.height()/3 + 3;
            emit bulletshoot(i);
            break;
        }
    }
}

void kid::resetbulletstate(){
    for(int i = 0; i < Bullet_Num; i++){
        b_list[i].resetstate();
    }
}

void kid::deathjudge(const QRect &r){
    if(this->crashRect.intersects(r)){
        this->state = state->getdeath();
        emit death();
    }
}
