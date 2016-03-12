QT += core
QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = complex_network
CONFIG += console
QT += printsupport

TEMPLATE = app

SOURCES += main.cpp \
    create_net.cpp \
    node.cpp \
    complex_network.cpp \
    histogram.cpp \
    stdafx.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    representations.cpp

HEADERS += \
    create_net.h \
    stdafx.h \
    node.h \
    complex_network.h \
    histogram.h \
    resource.h \
    targetver.h \
    representations.h \
    mainwindow.h \
    qcustomplot.h
CONFIG += c++11

FORMS += \
    mainwindow.ui
