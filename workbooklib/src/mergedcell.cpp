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



MergedCell::MergedCell(QObject *parent) :
    Cell(*new MergedCellPrivate(), parent) {
}

MergedCell::MergedCell(int row, int column, QObject *parent) :
    Cell(*new MergedCellPrivate(), parent) {

    Q_D(Cell);
    d->mRow = row;
    d->mColumn = column;
}

MergedCell::MergedCell(int row, int column, const QVariant &value, QObject *parent) :
    Cell(*new MergedCellPrivate(), parent) {

    Q_D(Cell);
    d->mRow = row;
    d->mColumn = column;
    d->mValue = value;
}

MergedCell::MergedCell(CellReference reference, QObject *parent) :
    Cell(*new MergedCellPrivate(), parent) {

    Q_D(Cell);
    d->mRow = reference.row();
    d->mColumn = reference.column();
}

MergedCell::MergedCell(CellReference reference, QVariant &value, QObject *parent) :
    Cell(*new MergedCellPrivate(), parent) {

    Q_D(Cell);
    d->mRow = reference.row();
    d->mColumn = reference.column();
    d->mValue = value;
}

MergedCell::~MergedCell() {

}

