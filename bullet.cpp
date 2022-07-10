#include "bullet.h"

bullet::bullet(QObject *parent) : QObject(parent)
{
    b_pic.load(BULLET_PIC);
    state = false;
    b_x = 0;
    b_y = 0;
    b_crashrect.setSize(QSize(b_pic.width(), b_pic.height()));
    b_crashrect.moveTo(b_x, b_y);
}

void bullet::updateBulletPos(){
    if(state == true){
        if(direction){
            b_x += Bullet_Speed;
            b_crashrect.moveTo(b_x, b_y);
            if(b_x >= GAME_WIDTH){
                state = false;
                emit out();
            }
        }else{
            b_x -= Bullet_Speed;
            b_crashrect.moveTo(b_x, b_y);
            if(b_x <= 0) {
                state = false;
                emit out();
            }
        }
    }else return;
}

void bullet::resetstate(){
    this->state = false;
    this->b_x = 0;
    this->b_y = 0;
    this->b_crashrect.moveTo(b_x, b_y);
}

void bullet::posdetect(){
    if(b_x < 0 || b_x > GAME_WIDTH || b_y < 0 || b_y > GAME_HEIGHT)
        state = false;
}
