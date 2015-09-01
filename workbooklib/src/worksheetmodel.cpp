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
#include "worksheet.h"
#include "cell.h"
#include "cellreference.h"
#include "format.h"
#include "range.h"
#include "cellreference.h"

WorksheetModel::WorksheetModel(PluginStore *store, QObject *parent) :
    QAbstractTableModel(parent),
    mRows(ROWS),
    mColumns(COLUMNS),
    pPluginStore(store) {

    setWorksheet(new Worksheet(pPluginStore, this));
}

WorksheetModel::WorksheetModel(Worksheet *sheet, PluginStore *store, QObject *parent) :
    QAbstractTableModel(parent),
    mRows(ROWS),
    mColumns(COLUMNS),
    pPluginStore(store) {
    setWorksheet(sheet);
}

WorksheetModel::~WorksheetModel() {

}

void WorksheetModel::setWorksheet(Worksheet *sheet) {
    pSheet = sheet;
    pSheet->setModel(this);
    connect(sheet, SIGNAL(formatHasChanged(int,int)), this, SLOT(formatChanged(int,int)));
}

bool WorksheetModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role == Qt::EditRole) {

        int row = index.row();
        int column = index.column();

        pSheet->setCell(row, column, value);

        emit dataChanged(index, index);
        return true;

    }
    return false;
}

Cell* WorksheetModel::cellAsCell(int row, int column) {
    return pSheet->cellAsCell(row, column);
}

bool WorksheetModel::isLocked(CellReference &ref) {
    return pSheet->isLocked(ref.row(), ref.column());
}

bool WorksheetModel::isLocked(int row, int column) {
    return pSheet->isLocked(row, column);
}

void WorksheetModel::lockSheet() {
    pSheet->lockSheet();
    emit layoutChanged();
}

void WorksheetModel::unlockSheet() {
    pSheet->unlockSheet();
    emit layoutChanged();
}

void WorksheetModel::lockCell(int row, int column) {
    pSheet->lockCell(row, column);
    QModelIndex i = this->index(row, column);
    emit dataChanged(i, i);
}

void WorksheetModel::lockCell(CellReference &ref) {
    pSheet->lockCell(ref.row(), ref.column());
    QModelIndex i = this->index(ref.row(), ref.column());
    emit dataChanged(i, i);
}

void WorksheetModel::lockRow(int &row) {
    pSheet->lockRow(row);
    int maxColumn = pSheet->maxColumn(row);
    QModelIndex i1 = this->index(row, 0);
    QModelIndex i2 = this->index(row, maxColumn);
    emit dataChanged(i1, i2);
}

void WorksheetModel::lockColumn(int &column) {
    pSheet->lockColumn(column);
    int maxRow = pSheet->maxRow();
    QModelIndex i1 = this->index(0, column);
    QModelIndex i2 = this->index(maxRow, column);
    emit dataChanged(i1, i2);
}

void WorksheetModel::lockRange(Range &range) {
    pSheet->lockRange(range);
    QModelIndex i1 = this->index(range.top(), range.left());
    QModelIndex i2 = this->index(range.bottom(), range.right());
    emit dataChanged(i1, i2);
}

void WorksheetModel::unlockCell(int row, int column) {
    pSheet->unlockCell(row, column);
    QModelIndex i = this->index(row, column);
    emit dataChanged(i, i);
}

void WorksheetModel::unlockCell(CellReference &ref) {
    pSheet->unlockCell(ref.row(), ref.column());
    QModelIndex i = this->index(ref.row(), ref.column());
    emit dataChanged(i, i);
}

void WorksheetModel::unlockRow(int &row) {
    pSheet->unlockRow(row);
    int maxColumn = pSheet->maxColumn(row);
    QModelIndex i1 = this->index(row, 0);
    QModelIndex i2 = this->index(row, maxColumn);
    emit dataChanged(i1, i2);
}

void WorksheetModel::unlockColumn(int &column) {
    pSheet->unlockColumn(column);
    int maxRow = pSheet->maxRow();
    QModelIndex i1 = this->index(0, column);
    QModelIndex i2 = this->index(maxRow, column);
    emit dataChanged(i1, i2);
}

void WorksheetModel::unlockRange(Range &range) {
    pSheet->unlockRange(range);
    QModelIndex i1 = this->index(range.top(), range.left());
    QModelIndex i2 = this->index(range.bottom(), range.right());
    emit dataChanged(i1, i2);
}

Qt::ItemFlags WorksheetModel::flags(const QModelIndex &index) const {
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if (pSheet->isLocked(index.row(), index.column()))
        flags &= ~Qt::ItemIsEditable;
    else
        flags |= Qt::ItemIsEditable;
    return flags;
}

void WorksheetModel::saveWorksheet(QString path) {
    pSheet->saveWorksheet(path);
}

void WorksheetModel::formatChanged(int row, int column) {
    QModelIndex i = this->index(row, column);
    emit dataChanged(i, i);
}

int WorksheetModel::rowCount(const QModelIndex& /*parent*/) const {
    return mRows;
}

int WorksheetModel::columnCount(const QModelIndex& /*parent*/) const {
    return mColumns;
}

QVariant WorksheetModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        int row = index.row();
        int column = index.column();
        QVariant cell = pSheet->cell(row, column);
        return cell;
    }
    return QVariant();
}

Format* WorksheetModel::format(const QModelIndex &index, int role) const {
    int row = index.row();
    int column = index.column();
    return format(row, column, role);
}

Format* WorksheetModel::format(int row, int column, int role) const {
    if (role == Qt::DisplayRole) {
        Format *format = pSheet->format(row, column);
        // you can have formats set for cells that do not have data in them yet. This signal saves formats
        // when they have been modified.
        return format;
    }
    return NULL;
}

void WorksheetModel::formatHasChanged(Format* format) {
    pSheet->setFormat(format);
}

void WorksheetModel::setFormat(const QModelIndex &index, Format *format, int role)  {
    if (index.isValid() && role == Qt::EditRole) {

        pSheet->setFormat(format);

        QModelIndex start, end;
        int row = index.row();
        int column = index.column();
        end = QAbstractTableModel::index(row + 1, column + 1);

        if (row > 0) row--;
        if (column > 0) column--;

        start = QAbstractTableModel::index(row, column);

        emit dataChanged(start, end);
    }
}

void WorksheetModel::setFormat(int row, int column, Format *format, int role) {
    if (role == Qt::EditRole) {
        QModelIndex index = QAbstractTableModel::index(row, column);

        if (index.isValid()) {

            pSheet->setFormat(format);

            emit dataChanged(index, index);
        }
    }
}

QVariant WorksheetModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal)
            return CellReference::columnToString(section);
        else if (orientation == Qt::Vertical)
            return QString::number(section + 1);
    }

    return QVariant();
}

void WorksheetModel::setShowGrid(bool showGrid) {
    pSheet->setShowGrid(showGrid);
}

bool WorksheetModel::showGrid() {
    return pSheet->showGrid();
}


