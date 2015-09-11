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

#include "cell.h"
#include "cell_p.h"
#include "cellreference.h"
#include "format.h"

#include "xlsxcell.h"
#include "xlsxworksheet.h"

Cell::Cell() :
    d_ptr(new CellPrivate(this)) {

}

Cell::Cell(QObject *parent) :
    QObject(parent),
    d_ptr(new CellPrivate(this)) {

}

Cell::Cell(int row, int column, QObject *parent) :
    QObject(parent),
    d_ptr(new CellPrivate(this)) {

    Q_D(Cell);
    d->mRow = row;
    d->mColumn = column;
}

Cell::Cell(int row, int column, const QVariant &value, QObject *parent) :
    QObject(parent),
    d_ptr(new CellPrivate(this)) {

    Q_D(Cell);
    d->mRow = row;
    d->mColumn = column;
    d->mValue = value;
}

Cell::Cell(CellReference reference, QObject *parent) :
    QObject(parent),
    d_ptr(new CellPrivate(this)) {

    Q_D(Cell);
    d->mRow = reference.row();
    d->mColumn = reference.column();
}

Cell::Cell(CellReference reference, QVariant &value, QObject *parent) :
    QObject(parent),
    d_ptr(new CellPrivate(this)) {

    Q_D(Cell);
    d->mRow = reference.row();
    d->mColumn = reference.column();
    d->mValue = value;
}

Cell::~Cell() {

}

CellType Cell::type() {
    return d_ptr->type();
}

QString Cell::name() {
    return d_ptr->name();
}

void Cell::setName(QString name) {
    d_ptr->setName(name);
}


bool Cell::empty() {
    return d_ptr->isEmpty();
}

bool Cell::locked() {
    return d_ptr->locked();
}

bool Cell::isEmpty() {
    return d_ptr->isEmpty();
}

void Cell::setLocked(bool locked) {
    d_ptr->setLocked(locked);
}

int Cell::row() const {
    return d_ptr->row();
}

int Cell::column() const {
    return d_ptr->column();
}

QString Cell::toString() {
    return d_ptr->toString();
}

void Cell::setPosition(int &row, int &column) {
    Q_D(Cell);
    d->mRow = row;
    d->mColumn = column;
}

void Cell::setPosition(CellReference &reference) {
    Q_D(Cell);
    d->mRow = reference.row();
    d->mColumn = reference.column();
}

void Cell::setValue(const QVariant &value) {
    Q_D(Cell);
    d->mValue = value;
}

QVariant Cell::value() const {
    QVariant v = d_ptr->value();
    if (v.isValid())
        return v;
    return QVariant();
}
