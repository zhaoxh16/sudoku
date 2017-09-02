#-------------------------------------------------
#
# Project created by QtCreator 2017-08-28T12:33:01
#
#-------------------------------------------------

QT       += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sudoku
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
        mainwindow.cpp \
    gameboard.cpp \
    numberblock.cpp \
    highlightframe.cpp \
    mainform.cpp \
    timer.cpp \
    undomodule.cpp \
    boardcover.cpp \
    database.cpp \
    chooselevelwidget.cpp \
    sudokualgorithm.cpp \
    welcomewidget.cpp \
    loadwidget.cpp \
    windialog.cpp

HEADERS += \
        mainwindow.h \
    gameboard.h \
    numberblock.h \
    highlightframe.h \
    mainform.h \
    timer.h \
    undomodule.h \
    boardcover.h \
    database.h \
    chooselevelwidget.h \
    sudokualgorithm.h \
    welcomewidget.h \
    loadwidget.h \
    windialog.h

DISTFILES += \
    ../Dan Gibson - Nature's Path 自然小径_01.wav \
    ../Dan Gibson - Nature's Path 自然小径_01.wav

FORMS += \
    chooselevelwidget.ui \
    welcomewidget.ui \
    loadwidget.ui \
    windialog.ui
