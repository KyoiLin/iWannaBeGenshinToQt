#-------------------------------------------------
#
# Project created by QtCreator 2022-05-05T10:13:43
#
#-------------------------------------------------

QT       += core gui
QT += core
CONFIG   += resources_big
QT += multimedia
QT += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = iwannabegenshin
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    kid.cpp \
    movestate.cpp \
    floor.cpp \
    bullet.cpp \
    save.cpp \
    tppoint.cpp \
    zhongli.cpp \
    ball.cpp \
    helper.cpp

HEADERS += \
        widget.h \
    config.h \
    movestate.h \
    kid.h \
    floor.h \
    bullet.h \
    save.h \
    tppoint.h \
    zhongli.h \
    ball.h \
    helper.h

RESOURCES += \
    res.qrc

FORMS += \
    helper.ui

RC_FILE += icon.rc
