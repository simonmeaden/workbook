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
