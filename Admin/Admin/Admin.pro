#-------------------------------------------------
#
# Project created by QtCreator 2020-06-11T13:28:59
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Admin
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
    FileHeader.cpp \
    LoginHeader.cpp \
        main.cpp \
        Admin.cpp \
    QueueTable.cpp \
    MainHeader.cpp \
    TaskHeader.cpp

HEADERS += \
        Admin.h \
    FileHeader.h \
    LoginHeader.h \
    QueueTable.h \
    MainHeader.h \
    TaskHeader.h

FORMS += \
        Admin.ui

RESOURCES += \
    Resources.qrc
