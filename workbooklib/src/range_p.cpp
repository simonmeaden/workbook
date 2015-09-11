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
#include "range_p.h"
#include "range.h"
#include "cellreference.h"


RangePrivate::RangePrivate(Range *parent) :
    q_ptr(parent),
    mTop(0),
    mBottom(0),
    mLeft(0),
    mRight(0) {

}

RangePrivate::RangePrivate(int &row1, int &column1, int &row2, int &column2, Range *parent) :
    q_ptr(parent),
    mTop(row1),
    mBottom(row2),
    mLeft(column1),
    mRight(column2) {

    normalise();

}

RangePrivate::RangePrivate(CellReference topLeft, CellReference bottomRight, Range *parent) :
    q_ptr(parent),
    mTop(topLeft.row()),
    mBottom(bottomRight.row()),
    mLeft(topLeft.column()),
    mRight(bottomRight.column()) {

    normalise();

}

void RangePrivate::setRange(int &row1, int &column1, int &row2, int &column2) {
    mTop = row1;
    mBottom = row2;
    mLeft = column1;
    mRight = column2;

    normalise();
}

QQuad<int, int, int, int> RangePrivate::range() {
    QQuad<int, int, int, int> range;
    range.first = mLeft;
    range.second = mTop;
    range.third = mRight - mLeft;
    range.fourth = mBottom - mTop;
    return range;
}


void RangePrivate::normalise() {
    // normalise left/right/top/bottom positions (bottom > top right > left.
    if (mTop > mBottom) {
        int t = mTop;
        mTop = mBottom;
        mBottom = t;
    }

    if (mLeft > mRight) {
        int t = mLeft;
        mLeft = mRight;
        mRight = t;
    }
}


bool RangePrivate::isEqual(Range *a, Range *b) {
    return (a->d_ptr->mRight == b->d_ptr->mRight &&
            a->d_ptr->mLeft == b->d_ptr->mLeft &&
            a->d_ptr->mTop == b->d_ptr->mTop &&
            a->d_ptr->mBottom == b->d_ptr->mBottom);
}

bool RangePrivate::isNull() {
    return (mTop == 0 && mRight == 0 && mLeft == 0 && mBottom == 0);
}

/*!
 * \brief Checks for an intersection of two areas.
 *
 * \param area The \cArea to check against.
 * \return true if there is an overlap between the two \c Area's.
 */
bool RangePrivate::intersects(Range *range) {
    if (range->d_ptr->mBottom < mTop) // area completely  above this
        return false;

    if(mBottom < range->d_ptr->mTop) // this completely above area
        return false;

    if (range->d_ptr->mRight < mLeft) // area to left of this
        return false;

    if (mRight < range->d_ptr->mLeft) // this left of area
        return false;

    return true;
}

/*!
 * \brief Returns the areas of this area which will need to be resaved.
 *
 * The list that is returned are the areas of the existing \c Area which
 * are NOT overlapped by the supplied \c Area. The \c Area that is overlapped
 * by the new area will be discarded.
 *
 * Generally this will be three areas, depending on where the overlap occurs. If
 * the supplied \c Area is a) smaller and b) totally inside the old area then
 * there will be four. If they are the same sixe and the same position then there
 * will not be  any.
 *
 * \param area the new area.
 * \return a list of \c Area objects that will be redone.
 */
QList<Range*> RangePrivate::intersections(Range *range) {
    int maxLeft   = qMax<int>(mLeft, range->d_ptr->mLeft);
    //    int minLeft   = qMin<int>(mLeft, area.mLeft);
    int minRight  = qMin<int>(mRight, range->d_ptr->mRight);
    //    int maxRight  = qMax<int>(mRight, area.mRight);
    int maxTop    = qMax<int>(mTop, range->d_ptr->mTop);
    //    int minTop    = qMin<int>(mTop, area.mTop);
    int minBottom = qMin<int>(mBottom, range->d_ptr->mBottom);
    //    int maxBottom = qMax<int>(mBottom, area.mBottom);

    QList<Range*> list;

    if (range == q_ptr) return list;

    Range *a = NULL, *b = NULL, *c = NULL, *d = NULL;

    if (range->d_ptr->mTop < mTop) {
        if (mTop != maxTop) {
            a = new Range(mTop, mLeft, maxTop, mRight);
        }
    }

    if (range->d_ptr->mLeft < mLeft) {
        if (mLeft != maxLeft) {
            b = new Range(mLeft, mTop, mRight, maxLeft);
        }
    }

    if (range->d_ptr->mRight < mRight) {
        if (mRight != minRight) {
            c = new Range(mTop, minRight, mBottom, mRight);
        }
    }

    if (range->d_ptr->mBottom < mBottom) {
        if (mBottom != minBottom) {
            d = new Range(minBottom, mLeft, mBottom, mRight);
        }
    }

    if (a != NULL) {
        b = a->removeOverlap(b);
        c = a->removeOverlap(c);
        d = a->removeOverlap(d);
        list.append(a);
    }

    if (b != NULL) {
        c = b->removeOverlap(c);
        d = b->removeOverlap(d);
        list.append(b);
    }

    if (c != NULL) {
        d = c->removeOverlap(d);
        list.append(c);
    }

    if (d != NULL)
        list.append(d);

    return list;
}

Range* RangePrivate::removeOverlap(Range *range) {
    if (range == NULL) return NULL;

    if (mTop == range->d_ptr->mTop || mBottom == range->d_ptr->mBottom) {
        if (mLeft == range->d_ptr->mLeft) {
            range->d_ptr->mLeft = mRight;
        } else if (mRight == range->d_ptr->mRight) {
            range->d_ptr->mRight = mLeft;
        }
    } /*else if (mBottom == range->d_ptr->mBottom) {
        if (mLeft == range->d_ptr->mLeft) {
            range->d_ptr->mLeft = mRight;
        } else if (mRight == range->d_ptr->mRight) {
            range->d_ptr->mRight = mLeft;
        }
    } */
    return range;
}

QQuad<int, int, int, int> RangePrivate::rangeFromString(QString &rangeRef) {

    QQuad<QString, QString, QString, QString> m_quad = init(rangeRef);

    QQuad<int, int, int, int> result;
    if (!m_quad.first.isEmpty() && !m_quad.second.isEmpty() && !m_quad.third.isEmpty() && !m_quad.fourth.isEmpty()) {
        result.first = CellReference::columnFromString(m_quad.first);
        result.second = CellReference::rowFromString(m_quad.second);
        result.third = CellReference::columnFromString(m_quad.third);
        result.fourth = CellReference::rowFromString(m_quad.fourth);
    }

    return result;

}

QString RangePrivate::rangeToString(int column, int row, int width, int height) {
    QString result = CellReference::columnToString(column) + CellReference::rowToString(row);
    result += ":";
    result += CellReference::columnToString(column + width - 1) + CellReference::rowToString(row + height - 1);
    return result;
}

