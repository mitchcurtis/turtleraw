## TurtleRaw project file
QT += core gui multimedia xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = turtleraw
TEMPLATE = app

SOURCES += src/main.cpp \
            src/main_window.cpp \
            src/folder_browser.cpp \
            src/folder_browser_element.cpp \
            src/settings.cpp

HEADERS += src/hella.h \
            src/main_window.h \
            src/folder_browser.h \
            src/folder_browser_element.h \
            src/settings.h

## Submodules
# phantomstyle
include(modules/phantomstyle/src/phantom/phantom.pri)

RESOURCES += \
    resources.qrc
