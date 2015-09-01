#-------------------------------------------------
#
# Project created by QtCreator 2015-02-28T10:07:42
#
#-------------------------------------------------

QT += core gui widgets

TEMPLATE = lib

SUBDIRS = \
    plugin

DEFINES += WORKBOOK_LIBRARY
DEFINES += USE_PLUGINS

CONFIG += debug_and_release
CONFIG += debug_and_release_target
CONFIG += build_all
#CONFIG += static # static library
CONFIG += shared # shared dll library
CONFIG += c++11 # C++11 is the newest standard

CONFIG += create_prl # create library info for dependant apps
CONFIG += link_prl # link prl's from dependant libraries

DOCPATH = $$PWD/docs

CONFIG -= import_plugins

CONFIG(debug, debug|release) {
    TARGET = workbookd
    DESTDIR = $$PWD/../../../build/workbook
    OBJECTS_DIR = $$DESTDIR/.objd
    MOC_DIR = $$DESTDIR/.mocd
    RCC_DIR = $$DESTDIR/.qrcd
    UI_DIR = $$DESTDIR/.uid
}

CONFIG(release, debug|release) {
    TARGET = workbook
    DESTDIR = $$PWD/../../../build/workbook
    OBJECTS_DIR = $$DESTDIR/.obj
    MOC_DIR = $$DESTDIR/.moc
    RCC_DIR = $$DESTDIR/.qrc
    UI_DIR = $$DESTDIR/.ui
}

INCLUDEPATH += $$PWD/src
INCLUDEPATH += $$PWD/../include
INCLUDEPATH += $$PWD/../plugin/include

include($$PWD/../../simonsoft/extendedtabwidget.pri)
include($$PWD/../../simonsoft/qstd.pri)
include($$PWD/../../simonsoft/qquad.pri)
include($$PWD/../../QtXlsxWriter/src/xlsx/qtxlsx.pri)

SOURCES += \
    $$PWD/src/workbook.cpp \
    $$PWD/src/workbook_p.cpp \
    $$PWD/src/cell.cpp \
    $$PWD/src/cell_p.cpp \
    $$PWD/src/cellreference.cpp \
    $$PWD/src/cellreference_p.cpp \
    $$PWD/src/range.cpp \
    $$PWD/src/worksheet.cpp \
    $$PWD/src/worksheet_p.cpp \
    $$PWD/src/range_p.cpp \
    $$PWD/src/formatdelegate.cpp \
    $$PWD/src/format.cpp \
    $$PWD/src/format_p.cpp \
    $$PWD/src/formatdelegate_p.cpp \
    $$PWD/src/toolbar/qworkbooktoolbar.cpp \
    $$PWD/src/qworkbookview.cpp \
    $$PWD/src/qworkbookview_p.cpp \
    $$PWD/src/qworksheetview.cpp \
    $$PWD/src/qworksheetview_p.cpp \
    $$PWD/src/worksheetmodel.cpp \
    $$PWD/src/workbookparser.cpp \
    $$PWD/src/pluginstore.cpp \
    src/toolbar/basetoolbar.cpp \
    src/toolbar/workbookfunctiontoolbar.cpp \
    src/toolbar/workbookfonttoolbar.cpp \
    src/toolbar/workbookfonteffectstoolbar.cpp \
    src/toolbar/workbookaligntoolbar.cpp \
    src/toolbar/workbookindenttoolbar.cpp

HEADERS += \
    $$PWD/src/workbook.h\
    $$PWD/src/workbook_p.h \
    $$PWD/src/cell.h \
    $$PWD/src/cell_p.h \
    $$PWD/src/cellreference.h \
    $$PWD/src/cellreference_p.h \
    $$PWD/src/range.h \
    $$PWD/src/range_p.h \
    $$PWD/src/worksheet.h \
    $$PWD/src/worksheet_p.h \
    $$PWD/src/formatdelegate.h \
    $$PWD/src/format.h \
    $$PWD/src/format_p.h \
    $$PWD/src/types.h \
    $$PWD/src/formatdelegate_p.h \
    $$PWD/src/toolbar/qworkbooktoolbar.h \
    $$PWD/src/qworkbookview.h \
    $$PWD/src/qworkbookview_p.h \
    $$PWD/src/qworksheetview.h \
    $$PWD/src/qworksheetview_p.h \
    $$PWD/src/reference.h \
    $$PWD/src/workbookparser.h \
    $$PWD/src/pluginstore.h \
    $$PWD/src/worksheetmodel.h \
    src/toolbar/basetoolbar.h \
    src/toolbar/workbookfunctiontoolbar.h \
    src/toolbar/workbookfonttoolbar.h \
    src/toolbar/workbookfonteffectstoolbar.h \
    src/toolbar/workbookaligntoolbar.h \
    src/toolbar/workbookindenttoolbar.h

RESOURCES += \
    $$PWD/src/workbook.qrc


#unix|win32: LIBS += -L$$PWD/../../QOds/build/lib/ -lods
#unix|win32: LIBS += -L$$PWD/../../QOds/build/lib/ -lquazip
#unix|win32: LIBS += -L$$PWD/../../QOds/build/lib/ -lzlib

#INCLUDEPATH += $$PWD/../../QOds/build
#INCLUDEPATH += $$PWD/../../QOds/build
#INCLUDEPATH += $$PWD/../../QOds/build

#DEPENDPATH += $$PWD/../../QOds/build
#DEPENDPATH += $$PWD/../../QOds/build
#DEPENDPATH += $$PWD/../../QOds/build

#win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../QOds/build/lib/ods.lib
#else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../../QOds/build/lib/libods.a
#win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../QOds/build/lib/quazip.lib
#else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../../QOds/build/lib/libquazip.a
#win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../QOds/build/lib/zlib.lib
#else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../../QOds/build/lib/libzlib.a
