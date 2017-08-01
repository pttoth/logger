TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

INCLUDEPATH += ./include

SOURCES += test/main.cpp \
    src/logger.cpp


include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    include/logger.hpp

