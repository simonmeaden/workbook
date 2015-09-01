# ***************************************************************************
# Copyright (c) 2013-2015, Simon Meaden
# ***************************************************************************
#
# Simonsoft - Workbook
# Config PRI File
#
# Workbook is intended as a simple spreadsheet based on QTableView.
#
# This code is licensed under the LGPL Version 3.0
# ***************************************************************************

INCLUDEPATH += $$PWD/src
INCLUDEPATH += $$PWD/src/include
INCLUDEPATH += $$PWD/../include
INCLUDEPATH += $$PWD/../plugin/include
INCLUDEPATH += $$PWD/../../include

QT += core gui svg
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../QtXlsxWriter/src/xlsx/qtxlsx.pri)

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
    $$PWD/src/qworksheetview_p.cpp \
    $$PWD/src/formatdelegate.cpp \
    $$PWD/src/format.cpp \
    $$PWD/src/format_p.cpp \
    $$PWD/src/formatdelegate_p.cpp \
    $$PWD/src/qworkbookview_p.cpp \
    $$PWD/src/qworkbooktoolbar.cpp \
    $$PWD/src/qworkbookview.cpp \
    $$PWD/src/qworksheetview.cpp \
    $$PWD/src/worksheetmodel.cpp \
    $$PWD/src/workbookparser.cpp \
    $$PWD/src/pluginstore.cpp

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
    $$PWD/src/qworksheetview_p.h \
    $$PWD/src/formatdelegate.h \
    $$PWD/src/format.h \
    $$PWD/src/format_p.h \
    $$PWD/src/types.h \
    $$PWD/src/formatdelegate_p.h \
    $$PWD/src/qworkbookview_p.h \
    $$PWD/src/qquad.h \
    $$PWD/src/qworkbooktoolbar.h \
    $$PWD/src/qworkbookview.h \
    $$PWD/src/qworksheetview.h \
    $$PWD/src/reference.h \
    $$PWD/src/workbookparser.h \
    $$PWD/src/pluginstore.h \
    $$PWD/src/worksheetmodel.h

