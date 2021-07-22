## TurtleRaw project file
QT += core gui multimedia xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = turtleraw
TEMPLATE = app

SOURCES += src/main.cpp \
            src/main_window.cpp \
            src/folder_browser.cpp \
            src/folder_browser_element.cpp \
            src/settings.cpp \
            src/assign_filetypes_dialog.cpp \
            src/settings_dialog.cpp \
            src/image_preview.cpp

HEADERS += src/hella.h \
            src/main_window.h \
            src/folder_browser.h \
            src/folder_browser_element.h \
            src/settings.h \
            src/assign_filetypes_dialog.h \
            src/settings_dialog.h \
            src/image_preview.h

## Libraries
# exiv2
LIBS += -L/usr/local/lib -lexiv2
INCLUDEPATH += /usr/local/include

## Submodules
# phantomstyle
include(modules/phantomstyle/src/phantom/phantom.pri)

# easylogging++
include(modules/easyloggingpp/easyloggingpp.pri)

RESOURCES += \
    resources.qrc
