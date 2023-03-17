#include "movestate.h"
#include <QDebug>
/*
statelist:
1 -- Standleft
2 -- Standright
3 -- Moveleft
4 -- Moveright
5 -- Jumpleft
6 -- Jumpright
7 -- Fallleft
8 -- Fallright
9 -- Jumpleftdouble
10 -- Jumprightdouble
11 -- Death
*/
int MoveState::jumptype = 0;

std::map<int, MoveState*> MoveState::statelist = std::map<int, MoveState*>();

void MoveState::initMoveState(int n, MoveState *state){
    statelist[n] = state;
}

MoveState* MoveState::getstate(int n){
    std::map<int, MoveState*>::iterator state_p = statelist.find(n);
    if(state_p == statelist.end()){
        qDebug() << "statelist can't find state.";
        exit(0);
    }
    return state_p->second;
}

MoveState::MoveState(QObject *parent):QObject(parent){
    nowState = true;
}

void MoveState::jumpchange(int n){
    jumptype = n;
}

//standleft
MoveState* Standleft::pressL(){
    return getstate(3);
}

MoveState* Standleft::pressR(){
    return getstate(4);
}

MoveState* Standleft:: pressShift(){
    jumpchange(1);
    return getstate(5);
}

//standright
MoveState* Standright::pressL(){
    return getstate(3);
}
MoveState* Standright::pressR(){
    return getstate(4);
}

MoveState* Standright::pressShift(){
    jumpchange(1);
    return getstate(6);
}

//moveleft
MoveState* Moveleft::pressL(){
    return this;
}

MoveState* Moveleft::pressR(){
    return getstate(4);
}

MoveState* Moveleft::releaseL(){
    return getstate(1);
}

MoveState* Moveleft::pressShift(){
    jumpchange(1);
    return getstate(5);
}

//moveright
MoveState* Moveright::pressR(){
    return this;
}

MoveState* Moveright::pressL(){
    return getstate(3);
}

MoveState* Moveright::releaseR(){
    return getstate(2);
}

MoveState* Moveright::pressShift(){
    jumpchange(1);
    return getstate(6);
}

//jumpleft
MoveState* Jumpleft::pressL(){
    return getstate(5);
}

MoveState* Jumpleft::pressR(){
    return getstate(6);
}

MoveState* Jumpleft::releaseL(){
    return getstate(5);
}

MoveState* Jumpleft::releaseShift(){
    return getstate(7);
}

//jumpright
MoveState* Jumpright::pressL(){
    return getstate(5);
}

MoveState* Jumpright::pressR(){
    return getstate(6);
}

MoveState* Jumpright::releaseR(){
    return getstate(6);
}

MoveState* Jumpright::releaseShift(){
    return getstate(8);
}

//fallleft
MoveState* Fallleft::pressR(){
    return getstate(8);
}

MoveState* Fallleft::pressShift(){
    if(jumptype == 1) {
        jumpchange(2);
        qDebug() << jumptype;
        return getstate(9);
    }
    else return this;
}

MoveState* Fallleft::backtostand(){
    jumpchange(0);
    return getstate(1);
}

//fallright
MoveState* Fallright::pressL(){
    return getstate(7);
}

MoveState* Fallright::pressShift(){
    if(jumptype == 1) {
        jumpchange(2);
        //qDebug() << jumptype;
        return getstate(10);
    }
    else return this;
}

MoveState* Fallright::backtostand(){
    jumpchange(0);
    return getstate(2);
}

//jumpleftdouble
MoveState* Jumpleftdouble::releaseShift(){
    return getstate(7);
}

//jumprightdouble
MoveState* Jumprightdouble::releaseShift(){
    return getstate(8);
}

//death
MoveState* Death::backtostand(){
    return getstate(11);
}
