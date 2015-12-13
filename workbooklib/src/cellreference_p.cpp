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

#include "workbook_global.h"
#include "cellreference_p.h"
#include "cellreference.h"
#include "workbook.h"

namespace QWorkbook {

CellReferencePrivate::CellReferencePrivate() :
    mRow(-1),
    mColumn(-1),
    bStaticRow(false),
    bStaticColumn(false) {
}

CellReferencePrivate::CellReferencePrivate(CellReference *parent) :
    q_ptr(parent),
    mRow(-1),
    mColumn(-1),
    bStaticRow(false),
    bStaticColumn(false) {

}

bool CellReferencePrivate::isValid() {

    if (mRow < 0 || mColumn < 0) return false;

    return true;

}

QString CellReferencePrivate::toString() {

    QString string =
            (bStaticRow ? "$" : "") +
            columnToString(mColumn) +
            (bStaticColumn ? "$" : "") +
            rowToString(mRow);
    return string;

}


void CellReferencePrivate::setPosition(int &row, int &column) {

    mRow = row;
    mColumn = column;

}

void CellReferencePrivate::setPosition(int &row, int &column, bool &rowStatic, bool &colStatic) {

    mRow = row;
    mColumn = column;
    bStaticRow = rowStatic;
    bStaticColumn = colStatic;

}

void CellReferencePrivate::setPosition(QString &reference) {

    SplitCellName split = cellFromString(reference);

    mRow = split.row;
    mColumn = split.column;
    bStaticRow = split.rowStatic;
    bStaticColumn = split.colStatic;

}





}
