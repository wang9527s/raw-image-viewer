#-------------------------------------------------
#
# Project created by QtCreator 2023-07-19T09:29:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = raw-image-viewer
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

DESTDIR = $$PWD/../bin/

INCLUDEPATH += \
    $$PWD/../depend/opencv3.2.0/include \
    $$PWD/../depend/LibRaw-0.21.0

LIBS += \
    $$PWD/../depend/opencv3.2.0/x64_release/opencv_world320.lib \
    $$PWD/../depend/LibRaw-0.21.0/release-x86_64/libraw.lib \

SOURCES += main.cpp

