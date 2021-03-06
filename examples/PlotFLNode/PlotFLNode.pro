# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = app
DESTDIR = bin
QT += core gui widgets

CONFIG += debug
DEFINES += PLOTFLNODE_LIB APP_HAS_DLL APP_BUILD_DLL QWT_DLL QT_DLL

INCLUDEPATH += . \
    ./GeneratedFiles \
    ./GeneratedFiles/$(Configuration) \
    ./../../../../include \
    ./../../../../include/common/QtGUIEx \
    ./../../src
LIBS += -L"./../../../../bin/debug" \
    -L"./../../lib" \
    -lqwtd
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/debug
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(PlotFLNode.pri)
TRANSLATIONS += PlotFLNode.ts

HEADERS += \
    mainwindow.h

SOURCES += \
    main.cpp \
    mainwindow.cpp
