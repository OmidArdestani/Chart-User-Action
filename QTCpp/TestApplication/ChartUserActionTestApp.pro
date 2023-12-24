QT  += core gui widgets printsupport

TEMPLATE = app


FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h

SOURCES += \
    main.cpp \
    mainwindow.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-CppChartUserAction-Desktop_Qt_6_6_1_MSVC2019_64bit-Release/release/ -lCppChartUserAction
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-CppChartUserAction-Desktop_Qt_6_6_1_MSVC2019_64bit-Debug/debug/ -lCppChartUserAction

INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src
