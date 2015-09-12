/*
    Copyright © Simon Meaden 2015.

    This file is part of the QWorkbook spreadsheet library.

    QWorkbook is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    QWorkbook is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QWorkbook.  If not, see <http://www.gnu.org/licenses/>.

    It is also available on request from Simon Meaden info@smelecomp.co.uk.
*/
#include "worksheetmodel_p.h"
#include "worksheetmodel.h"
#include "worksheet.h"
#include "cell.h"
#include "cellreference.h"
#include "format.h"
#include "range.h"
#include "cellreference.h"

WorksheetModelPrivate::WorksheetModelPrivate(PluginStore *store, WorksheetModel *parent) :
    mRows(INITIALROWS),
    mColumns(INITIALCOLUMNS),
    pPluginStore(store),
    q_ptr(parent) {

    setWorksheet(new Worksheet(pPluginStore, q_ptr));

}

WorksheetModelPrivate::WorksheetModelPrivate(Worksheet *sheet, PluginStore *store, WorksheetModel *parent) :
    mRows(INITIALROWS),
    mColumns(INITIALCOLUMNS),
    pPluginStore(store),
    q_ptr(parent) {

    setWorksheet(sheet);

}

WorksheetModelPrivate::~WorksheetModelPrivate() {

}

void WorksheetModelPrivate::setWorksheet(Worksheet *sheet) {
    pSheet = sheet;
    pSheet->setModel(q_ptr);
    q_ptr->connect(sheet, SIGNAL(formatHasChanged(int,int)), q_ptr, SLOT(formatChanged(int,int)));
}

bool WorksheetModelPrivate::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role == Qt::EditRole) {

        int row = index.row();
        int column = index.column();

        pSheet->setCell(row, column, value);

        emit q_ptr->dataChanged(index, index);


        mStatus.mMaxRow = (row > mStatus.mMaxRow ? row : mStatus.mMaxRow);
        mStatus.mMaxCol = (column > mStatus.mMaxCol ? column : mStatus.mMaxCol);

        return true;

    }
    return false;
}

int WorksheetModelPrivate::maxRow() {
    return mStatus.mMaxRow;
}

int WorksheetModelPrivate::maxColumn() {
    return mStatus.mMaxCol;
}

bool WorksheetModelPrivate::isLocked(CellReference &ref) {
    return pSheet->isLocked(ref.row(), ref.column());
}

bool WorksheetModelPrivate::isLocked(int row, int column) {
    return pSheet->isLocked(row, column);
}

void WorksheetModelPrivate::lockSheet() {
    pSheet->lockSheet();
    emit q_ptr->layoutChanged();
}

void WorksheetModelPrivate::unlockSheet() {
    pSheet->unlockSheet();
    emit q_ptr->layoutChanged();
}

void WorksheetModelPrivate::lockCell(int row, int column) {
    pSheet->lockCell(row, column);
    QModelIndex i = q_ptr->index(row, column);
    emit q_ptr->dataChanged(i, i);
}

void WorksheetModelPrivate::lockCell(CellReference &ref) {
    pSheet->lockCell(ref.row(), ref.column());
    QModelIndex i = q_ptr->index(ref.row(), ref.column());
    emit q_ptr->dataChanged(i, i);
}

void WorksheetModelPrivate::lockRow(int &row) {
    pSheet->lockRow(row);
    int maxColumn = pSheet->maxColumn(row);
    QModelIndex i1 = q_ptr->index(row, 0);
    QModelIndex i2 = q_ptr->index(row, maxColumn);
    emit q_ptr->dataChanged(i1, i2);
}

void WorksheetModelPrivate::lockColumn(int &column) {
    pSheet->lockColumn(column);
    int maxRow = pSheet->maxRow();
    QModelIndex i1 = q_ptr->index(0, column);
    QModelIndex i2 = q_ptr->index(maxRow, column);
    emit q_ptr->dataChanged(i1, i2);
}

void WorksheetModelPrivate::lockRange(Range &range) {
    pSheet->lockRange(range);
    QModelIndex i1 = q_ptr->index(range.top(), range.left());
    QModelIndex i2 = q_ptr->index(range.bottom(), range.right());
    emit q_ptr->dataChanged(i1, i2);
}

void WorksheetModelPrivate::unlockCell(int row, int column) {
    pSheet->unlockCell(row, column);
    QModelIndex i = q_ptr->index(row, column);
    emit q_ptr->dataChanged(i, i);
}

void WorksheetModelPrivate::unlockCell(CellReference &ref) {
    pSheet->unlockCell(ref.row(), ref.column());
    QModelIndex i = q_ptr->index(ref.row(), ref.column());
    emit q_ptr->dataChanged(i, i);
}

void WorksheetModelPrivate::unlockRow(int &row) {
    pSheet->unlockRow(row);
    int maxColumn = pSheet->maxColumn(row);
    QModelIndex i1 = q_ptr->index(row, 0);
    QModelIndex i2 = q_ptr->index(row, maxColumn);
    emit q_ptr->dataChanged(i1, i2);
}

void WorksheetModelPrivate::unlockColumn(int &column) {
    pSheet->unlockColumn(column);
    int maxRow = pSheet->maxRow();
    QModelIndex i1 = q_ptr->index(0, column);
    QModelIndex i2 = q_ptr->index(maxRow, column);
    emit q_ptr->dataChanged(i1, i2);
}

void WorksheetModelPrivate::unlockRange(Range &range) {
    pSheet->unlockRange(range);
    QModelIndex i1 = q_ptr->index(range.top(), range.left());
    QModelIndex i2 = q_ptr->index(range.bottom(), range.right());
    emit q_ptr->dataChanged(i1, i2);
}

Qt::ItemFlags WorksheetModelPrivate::flags(const QModelIndex &index) const {
    Qt::ItemFlags flags = q_ptr->QAbstractTableModel::flags(index);
    if (pSheet->isLocked(index.row(), index.column()))
        flags &= ~Qt::ItemIsEditable;
    else
        flags |= Qt::ItemIsEditable;
    return flags;
}

void WorksheetModelPrivate::saveWorksheet(QString path) {
    pSheet->saveWorksheet(path);
}

void WorksheetModelPrivate::formatChanged(int row, int column) {
    QModelIndex i = q_ptr->index(row, column);
    emit q_ptr->dataChanged(i, i);
}

int WorksheetModelPrivate::rowCount() const {
    return mRows;
}

int WorksheetModelPrivate::columnCount() const {
    return mColumns;
}

QVariant WorksheetModelPrivate::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        int row = index.row();
        int column = index.column();
        QVariant cell = pSheet->cell(row, column);
        return cell;
    }
    return QVariant();
}

Format* WorksheetModelPrivate::format(const QModelIndex &index, int role) const {
    int row = index.row();
    int column = index.column();
    return format(row, column, role);
}

Format* WorksheetModelPrivate::format(int row, int column, int role) const {
    if (role == Qt::DisplayRole) {
        Format *format = pSheet->format(row, column);
        // you can have formats set for cells that do not have data in them yet. This signal saves formats
        // when they have been modified.
        return format;
    }
    return NULL;
}

void WorksheetModelPrivate::formatHasChanged(Format* format) {
    pSheet->setFormat(format);
}

void WorksheetModelPrivate::setFormat(const QModelIndex &index, Format *format, int role)  {
    if (index.isValid() && role == Qt::EditRole) {

        pSheet->setFormat(format);

        QModelIndex start, end;
        int row = index.row();
        int column = index.column();
        end = q_ptr->QAbstractTableModel::index(row + 1, column + 1);

        if (row > 0) row--;
        if (column > 0) column--;

        start = q_ptr->QAbstractTableModel::index(row, column);

        emit q_ptr->dataChanged(start, end);
    }
}

void WorksheetModelPrivate::setFormat(int row, int column, Format *format, int role) {
    if (role == Qt::EditRole) {
        QModelIndex index = q_ptr->QAbstractTableModel::index(row, column);

        if (index.isValid()) {

            pSheet->setFormat(format);

            emit q_ptr->dataChanged(index, index);
        }
    }
}

QVariant WorksheetModelPrivate::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal)
            return CellReference::columnToString(section);
        else if (orientation == Qt::Vertical)
            return QString::number(section + 1);
    }

    return QVariant();
}

void WorksheetModelPrivate::setShowGrid(bool showGrid) {
    pSheet->setShowGrid(showGrid);
}

bool WorksheetModelPrivate::showGrid() {
    return pSheet->showGrid();
}
