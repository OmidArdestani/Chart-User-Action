QT  += core gui widgets printsupport

TEMPLATE = app


FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h

SOURCES += \
    main.cpp \
    mainwindow.cpp


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/release/ -lCppChartUserAction
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/debug/ -lCppChartUserAction

INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/release/libCppChartUserAction.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/debug/libCppChartUserAction.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/release/CppChartUserAction.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/debug/CppChartUserAction.lib
