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
#include "cell_p.h"
#include "format.h"
#include "types.h"
#include "cellreference.h"

#include "xlsxcell.h"
#include "xlsxworksheet.h"


#include "workbook_global.h"

namespace QWorkbook {

CellPrivate::CellPrivate() :
    mRow(-1),
    mColumn(-1),
    mValue(QVariant()),
    bLocked(false) {
}

CellPrivate::CellPrivate(Cell *q) :
    mRow(-1),
    mColumn(-1),
    mValue(QVariant()),
    bLocked(false),
    q_ptr(q) {
}

QVariant CellPrivate::value() const {
    if (mValue.isValid()) return mValue;
    return QVariant();
}

void CellPrivate::setValue(QVariant &value) {
    mValue = value;
}

QString CellPrivate::name() {
    if (mName.isEmpty()) {
        return Reference::cellToString(mRow, mColumn);
    }

    return mName;
}

void CellPrivate::setName(QString name) {
    mName = name;
}

void CellPrivate::setLocked(bool locked) {
    bLocked = locked;
}

bool CellPrivate::isEmpty() {
    if (mValue.isNull())
        return true;
    return false;
}

QString CellPrivate::toString() {
    QString str;
    str.append(Reference::columnToString(column()));
    str.append(QString::number(row()));
    str.append(":");
    str.append(mValue.toString());
    return str;
}

}
