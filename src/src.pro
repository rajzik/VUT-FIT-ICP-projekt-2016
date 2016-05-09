# @file   src.pro
# @author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
# @date   May 2016
# @brief  QT settings

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11
CONFIG += debug
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
