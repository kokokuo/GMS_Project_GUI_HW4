#-------------------------------------------------
#
# Project created by QtCreator 2013-12-27T18:04:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = graphical_Modeling_system_GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    xmlManager.cpp \
    xmlErrorCode.cpp \
    groups.cpp \
    group.cpp \
    gmsModel.cpp \
    components.cpp \
    component.cpp


HEADERS  += mainwindow.h \
    xmlManager.h \
    xmlErrorCode.h \
    groups.h \
    group.h \
    gmsModel.h \
    components.h \
    component.h


FORMS    += mainwindow.ui

RESOURCES += \
    asset.qrc
