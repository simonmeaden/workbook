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
#include "range.h"
#include "range_p.h"


#include "workbook_global.h"

namespace QWorkbook {

Range::Range(QObject *parent) :
    QObject(parent),
    d_ptr(new RangePrivate(this)) {

}

Range::Range(int &row1, int &column1, int &row2, int &column2, QObject *parent) :
    QObject(parent),
    d_ptr(new RangePrivate(row1, column1, row2, column2, this)) {
    Q_ASSERT(row1 > 0 && column1 > 0 && row2 > 0 && column2 > 0);
}

Range::Range(CellReference topLeft, CellReference bottomRight, QObject *parent) :
    QObject(parent),
    d_ptr(new RangePrivate(topLeft, bottomRight, this)) {
}

bool Range::operator==(Range *area) {
    return RangePrivate::isEqual(this, area);
}

bool Range::intersects(Range *range) {
    return d_ptr->intersects(range);
}

QList<Range*> Range::intersections(Range *range) {
    return d_ptr->intersections(range);
}

bool Range::isNull() {
    return d_ptr->isNull();
}

void Range::setRange(int &row1, int &column1, int &row2, int &column2) {
    Q_ASSERT(row1 > 0 && column1 > 0 && row2 > 0 && column2 > 0);
    d_ptr->setRange(row1, column1, row2, column2);
}

Range* Range::removeOverlap(Range *range) {
    return d_ptr->removeOverlap(range);
}

SplitRangeName Range::rangeFromString(const QString &value) {
    return RangePrivate::rangeFromString(value);
}

QString Range::rangeToString(int column, int row, int width, int height) {
    Q_ASSERT(row > 0 && column > 0 && width > 0 && height > 0);
    return RangePrivate::rangeToString(column, row, width, height);
}

QString Range::rangeToString(int &row1, int &column1, bool rowStatic1, bool colStatic1,
                             int &row2, int &column2, bool rowStatic2, bool colStatic2) {
    Q_ASSERT(row1 > 0 && column1 > 0 && row2 > 0 && column2 > 0);
    return RangePrivate::rangeToString(row1, column1, rowStatic1, colStatic1,
                                       row2, column2, rowStatic2, colStatic2);
}

/*!
 * \brief Returns the range of selected cells.
 *
 * Returns a RangeValue struct containing the four values.
 * The values returned are the leftmost \c column, in the
 * topmost \c row, the \c width and the \c height.
 */
RangeValue Range::range() {
    return d_ptr->range();
}

int Range::top() {
    return d_ptr->top();
}

int Range::bottom() {
    return d_ptr->bottom();
}

int Range::left() {
    return d_ptr->left();
}

int Range::right() {
    return d_ptr->right();
}

}

