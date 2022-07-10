#ifndef HELPER_H
#define HELPER_H

#include <QWidget>
#include <QKeyEvent>
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QPalette>
#include "config.h"

namespace Ui {
class helper;
}

class helper : public QWidget
{
    Q_OBJECT

public:
    explicit helper(QWidget *parent = 0);
    ~helper();
    void paintEvent(QPaintEvent *);

    QPixmap pic;

private:
    Ui::helper *ui;

protected:
    void keyPressEvent(QKeyEvent *event);

};

#endif // HELPER_H
