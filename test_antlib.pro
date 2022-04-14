QT += core gui widgets
CONFIG += c++17

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
include($$PWD/../../antlib/antlib.pri)
include($$PWD/../ant/antlib.pri)



SOURCES += \
    graphicsscene.cpp \
    graphicsview.cpp \
    main.cpp \
    mainwindow.cpp


HEADERS += \
    graphicsscene.h \
    graphicsview.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

