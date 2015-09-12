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

CellReference::CellReference(int row, int column, QObject *parent) : QObject(parent), d_ptr(new CellReferencePrivate(this)) {
    Q_D(CellReference);
    d->mRow = row;
    d->mColumn = column;
}

CellReference::CellReference(QString reference, QObject *parent) : QObject(parent), d_ptr(new CellReferencePrivate(this)) {
    setPosition(reference);
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
    Q_D(CellReference);
    d->mRow = row;
 }

void CellReference::setColumn(int &column) {
    Q_D(CellReference);
    d->mColumn = column;
}

void CellReference::setPosition(int &row, int &column) {
    Q_D(CellReference);
    d->mRow = row;
    d->mColumn = column;
}

void CellReference::setPosition(QString &reference) {
    Q_D(CellReference);
    QPair<int, int> pair = cellFromString(reference);

    d->mRow = pair.first;
    d->mColumn = pair.second;
}

QString CellReference::toString() {
    QString string = columnToString(d_ptr->column()) + rowToString(d_ptr->row());
    return string;
}

/*!
 * /brief Converts a row number to an spreadsheet row value.
 *
 * Note : Spreadsheet offsets start at 1 while most others start at 0. The
 * function increments to allow zero based offsets.
 *
 * Row is easy as it just a number a1 - n
 */
QString CellReference::rowToString(int row) {
    return CellReferencePrivate::rowToString(row);
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
 * columns in a spreadsheet I should probably shoot myself to stop me
 * being a danger to society.
 */
QString CellReference::columnToString(int column) {
    return CellReferencePrivate::columnToString(column);
}

QString CellReference::cellToString(int column, int row) {
    return CellReferencePrivate::cellToString(column, row);
}

QPair<int, int> CellReference::cellFromString(QString &value) {
    return Reference::cellFromString(value);
}

int CellReference::columnFromString(QString &value) {
    return Reference::columnFromString(value);
}

int CellReference::rowFromString(QString &value) {
    return Reference::rowFromString(value);
}

