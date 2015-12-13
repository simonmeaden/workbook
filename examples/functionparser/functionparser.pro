#-------------------------------------------------
#
# Project created by QtCreator 2015-09-14T16:13:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

CONFIG += debug_and_release
CONFIG += debug_and_release_target
CONFIG += build_all
#CONFIG += static # static library
#CONFIG += shared # shared dll library
CONFIG += c++11 # C++11 is the newest standard

CONFIG += link_prl

CONFIG(debug, debug|release) {
    TARGET = testparserd
    DESTDIR = ../../../../build/workbook/examples/parser
    OBJECTS_DIR = $$DESTDIR/.objd
    MOC_DIR = $$DESTDIR/.mocd
    RCC_DIR = $$DESTDIR/.qrcd
    UI_DIR = $$DESTDIR/.uid
}

CONFIG(release, debug|release) {
    TARGET = testparser
    DESTDIR = ../../../../build/workbook/examples/parser
    OBJECTS_DIR = $$DESTDIR/.obj
    MOC_DIR = $$DESTDIR/.moc
    RCC_DIR = $$DESTDIR/.qrc
    UI_DIR = $$DESTDIR/.ui
}

INCLUDEPATH += $$PWD/../include
INCLUDEPATH += $$PWD/../../workbooklib/src
INCLUDEPATH += $$PWD/../../workbooklib/src/include
INCLUDEPATH += $$PWD/../../../QtXlsxWriter/src/xlsx
DEPENDPATH  += $$PWD/../../workbooklib/src

include($$PWD/../../../simonsoft/qstd.pri)

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += ../../include
