#include "helper.h"
#include "ui_helper.h"

helper::helper(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::helper)
{
    ui->setupUi(this);
    pic.load(HELP_PIC);
    setFixedSize(pic.width(), pic.height());
    setWindowTitle(HELP_TITLE);
    QPalette p;
    p.setColor(QPalette::WindowText,Qt::white);
    ui->label->setPalette(p);
    ui->label_2->setPalette(p);
    ui->label_3->setPalette(p);
    ui->label_4->setPalette(p);
    ui->label_5->setPalette(p);
    ui->label_6->setPalette(p);
    ui->label_7->setPalette(p);
    ui->label_8->setPalette(p);
    ui->label_9->setPalette(p);
    ui->label_10->setPalette(p);
    ui->label_11->setPalette(p);
    ui->label_12->setPalette(p);
}

helper::~helper()
{
    delete ui;
}

void helper::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(rect(), pic, QRect());
}

void helper::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Escape:
        this->close();
        break;
    default:
        break;
    }
}
