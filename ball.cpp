#include "ball.h"

ball::ball(QObject *parent) : QObject(parent)
{
    k = 0;
    b = 0;
}


void ball::setpos(int x, int y){
    bx = x;
    by = y;
}

void ball::updatepos(){
    b_crashrect.moveTo(bx, by);
}

void ball::reset_shootstate(){
    this->is_shoot = false;
}

void ball::resetpos(){
    bx = -pic.height();
    by = -pic.width();
    b_crashrect.moveTo(bx, by);
}

void ball::calculate_path(const int kid_x, const int kid_y){
    if(kid_x - this->bx == 0) {
        direction = straight;
        return;
    } else {
        direction = nostraight;
        k = (this->by - kid_y)/(this->bx - kid_x);
        if(k == 0) {
            this->bx = 600;
            this->by = 10;
            k = (this->by - kid_y)/(this->bx - kid_x);
        }
        b = kid_y - k*kid_x;
    }
    //qDebug() << "bk" << k << "bb" << b;
}

void ball::move(){
    switch (direction) {
    case straight:
        this->by += (BLUEBALL_SPEED-1);
        break;
    case nostraight:
        this->bx -= BLUEBALL_SPEED;
        this->by = k * this->bx + b;
        break;
    default:
        break;
    }
    if(this->bx < 0 || this->bx > GAME_WIDTH || this->by < 0 || this->by > GAME_HEIGHT)
        this->is_shoot = false;
    //边界检测，飞出边界时切换发射状态
}

void PinkBall::calculate_path(const int kid_x, const int kid_y){
    this->bx = rand() % PINKBALL_RANGE_X_MAX;
    this->by = 28;
    direction = straight;
    setpos(bx, by);
    updatepos();
}

void PinkBall::move(){
    by += PINKBALL_SPEED;
    if(by >= GAME_HEIGHT) {
        is_shoot = false;
        is_move = false;
    }
}
