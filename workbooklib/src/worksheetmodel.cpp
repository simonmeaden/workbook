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
#include "worksheetmodel.h"
#include "worksheetmodel_p.h"
#include "cell.h"
#include "cellreference.h"
#include "format.h"
#include "range.h"
#include "cellreference.h"
#include "workbook_global.h"

#include "xlsxworksheet.h"

#include <Sheet.hpp>

namespace QWorkbook {

WorksheetModel::WorksheetModel(QObject *parent) :
    QAbstractTableModel(parent),
    d_ptr(new WorksheetModelPrivate(this)) {

}

//void WorksheetModel::setWorksheet(Worksheet *sheet) {
//    d_ptr->setWorksheet(sheet);
//}

WorksheetModel* WorksheetModel::clone() {
    return d_ptr->clone();
}

bool WorksheetModel::setData(const QModelIndex &index, const QVariant value, int role) {
    return d_ptr->setData(index, value, role);
}

bool WorksheetModel::setData(int row, int column, const QVariant value, int role) {
    QModelIndex index = d_ptr->getIndex(row, column);
    return d_ptr->setData(index, value, role);
}

int WorksheetModel::maxRow() {
    return d_ptr->maxRow();
}

int WorksheetModel::maxColumn() {
    return d_ptr->maxColumn();
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

void WorksheetModel::saveWorksheet(QString path, WorksheetType type) {
    d_ptr->saveWorksheet(path, type);
}

void WorksheetModel::saveWorksheet(QXlsx::Worksheet *sheet) {
    d_ptr->writeXlsx(sheet);
}

void WorksheetModel::saveWorksheet(ods::Sheet *sheet) {
    d_ptr->writeOds(sheet);
}

void WorksheetModel::formatChanged(QModelIndex index) {
    d_ptr->formatChanged(index);
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

Cell* WorksheetModel::cellAsCell(int row, int column) {
    Q_D(WorksheetModel);
    return d_ptr->cellAsCell(row, column);
}

void WorksheetModel::setCellAsCell(int row, int column, Cell *cell) {
    Q_D(WorksheetModel);
    d_ptr->setCellAsCell(row, column, cell);
}

void WorksheetModel::setSheetName(QString name) {
    d_ptr->setSheetName(name);
}

QString WorksheetModel::sheetName() {
    return d_ptr->sheetName();
}

}

