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

#include "worksheetmodel.h"
#include "worksheetmodel_p.h"
#include "worksheet.h"
#include "cell.h"
#include "cellreference.h"
#include "format.h"
#include "range.h"
#include "cellreference.h"

WorksheetModel::WorksheetModel(PluginStore *store, QObject *parent) :
    QAbstractTableModel(parent),
    d_ptr(new WorksheetModelPrivate(store, this)) {

}

WorksheetModel::WorksheetModel(Worksheet *sheet, PluginStore *store, QObject *parent) :
    QAbstractTableModel(parent),
    d_ptr(new WorksheetModelPrivate(sheet, store, this)) {

}

WorksheetModel::~WorksheetModel() {

}

//void WorksheetModel::span(int row, int column, int rowSpan, int colSpan, QList<Cell*> cells) {
//    d_ptr->span(row, column, rowSpan, colSpan, cells);
//}
//void WorksheetModel::despan(int row, int column, int rowSpan, int colSpan) {
//    d_ptr->despan(row, column, rowSpan, colSpan);
//}

void WorksheetModel::setWorksheet(Worksheet *sheet) {
    d_ptr->setWorksheet(sheet);
}

bool WorksheetModel::setData(const QModelIndex &index, const QVariant &value, int role) {    
    return d_ptr->setData(index, value, role);
}

bool WorksheetModel::isLocked(CellReference &ref) {
    return d_ptr->isLocked(ref.row(), ref.column());
}

bool WorksheetModel::isLocked(int row, int column) {
    return d_ptr->isLocked(row, column);
}

void WorksheetModel::lockSheet() {
    d_ptr->lockSheet();
}

void WorksheetModel::unlockSheet() {
    d_ptr->unlockSheet();
}

void WorksheetModel::lockCell(int row, int column) {
    d_ptr->lockCell(row, column);
}

void WorksheetModel::lockCell(CellReference &ref) {
    d_ptr->lockCell(ref.row(), ref.column());
}

void WorksheetModel::lockRow(int &row) {
    d_ptr->lockRow(row);
}

void WorksheetModel::lockColumn(int &column) {
    d_ptr->lockColumn(column);
}

void WorksheetModel::lockRange(Range &range) {
    d_ptr->lockRange(range);
}

void WorksheetModel::unlockCell(int row, int column) {
    d_ptr->unlockCell(row, column);
}

void WorksheetModel::unlockCell(CellReference &ref) {
    d_ptr->unlockCell(ref.row(), ref.column());
}

void WorksheetModel::unlockRow(int &row) {
    d_ptr->unlockRow(row);
}

void WorksheetModel::unlockColumn(int &column) {
    d_ptr->unlockColumn(column);
}

void WorksheetModel::unlockRange(Range &range) {
    d_ptr->unlockRange(range);
}

Qt::ItemFlags WorksheetModel::flags(const QModelIndex &index) const {
     return d_ptr->flags(index);
}

void WorksheetModel::saveWorksheet(QString path) {
    d_ptr->saveWorksheet(path);
}

void WorksheetModel::formatChanged(int row, int column) {
    d_ptr->formatChanged(row, column);
}

int WorksheetModel::rowCount(const QModelIndex& /*parent*/) const {
    return d_ptr->rowCount();
}

int WorksheetModel::columnCount(const QModelIndex& /*parent*/) const {
    return d_ptr->columnCount();
}

QVariant WorksheetModel::data(const QModelIndex &index, int role) const {
    return d_ptr->data(index, role);
}

Format* WorksheetModel::format(const QModelIndex &index, int role) const {
    return d_ptr->format(index,role);
}

Format* WorksheetModel::format(int row, int column, int role) const {
    return format(row, column, role);
}

void WorksheetModel::formatHasChanged(Format* format) {
    d_ptr->formatHasChanged(format);
}

void WorksheetModel::setFormat(const QModelIndex &index, Format *format, int role)  {
    d_ptr->setFormat(index, format, role);
}

void WorksheetModel::setFormat(int row, int column, Format *format, int role) {
    d_ptr->setFormat(row, column, format, role);
}

QVariant WorksheetModel::headerData(int section, Qt::Orientation orientation, int role) const {
    return d_ptr->headerData(section, orientation, role);
}

void WorksheetModel::setShowGrid(bool showGrid) {
    d_ptr->setShowGrid(showGrid);
}

bool WorksheetModel::showGrid() {
    return d_ptr->showGrid();
}

Cell* WorksheetModel::cellAsCell(int row, int column) {
    Q_D(WorksheetModel);
    return d->pSheet->cellAsCell(row, column);
}

void WorksheetModel::setCellAsCell(int row, int column, Cell *cell) {
    Q_D(WorksheetModel);
    d->pSheet->setCellAsCell(row, column, cell);
}
