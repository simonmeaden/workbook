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
#include "range.h"
#include "range_p.h"


Range::Range() :
    d_ptr(new RangePrivate(this)) {

}

Range::Range(const int &row1, const int &column1, const int &row2, const int &column2) :
    d_ptr(new RangePrivate(row1, column1, row2, column2, this)) {
}

Range::Range(const CellReference topLeft, const CellReference bottomRight) :
    d_ptr(new RangePrivate(topLeft, bottomRight, this)) {
}

bool Range::operator==(const Range *area) const {
    return RangePrivate::isEqual(this, area);
}

bool Range::intersects(const Range *range) {
    return d_ptr->intersects(range);
}

QList<Range*> Range::intersections(const Range *range) {
    return d_ptr->intersections(range);
}

bool Range::isNull() {
    return d_ptr->isNull();
}

void Range::setRange(const int &row1, const int &column1, const int &row2, const int &column2) {
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
