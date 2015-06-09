TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.10

SOURCES += main.cpp \
    processing.cpp \
    cutting.cpp \
    moments.cpp

LIBS += -L/usr/local/lib \
    -lopencv_core \
    -lopencv_highgui \
    -lopencv_features2d \
    -lopencv_imgproc

QMAKE_CXXFLAGS+=-std=c++11

QMAKE_LFLAGS+=-std=c++11

INCLUDEPATH += /usr/local/include

copydata.commands = $(COPY_DIR) $$PWD/img/* $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    processing.h \
    cutting.h \
    moments.h

