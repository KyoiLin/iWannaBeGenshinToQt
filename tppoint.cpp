#include "tppoint.h"

TPPoint::TPPoint(QObject *parent) : QObject(parent)
{
    tp_pic.load(TP_PIC);
    tp_crashrect.setSize(QSize(tp_pic.width(), tp_pic.height()));
    tpx = 990;
    tpy = 595;
    tp_crashrect.moveTo(tpx, tpy);
}

void TPPoint::resetpos(){
    tpx = 1000;
    tpy = 700;
    tp_crashrect.moveTo(tpx, tpy);
}

void TPPoint::backpos(){
    tpx = 990;
    tpy = 595;
    tp_crashrect.moveTo(tpx, tpy);
}

bool TPPoint::tp_CollisionDetection(const QRect &kidrect){
    if(this->tp_crashrect.intersects(kidrect)){
        emit mapchange();
        return true;
    }else return false;
}
