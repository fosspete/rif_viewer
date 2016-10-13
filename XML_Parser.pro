#-------------------------------------------------
#
# Project created by QtCreator 2015-02-26T20:48:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XML_Parser
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    rifparser.cpp \
    attrdeflist.cpp \
    requirementlist.cpp

HEADERS  += mainwindow.h \
    rifparser.h \
    attrdeflist.h \
    requirementlist.h

FORMS    += mainwindow.ui
