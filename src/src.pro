#-------------------------------------------------
#
# Project created by QtCreator 2016-05-05T10:39:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = ../HRA2016
TEMPLATE = app

LIBS += -lboost_system -lboost_filesystem

SOURCES +=\
        mainwindow.cpp \
    game.cpp \
    game-gui.cpp \
    main-gui.cpp \
    player.cpp

HEADERS  += mainwindow.h \
    game.h \
    game-gui.h \
    player.h \
    enums.h

FORMS    += mainwindow.ui
