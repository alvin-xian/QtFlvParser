#-------------------------------------------------
#
# Project created by QtCreator 2017-08-31T09:57:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtFlvParser
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    flvheader.cpp \
    flvscripttag.cpp \
    flvavctag.cpp \
    flvvideotag.cpp \
    flvaudiotag.cpp \
    flvfileparser.cpp \
    itag.cpp

HEADERS  += mainwindow.h \
    flvheader.h \
    flvscripttag.h \
    flvavctag.h \
    flvvideotag.h \
    flvaudiotag.h \
    flvfileparser.h \
    itag.h

FORMS    += mainwindow.ui
