/*
 * This Workbook library is © Simon Meaden 2015. It is licensed under the LGPL V3 license.
 *
 * This Workbook library dynamically links to unmodified Nokia Qt5 Library. The Qt5
 * Library is © 2011 Nokia Corporation and/or its subsidiary(-ies), and is licensed
 * under the GNU Lesser General Public License version 2.1 with Nokia Qt LGPL exception
 * version 1.1.
 *
 * Qt5 library is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License, version 2.1, as published by the
 * Free Software Foundation.
 *
 * Qt5 library is provided “AS IS”, without WARRANTIES OR CONDITIONS OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY WARRANTIES OR CONDITIONS OF
 * TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 * As an additional permission to the GNU Lesser General Public License version 3.0, the
 * object code form of a “work that uses the Library” may incorporate material from a
 * header file that is part of the Library. You may distribute such object code under
 * terms of your choice, provided that: (i) the header files of the Library have not
 * been modified; and (ii) the incorporated material is limited to numerical parameters,
 * data structure layouts, accessors, macros, inline functions and templates; and (iii)
 * you comply with the terms of Section 6 of the GNU Lesser General Public License version 3.0.
 *
 * Moreover, you may apply this exception to a modified version of the Library, provided
 * that such modification does not involve copying material from the Library into the
 * modified Library’s header files unless such material is limited to (i) numerical
 * parameters; (ii) data structure layouts; (iii) accessors; and (iv) small macros,
 * templates and inline functions of five lines or less in length.
 *
 * Furthermore, you are not required to apply this additional permission to a modified
 * version of the Library.
 *
 * You should have received a copy of the GNU Lesser General Public License along
 * with this package; if not, write to the Free Software Foundation, Inc., 51 Franklin
 * Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * The source code for Qt 5.4.X SDK is available from Nokia here:
 * http://get.qt.nokia.com/qt/source/qt-everywhere-opensource-src-4.7.X.zip.
 *
 * It is also available on request from Simon Meaden info@smelecomp.co.uk.
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

