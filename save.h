#ifndef SAVE_H
#define SAVE_H

#include <QObject>
#include <QPixmap>
#include <QRect>
#include <QDebug>
#include <QFile>
#include <QPoint>
#include <QSoundEffect>
#include "config.h"

class Save : public QObject
{
    Q_OBJECT
public:
    explicit Save(QObject *parent = nullptr);
    void getsave(const QRect &rect, const int x, const int y);
    //在widget里遍历发射出的子弹进行碰撞检测
    void resetpos();
    //重置坐标，主要是用于场景切换的时候隐藏该任务
    QPoint readsave();
    //读档
    void backpos();
    //读档时恢复初始坐标

public:
    QPixmap s_pic1;
    QPixmap s_pic2;
    QRect s_crashrect;
    bool save_state;
    int savex;
    int savey;
    //保存的坐标
    int s_x;
    int s_y;
    //存档点自身的坐标
    int time;
    //显示时长
    QSoundEffect *savevoice;


signals:
    void save();

public slots:
};

#endif // SAVE_H
