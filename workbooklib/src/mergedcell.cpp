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
#include "mergedcell.h"



#include "workbook_global.h"

namespace QWorkbook {

MergedCell::MergedCell(QObject *parent) :
    Cell(*new MergedCellPrivate(), parent) {
}

MergedCell::MergedCell(int row, int column, int rowSpan, int colSpan, QObject *parent) :
    Cell(*new MergedCellPrivate(), parent) {

    Q_D(MergedCell);
    d->mRow = row;
    d->mColumn = column;
    d->mRowSpan = rowSpan;
    d->mColSpan = colSpan;
}

MergedCell::MergedCell(int row, int column, int rowSpan, int colSpan, const QVariant &value, QObject *parent) :
    Cell(*new MergedCellPrivate(), parent) {

    Q_D(MergedCell);
    d->mRow = row;
    d->mColumn = column;
    d->mRowSpan = rowSpan;
    d->mColSpan = colSpan;
    d->mValue = value;
}

MergedCell::MergedCell(CellReference from, int rowSpan, int colSpan, QObject *parent) :
    Cell(*new MergedCellPrivate(), parent) {

    Q_D(MergedCell);
    d->mRow = from.row();
    d->mColumn = from.column();
    d->mRowSpan = rowSpan;
    d->mColSpan = colSpan;
}

MergedCell::MergedCell(CellReference from, CellReference to, QObject *parent) :
    Cell(*new MergedCellPrivate(), parent) {

    Q_D(MergedCell);
    d->mRow = from.row();
    d->mColumn = from.column();
    int f = from.row();
    int t = to.row();
    int temp;
    if (f > t) {
        temp = f;
        f = t;
        t = temp;
    }
    d->mRowSpan = t - f + 1;
    f = from.row();
    t = to.row();
    if (f > t) {
        temp = f;
        f = t;
        t = temp;
    }
    d->mColSpan = t - f + 1;
}

MergedCell::MergedCell(CellReference from, int rowSpan, int colSpan, QVariant &value, QObject *parent) :
    Cell(*new MergedCellPrivate(), parent) {

    Q_D(MergedCell);
    d->mRow = from.row();
    d->mColumn = from.column();
    d->mRowSpan = rowSpan;
    d->mColSpan = colSpan;
    d->mValue = value;
}

MergedCell::MergedCell(CellReference from, CellReference  to, QVariant &value, QObject *parent) :
    Cell(*new MergedCellPrivate(), parent) {

    Q_D(MergedCell);
    d->mRow = from.row();
    d->mColumn = from.column();
    int f = from.row();
    int t = to.row();
    int temp;
    if (f > t) {
        temp = f;
        f = t;
        t = temp;
    }
    d->mRowSpan = t - f + 1;
    f = from.row();
    t = to.row();
    if (f > t) {
        temp = f;
        f = t;
        t = temp;
    }
    d->mColSpan = t - f + 1;
    d->mValue = value;
}

QList<Cell*> MergedCell::overwritten() {
    Q_D(MergedCell);
    return d->overwritten();
}

void MergedCell::setOverwritten(QList<Cell*> cells) {
    Q_D(MergedCell);
    d->mOverwritten = cells;
}

void MergedCell::setMergedData() {
    Q_D(MergedCell);
    d->mMergedData = MergedCellPrivate::MergedData;
}

void MergedCell::setFirstCell() {
    Q_D(MergedCell);
    d->mMergedData = MergedCellPrivate::FirstCellData;
}

int MergedCell::rowSpan() {
    Q_D(MergedCell);
    return d->mRowSpan;

}
int MergedCell::columnSpan() {
    Q_D(MergedCell);
    return d->mColSpan;
}

}

