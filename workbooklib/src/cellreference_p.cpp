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
#include <QPair>

#include "cellreference_p.h"
#include "cellreference.h"
#include "workbook.h"
#include "range.h"


CellReferencePrivate::CellReferencePrivate() :
    mRow(-1),
    mColumn(-1) {
}

CellReferencePrivate::CellReferencePrivate(CellReference *parent) :
    q_ptr(parent),
    mRow(-1),
    mColumn(-1) {
}

bool CellReferencePrivate::isValid() {

    if (mRow < 0 || mColumn < 0) return false;

    return true;

}

/*!
 * /brief Converts a row number to an spreadsheet row value.
 *
 * Note : Spreadsheet offsets start at 1 while most others start at 0. The
 * function increments to allow zero based offsets.
 *
 * Row is easy as it just a number a1 - n
 */
QString CellReferencePrivate::rowToString(int row) {
    QString result =  QString::number(row + 1);
    return result;
}

/*!
 * \brief Converts a column number to an spreadsheet column value A - Z, AA - ZZ.
 *
 * 0 = A
 * 1 = B
 * ...
 * 26 = AA
 * 27 = AB etc.
 *
 * I'm not going past two columns. If I need to have more than 702 (26 * 26) + 26
 * columns in a spreadsheet I will probably shoot myself to stop me
 * being a danger to society.
 */
QString CellReferencePrivate::columnToString(int column) {
    int divisor = 26;
    int mod = column % divisor;
    int div = column / divisor;
    // limit to one extra char

    char c = mod + 'A';
    QString result(c);
    if (div > 0 && div <= 26) {
        c = 'A' + (div - 1);
        result.prepend(c);
        c += div;
    }
    return result;
}

QString CellReferencePrivate::cellToString(int column, int row) {
    QString result =  columnToString(column) + rowToString(row);
    return result;
}


