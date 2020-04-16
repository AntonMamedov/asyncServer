TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        core.cpp \
        httpheader.cpp \
        httpparser.cpp \
        main.cpp \
        secondaryfunctions.cpp

HEADERS += \
    core.h \
    httpheader.h \
    httpparser.h \
    secondaryfunctions.h
