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
    src/workbook.cpp \
    src/workbook_p.cpp \
    src/cell.cpp \
    src/cell_p.cpp \
    src/cellreference.cpp \
    src/cellreference_p.cpp \
    src/range.cpp \
    src/worksheet.cpp \
    src/worksheet_p.cpp \
    src/range_p.cpp \
    src/formatdelegate.cpp \
    src/format.cpp \
    src/format_p.cpp \
    src/formatdelegate_p.cpp \
    src/toolbar/qworkbooktoolbar.cpp \
    src/qworkbookview.cpp \
    src/qworkbookview_p.cpp \
    src/qworksheetview.cpp \
    src/qworksheetview_p.cpp \
    src/worksheetmodel.cpp \
    src/workbookparser.cpp \
    src/pluginstore.cpp \
    src/toolbar/qworkbookfunctiontoolbar.cpp \
    src/toolbar/qworkbookaligntoolbar.cpp \
    src/toolbar/qworkbookfonteffectstoolbar.cpp \
    src/toolbar/qworkbookfonttoolbar.cpp \
    src/toolbar/qworkbookindenttoolbar.cpp \
    src/toolbar/qworkbookmergetoolbar.cpp \
    src/worksheetmodel_p.cpp \
    src/mergedcell.cpp \
    src/formulacell.cpp \
    src/pluginstore_p.cpp \
    src/workbookparser_p.cpp \
    src/toolbar/qworkbooktoolbar_p.cpp \
    src/toolbar/qworkbookaligntoolbar_p.cpp \
    src/toolbar/qworkbookfonteffectstoolbar_p.cpp \
    src/toolbar/qworkbookfonttoolbar_p.cpp \
    src/toolbar/qworkbookfunctiontoolbar_p.cpp \
    src/toolbar/qworkbookindenttoolbar_p.cpp \
    src/toolbar/qworkbookmergetoolbar_p.cpp \
    src/toolbar/qcelledittoolbar.cpp \
    src/toolbar/qcelledittoolbar_p.cpp

HEADERS += \
    src/workbook.h\
    src/workbook_p.h \
    src/cell.h \
    src/cell_p.h \
    src/cellreference.h \
    src/cellreference_p.h \
    src/range.h \
    src/range_p.h \
    src/worksheet.h \
    src/worksheet_p.h \
    src/formatdelegate.h \
    src/format.h \
    src/format_p.h \
    src/types.h \
    src/formatdelegate_p.h \
    src/toolbar/qworkbooktoolbar.h \
    src/qworkbookview.h \
    src/qworkbookview_p.h \
    src/qworksheetview.h \
    src/qworksheetview_p.h \
    src/reference.h \
    src/workbookparser.h \
    src/pluginstore.h \
    src/worksheetmodel.h \
    src/toolbar/qworkbookfunctiontoolbar.h \
    src/toolbar/qworkbookmergetoolbar.h \
    src/toolbar/qworkbookfonttoolbar.h \
    src/toolbar/qworkbookindenttoolbar.h \
    src/toolbar/qworkbookfonteffectstoolbar.h \
    src/toolbar/qworkbookaligntoolbar.h \
    src/worksheetmodel_p.h \
    src/mergedcell.h \
    src/formulacell.h \
    src/mergedcell_p.h \
    src/formulacell_p.h \
    src/pluginstore_p.h \
    src/workbookparser_p.h \
    src/toolbar/qworkbooktoolbar_p.h \
    src/toolbar/qworkbookaligntoolbar_p.h \
    src/toolbar/qworkbookfonteffectstoolbar_p.h \
    src/toolbar/qworkbookfonttoolbar_p.h \
    src/toolbar/qworkbookfunctiontoolbar_p.h \
    src/toolbar/qworkbookindenttoolbar_p.h \
    src/toolbar/qworkbookmergetoolbar_p.h \
    src/toolbar/qcelledittoolbar.h \
    src/toolbar/qcelledittoolbar_p.h

RESOURCES += \
    $$PWD/src/workbook.qrc


#unix|win32: LIBS += -L$$PWD/../lib/ -lzlib
#unix|win32: LIBS += -L$$PWD/../lib/ -lquazip
#unix|win32: LIBS += -L$$PWD/../lib/ -lods

#INCLUDEPATH += $$PWD/../../QOds/ods
#INCLUDEPATH += $$PWD/../../QOds/ods
#INCLUDEPATH += $$PWD/../../QOds/ods

#DEPENDPATH += $$PWD/../../QOds/ods
#DEPENDPATH += $$PWD/../../QOds/ods
#DEPENDPATH += $$PWD/../../QOds/ods
