#-------------------------------------------------
#
# Project created by QtCreator 2016-04-13T11:22:37
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BrzoKucanje
TEMPLATE = app

RC_ICONS += resources/icons/FastTyping.ico

SOURCES += main.cpp\
        mainwindow.cpp \
    word.cpp \
    mainmenu.cpp \
    game.cpp \
    multiplayer.cpp \
    label.cpp \
    serverwidget.cpp \
    twoplayerwindow.cpp \
    scorewindow.cpp \
    players.cpp

HEADERS  += mainwindow.h \
    word.h \
    mainmenu.h \
    game.h \
    multiplayer.h \
    label.h \
    serverwidget.h \
    twoplayerwindow.h \
    scorewindow.h \
    players.h

FORMS    += mainwindow.ui \
    mainmenu.ui \
    multiplayer.ui \
    serverwidget.ui \
    twoplayerwindow.ui \
    scorewindow.ui

QMAKE_CXXFLAGS += -std=c++11

DISTFILES += \
    data/words.txt

RESOURCES += \
    resources.qrc
