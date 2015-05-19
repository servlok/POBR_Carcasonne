TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.10

SOURCES += main.cpp

LIBS += -L/usr/local/lib \
    -lopencv_core \
    -lopencv_highgui

QMAKE_CXXFLAGS+=-std=c++11
QMAKE_CXXFLAGS+=-stdlib=libc++

QMAKE_LFLAGS+=-std=c++11
QMAKE_LFLAGS+=-stdlib=libc++

INCLUDEPATH += /usr/local/include


include(deployment.pri)
qtcAddDeployment()

