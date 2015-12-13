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

#include "workbook.h"
#include "cellreference.h"

#include "workbook_global.h"

namespace QWorkbook {

/*!
 * \brief Creates an invalid CellReference.
 * \param parent parent object
 */
CellReference::CellReference() :
    QObject(),
    d_ptr(new CellReferencePrivate(this)) {
}

CellReference::CellReference(QObject *parent) :
    QObject(parent),
    d_ptr(new CellReferencePrivate(this)) {
}

CellReference::CellReference(int row, int column, QObject *parent) :
    QObject(parent),
    d_ptr(new CellReferencePrivate(this)) {
    Q_ASSERT(row > 0 && column > 0);

    d_ptr->setPosition(row, column);

}

CellReference::CellReference(int row, int column, bool rowStatic, bool colStatic, QObject *parent) :
    QObject(parent),
    d_ptr(new CellReferencePrivate(this)) {
    Q_ASSERT(row > 0 && column > 0);

    d_ptr->setPosition(row, column, rowStatic, colStatic);

}

CellReference::CellReference(QString reference, QObject *parent) :
    QObject(parent),
    d_ptr(new CellReferencePrivate(this)) {

    d_ptr->setPosition(reference);

}

bool CellReference::isValid() {
    return d_ptr->isValid();
}

int CellReference::row() const {
    return d_ptr->row();
}


int CellReference::column() const {
    return d_ptr->column();
}

void CellReference::setRow(int &row) {
    Q_ASSERT(row > 0);

    Q_D(CellReference);
    d->mRow = row;

 }

void CellReference::setColumn(int &column) {
    Q_ASSERT(column > 0);

    Q_D(CellReference);
    d->mColumn = column;

}


QString CellReference::toString() {

    return d_ptr->toString();

}


}
