#ifndef MOVESTATE_H
#define MOVESTATE_H
#include <map>
#include <iostream>
#include <QPixmap>
#include <QPainter>
#include <string>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QObject>
#include "config.h"


class MoveState : public QObject
{
    Q_OBJECT
public:
    static std::map<int, MoveState*> statelist;
    static void initMoveState(int n, MoveState *state);
    static MoveState* getstate(int n);
    //实现状态变换
    static void jumpchange(int n);

    explicit MoveState(QObject *parent = nullptr);

    virtual MoveState* pressR(){return this;}
    virtual MoveState* releaseR(){return this;}
    virtual MoveState* pressL(){return this;}
    virtual MoveState* releaseL(){return this;}
    virtual MoveState* pressShift(){return this;}
    virtual MoveState* releaseShift(){return this;}

    bool operator ==(MoveState &s){
        if(this->num == s.num)
            return true;
        else return false;
    }

    virtual MoveState* backtostand(){
        if(this->num % 2 == 1) return getstate(1);
        else return getstate(2);
    }

    MoveState* getdeath(){
        return getstate(11);
    }

    MoveState* resetstate(){
        return getstate(1);
    }

    MoveState* setstate_fall(){
        if(getdirection()) return getstate(7);
        else return getstate(8);
    }

    bool getdirection(){
        if(this->num % 2 == 1) return false;//left
        else return true;//right
    }
    
public:
    int num;
    QPixmap pic1;
    QPixmap pic2;
    bool nowState;
    static int jumptype;

};

class Standleft: public MoveState
{
public:
    Standleft():MoveState(){
        num = 1;
        pic1.load(Standleft1);
        pic2.load(Standleft2);
    }

    MoveState* pressL();
    MoveState* pressR();
    MoveState* pressShift();
};

class Standright: public MoveState
{
public:
    Standright():MoveState(){
        num = 2;
        pic1.load(Standright1);
        pic2.load(Standright2);
    }

    MoveState* pressL();
    MoveState* pressR();
    MoveState* pressShift();
};

class Moveleft: public MoveState
{
public:
    Moveleft():MoveState(){
        num = 3;
        pic1.load(Moveleft1);
        pic2.load(Moveleft2);
    }

    MoveState* pressL();
    MoveState* pressR();
    MoveState* releaseL();
    MoveState* pressShift();

};

class Moveright: public MoveState
{
public:
    Moveright():MoveState(){
        num = 4;
        pic1.load(Moveright1);
        pic2.load(Moveright2);
    }

    MoveState* pressR();
    MoveState* pressL();
    MoveState* releaseR();
    MoveState* pressShift();
};

class Jumpleft: public MoveState
{
public:
    Jumpleft():MoveState(){
        num = 5;
        pic1.load(Jumpleft1);
        pic2.load(Jumpleft2);
    }

    MoveState* pressL();
    MoveState* pressR();
    MoveState* releaseL();
    MoveState* releaseShift();
};

class Jumpleftdouble: public MoveState
{
public:
    Jumpleftdouble():MoveState() {
        num = 9;
        pic1.load(Jumpleft1);
        pic2.load(Jumpleft2);
    }

    MoveState* releaseShift();
};

class Jumpright: public MoveState
{
public:
    Jumpright():MoveState(){
        num = 6;
        pic1.load(Jumpright1);
        pic2.load(Jumpright2);
    }

    MoveState* pressL();
    MoveState* pressR();
    MoveState* releaseR();
    MoveState* releaseShift();
};

class Jumprightdouble: public MoveState
{
public:
    Jumprightdouble():MoveState() {
        num = 10;
        pic1.load(Jumpright1);
        pic2.load(Jumpright2);
    }

    MoveState* releaseShift();
};

class Fallleft: public MoveState
{
public:
    Fallleft():MoveState(){
        num = 7;
        pic1.load(Fallleft1);
        pic2.load(Fallleft2);
    }

    MoveState* pressR();
    MoveState* pressShift();
    MoveState* backtostand();
};

class Fallright: public MoveState
{
public:
    Fallright():MoveState(){
        num = 8;
        pic1.load(Fallright1);
        pic2.load(Fallright2);
    }

    MoveState* pressL();
    MoveState* pressShift();
    MoveState* backtostand();
};

class Death: public MoveState
{
public:
    Death():MoveState() {
        num = 11;
        pic1.load(Death1);
        pic2.load(Death2);
    }

    MoveState* backtostand();
};

#endif // MOVESTATE_H
