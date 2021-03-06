#-------------------------------------------------
#
# Project created by QtCreator 2018-05-31T19:51:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_Module_Test
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

#CONFIG+=console

SOURCES += \
        main.cpp \
        widget.cpp \
    calibration.cpp \
    Application.cpp \
    dramview.cpp

HEADERS += \
        widget.h \
    calibration.h \
    Application.h \
    dramview.h

FORMS += \
        widget.ui \
    ipsetting.ui

QMAKE_CXXFLAGS += -std=c++11

target.path=/opt/arm
INSTALLS+=target

mylibs.path = /opt/arm
mylibs.files=../../build/arm/libDriver.so
INSTALLS+=mylibs

myConfig.path=/
myConfig.files=/opt/sdk_for_A7/rootfs/opt
INSTALLS+=myConfig

unix:!macx: LIBS += -L$$PWD/../../build/arm/ -lDriver

INCLUDEPATH += $$PWD/../../src
DEPENDPATH += $$PWD/../../build/arm

