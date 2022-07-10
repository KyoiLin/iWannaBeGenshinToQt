#include "save.h"
#include <QDebug>

Save::Save(QObject *parent) : QObject(parent)
{
    s_pic1.load(SAVE_PIC1);
    s_pic2.load(SAVE_PIC2);
    s_crashrect.setSize(QSize(s_pic1.width(), s_pic2.height()));
    this->savex = 600;
    this->savey = 600;
    this->s_x = 10;
    this->s_y = 595;
    s_crashrect.moveTo(this->s_x, this->s_y);
    this->save_state = false;
    //默认未激活状态
    time = 0;
    savevoice = new QSoundEffect(this);
    savevoice->setSource(QUrl::fromLocalFile(SAVE_SOUND));
    savevoice->setLoopCount(1);
    savevoice->setVolume(0.7);
    //设置存档音效

}

void Save::resetpos(){
    s_x = -s_pic1.width();
    s_y = -s_pic2.height();
    s_crashrect.moveTo(s_x, s_y);
}

void Save::backpos(){
    s_x = 10;
    s_y = 595;
    s_crashrect.moveTo(s_x, s_y);
}

void Save::getsave(const QRect &rect, const int x, const int y){
    if(this->s_crashrect.intersects(rect)){
        this->savex = x;
        this->savey = y;
        this->save_state = true;
        //读取当前坐标
        QFile save_file(SAVEFILE_PATH);
        if(!save_file.open(QIODevice::WriteOnly|QIODevice::Truncate))
            qDebug() << "fail to open file";
        else {
            qDebug() << "open file";
            QTextStream data(&save_file);
            data << this->savex << " " << this->savey;
            save_file.close();
        }
        qDebug() << "save" << savex << " " << savey;
        //存档
        emit save();
    }
}

QPoint Save::readsave(){
    QFile save_file(SAVEFILE_PATH);
    int x, y;
    if(!save_file.open(QIODevice::ReadOnly)){
        qDebug() << "fail to open file";
        x = 300;
        y = 600;
    }else {
        qDebug() << "open file";
        QTextStream data(&save_file);
        data >> x >> y;
        save_file.close();
        qDebug() << x << y;
    }
    return QPoint(x, y);
}
