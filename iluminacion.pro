#-------------------------------------------------
#
# Project created by QtCreator 2014-11-20T08:13:05
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = iluminacion
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

LIBS += -lm -lGL -lglut -lGLU /usr/lib64/libopencv_core.so /usr/lib64/libopencv_highgui.so

