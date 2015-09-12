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


Range::Range() :
    d_ptr(new RangePrivate(this)) {

}

Range::Range(int &row1, int &column1, int &row2, int &column2) :
    d_ptr(new RangePrivate(row1, column1, row2, column2, this)) {
}

Range::Range(CellReference topLeft, CellReference bottomRight) :
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
    d_ptr->setRange(row1, column1, row2, column2);
}

Range* Range::removeOverlap(Range *range) {
    return d_ptr->removeOverlap(range);
}

QQuad<int, int, int, int> Range::rangeFromString(QString &value) {
    return RangePrivate::rangeFromString(value);
}

QString Range::rangeToString(int column, int row, int width, int height) {
    return RangePrivate::rangeToString(column, row, width, height);
}

/*!
 * \brief Returns the range of selected cells.
 *
 * Returns a QQuad containing the four values.
 * The values returned are in \c first the leftmost column, in the \c second
 * the topmost row, in the \c third the width and in the fourth the height.
 *
 * \return a QQuad containing the range.
 */
QQuad<int, int, int, int> Range::range() {
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
