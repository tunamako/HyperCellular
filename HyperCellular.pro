#-------------------------------------------------
#
# Project created by QtCreator 2018-01-27T01:14:26
#
#-------------------------------------------------

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += include
TARGET = bin/main
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/math_helpers.cpp \
    src/edge.cpp \
    src/tile.cpp \
    src/automaton.cpp \
    src/pcviewmodel.cpp \
    src/controller.cpp \


HEADERS += \
    include/mainwindow.h \
    include/math_helpers.h \
    include/edge.h \
    include/tile.h \
    include/automaton.h \
    include/pcviewmodel.h \
    include/controller.h \

OBJECTS_DIR += build
MOC_DIR += build

QMAKE_CXXFLAGS += -lgtest -Wall -Wno-unused-parameter -g -std=c++11
