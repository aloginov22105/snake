//TEMPLATE = app
//CONFIG += console c++11
//CONFIG -= app_bundle
//CONFIG -= qt
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += core

SOURCES += \
        game.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
    game.h \
    mainwindow.h

RESOURCES += \
    resource.qrc

FORMS += \
    mainwindow.ui
