QT  += core gui widgets printsupport

TEMPLATE = lib
CONFIG += staticlib

TARGET = CppChartUserAction

HEADERS += \
    QCustomPlot/qcustomplot.h \
    Tools/chartmarker.h \
    Tools/chartmeasure.h \
    Tools/chartpointer.h \
    Tools/chartselector.h \
    Tools/chartshape.h \
    Tools/iplottool.h \
    actionhandler.h \
    chartuseraction.h

SOURCES += \
    QCustomPlot/qcustomplot.cpp \
    Tools/chartmarker.cpp \
    Tools/chartmeasure.cpp \
    Tools/chartpointer.cpp \
    Tools/chartselector.cpp \
    Tools/chartshape.cpp \
    actionhandler.cpp \
    chartuseraction.cpp
