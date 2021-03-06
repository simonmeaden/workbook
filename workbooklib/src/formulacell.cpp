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
#include "formulacell.h"

// TODO manage cell as formula.

#include "workbook_global.h"

namespace QWorkbook {

FormulaCell::FormulaCell(QObject *parent) :
    MergedCell(*new FormulaCellPrivate(), parent) {
}

FormulaCell::FormulaCell(int row, int column, QObject *parent) :
    MergedCell(*new FormulaCellPrivate(), parent) {

    Q_D(Cell);
    d->mRow = row;
    d->mColumn = column;
}

FormulaCell::FormulaCell(int row, int column, const QVariant &value, QObject *parent) :
    MergedCell(*new FormulaCellPrivate(), parent) {

    Q_D(Cell);
    d->mRow = row;
    d->mColumn = column;
    d->mValue = value;
}

FormulaCell::FormulaCell(CellReference reference, QObject *parent) :
    MergedCell(*new FormulaCellPrivate(), parent) {

    Q_D(Cell);
    d->mRow = reference.row();
    d->mColumn = reference.column();
}

FormulaCell::FormulaCell(CellReference reference, QVariant &value, QObject *parent) :
    MergedCell(*new FormulaCellPrivate(), parent) {

    Q_D(Cell);
    d->mRow = reference.row();
    d->mColumn = reference.column();
    d->mValue = value;
}


}

