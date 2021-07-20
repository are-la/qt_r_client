#-------------------------------------------------
#
# Project created by QtCreator 2019-07-17T21:19:05
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = r_client
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


SOURCES += main.cpp\
    degree_of_friend.cpp \
    news.cpp \
        widget.cpp \
    end.cpp \
    chat_main.cpp \
    check.cpp \
    detail_tail.cpp \
    firmain.cpp \
    group_chat.cpp \
    mybutton.cpp

HEADERS  += widget.h \
    degree_of_friend.h \
    end.h \
    chat_main.h \
    check.h \
    detail_tail.h \
    firmain.h \
    group_chat.h \
    header.h \
    mybutton.h \
    news.h

FORMS    += widget.ui \
    degree_of_friend.ui \
    end.ui \
    chat_main.ui \
    check.ui \
    detail_tail.ui \
    firmain.ui \
    group_chat.ui \
    mybutton.ui \
    news.ui
