/*
 * This Workbook library is © Simon Meaden 2015. It is licensed under the LGPL V3 license.
 *
 * This Workbook library dynamically links to unmodified Nokia Qt5 Library. The Qt5
 * Library is © 2011 Nokia Corporation and/or its subsidiary(-ies), and is licensed
 * under the GNU Lesser General Public License version 2.1 with Nokia Qt LGPL exception
 * version 1.1.
 *
 * Qt5 library is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License, version 2.1, as published by the
 * Free Software Foundation.
 *
 * Qt5 library is provided “AS IS”, without WARRANTIES OR CONDITIONS OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY WARRANTIES OR CONDITIONS OF
 * TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 * As an additional permission to the GNU Lesser General Public License version 3.0, the
 * object code form of a “work that uses the Library” may incorporate material from a
 * header file that is part of the Library. You may distribute such object code under
 * terms of your choice, provided that: (i) the header files of the Library have not
 * been modified; and (ii) the incorporated material is limited to numerical parameters,
 * data structure layouts, accessors, macros, inline functions and templates; and (iii)
 * you comply with the terms of Section 6 of the GNU Lesser General Public License version 3.0.
 *
 * Moreover, you may apply this exception to a modified version of the Library, provided
 * that such modification does not involve copying material from the Library into the
 * modified Library’s header files unless such material is limited to (i) numerical
 * parameters; (ii) data structure layouts; (iii) accessors; and (iv) small macros,
 * templates and inline functions of five lines or less in length.
 *
 * Furthermore, you are not required to apply this additional permission to a modified
 * version of the Library.
 *
 * You should have received a copy of the GNU Lesser General Public License along
 * with this package; if not, write to the Free Software Foundation, Inc., 51 Franklin
 * Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * The source code for Qt 5.4.X SDK is available from Nokia here:
 * http://get.qt.nokia.com/qt/source/qt-everywhere-opensource-src-4.7.X.zip.
 *
 * It is also available on request from Simon Meaden info@smelecomp.co.uk.
 */

#include <QDir>
#include <QApplication>

#include "qstd.h"

#include <workbook_global.h>
#include "worksheet.h"
#include "worksheet_p.h"
#include "cell.h"
#include "format.h"
#include "pluginstore.h"

Worksheet::Worksheet(PluginStore *store, QObject *parent) :
    QObject(parent),
    d_ptr(new WorksheetPrivate(store, this)) {

}

Worksheet::Worksheet(QString name, PluginStore *store, QObject *parent) :
    QObject(parent),
    d_ptr(new WorksheetPrivate(store, this)) {
    d_ptr->setSheetName(name);
}

Worksheet::~Worksheet() {

}

PluginStore* Worksheet::pluginStore() {
    return d_ptr->pluginStore();
}

void Worksheet::setSheetName(QString name) {
    d_ptr->setSheetName(name);
}

QString Worksheet::sheetName() {
    return d_ptr->sheetName();
}

void Worksheet::setModel(WorksheetModel *model) {
    d_ptr->setModel(model);
}

void Worksheet::saveWorksheet(QString path) {
    d_ptr->saveWorksheet(path);
}

void Worksheet::saveWorksheet() {
    d_ptr->saveWorksheet();
}

void Worksheet::saveWorksheet(WorksheetType type, QString path) {
    d_ptr->saveWorksheet(type, path);
}

void Worksheet::writeXlsx(QXlsx::Worksheet *sheet) {
    d_ptr->writeXlsx(sheet);
}

void Worksheet::readXlsx(QXlsx::Worksheet *sheet, int index) {
    d_ptr->readXlsx(sheet, index);
}

void Worksheet::saveWorksheet(WorksheetType type) {
    d_ptr->saveWorksheet(type);
}

int Worksheet::maxColumn(int row) {
    return d_ptr->maxColumn(row);
}

int Worksheet::maxRow() {
    return d_ptr->maxRow();
}

QVariant Worksheet::cell(CellReference &ref) {
    return d_ptr->cell(ref.row(), ref.column());
}

QVariant Worksheet::cell(int row, int column) {
    return d_ptr->cell(row, column);
}

Cell* Worksheet::cellAsCell(int row, int column) {
    return d_ptr->cellAsCell(row, column);
}

void Worksheet::setCellAsCell(int row, int column, Cell* cell) {
    d_ptr->setCellAsCell(row, column, cell);
}

void Worksheet::setCell(int row, int column, QVariant cell) {
    d_ptr->setCell(row, column, cell);
}

void Worksheet::setCell(CellReference &ref, QVariant cell) {
    d_ptr->setCell(ref.row(), ref.column(), cell);
}

Format* Worksheet::format(CellReference &ref) {
    return d_ptr->format(ref.row(), ref.column());
}

Format* Worksheet::format(int row, int column) {
    return d_ptr->format(row, column);
}

void Worksheet::setFormat(Format *format) {
    d_ptr->setFormat(format);
}

void Worksheet::formatChanged(Format *format) {
//    Format *format = qobject_cast<Format*>(sender());
    d_ptr->setFormat(format);
    emit formatHasChanged(format->row(), format->column());
}

Format* Worksheet::rowFormat(int row) {
    return d_ptr->rowFormat(row);
}

Format* Worksheet::columnFormat(int column) {
    return d_ptr->columnFormat(column);
}

void Worksheet::setRowFormat(int row, Format *format) {
    d_ptr->setRowFormat(row, format);
}

void Worksheet::setColumnFormat(int column, Format *format) {
    d_ptr->setColumnFormat(column, format);
}

void Worksheet::setShowGrid(bool showGrid) {
    d_ptr->setShowGrid(showGrid);
}

bool Worksheet::showGrid() {
    return d_ptr->showGrid();
}

bool Worksheet::isLocked(CellReference &ref) {
    return d_ptr->isLocked(ref.row(), ref.column());
}

bool Worksheet::isLocked(int row, int column) {
    return d_ptr->isLocked(row, column);
}

void Worksheet::lockSheet() {
    d_ptr->lockSheet();
}

void Worksheet::unlockSheet() {
    d_ptr->unlockSheet();
}

void Worksheet::lockCell(int row, int column) {
    d_ptr->lockCell(row, column);
}

void Worksheet::lockCell(CellReference &ref) {
    d_ptr->lockCell(ref.row(), ref.column());
}

void Worksheet::lockRow(int &row) {
    d_ptr->lockRow(row);
}

void Worksheet::lockColumn(int &column) {
    d_ptr->lockColumn(column);
}

void Worksheet::lockRange(Range &range) {
    d_ptr->lockRange(range);
}

void Worksheet::unlockCell(int row, int column) {
    d_ptr->unlockCell(row, column);
}

void Worksheet::unlockCell(CellReference &ref) {
    d_ptr->unlockCell(ref.row(), ref.column());
}

void Worksheet::unlockRow(int &row) {
    d_ptr->unlockRow(row);
}

void Worksheet::unlockColumn(int &column) {
    d_ptr->unlockColumn(column);
}

void Worksheet::unlockRange(Range &range) {
    d_ptr->unlockRange(range);
}

void Worksheet::leftBorderChanged(Format *format) {
    d_ptr->leftBorderChanged(format);
}

void Worksheet::topBorderChanged(Format *format) {
    d_ptr->topBorderChanged(format);
}

void Worksheet::rightBorderChanged(Format *format) {
    d_ptr->rightBorderChanged(format);
}

void Worksheet::bottomBorderChanged(Format *format) {
    d_ptr->bottomBorderChanged(format);
}
