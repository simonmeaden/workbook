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
#include "range_p.h"
#include "range.h"
#include "cellreference.h"


#include "workbook_global.h"

namespace QWorkbook {

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

RangePrivate::RangePrivate(int &row1, int &column1, bool rowStatic1, bool colStatic1,
                           int &row2, int &column2, bool rowStatic2, bool colStatic2, Range *parent) :
    q_ptr(parent),
    mTop(row1),
    mBottom(row2),
    mLeft(column1),
    mRight(column2),
    bRowStatic1(rowStatic1),
    bRowStatic2(rowStatic2),
    bColStatic1(colStatic1),
    bColStatic2(colStatic2) {

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

RangeValue RangePrivate::range() {
    RangeValue range;
    range.column = mLeft;
    range.row = mTop;
    range.width = mRight - mLeft;
    range.height = mBottom - mTop;
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
    \brief Checks for an intersection of two areas.

    \param area The \cArea to check against.
    \return true if there is an overlap between the two \c Area's.
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
    \brief Returns the areas of this area which will need to be resaved.

    The list that is returned are the areas of the existing \c Range which
    are NOT overlapped by the supplied \c Range. The \c Area that is overlapped
    by the new area will be discarded.

    Generally this will be three areas, depending on where the overlap occurs. If
    the supplied \c Range is a) smaller and b) totally inside the old area then
    there will be four. If they are the same sixe and the same position then there
    will not be  any.
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
            a = new Range(mTop, mLeft, maxTop, mRight, q_ptr->parent());
        }
    }

    if (range->d_ptr->mLeft < mLeft) {
        if (mLeft != maxLeft) {
            b = new Range(mLeft, mTop, mRight, maxLeft, q_ptr->parent());
        }
    }

    if (range->d_ptr->mRight < mRight) {
        if (mRight != minRight) {
            c = new Range(mTop, minRight, mBottom, mRight, q_ptr->parent());
        }
    }

    if (range->d_ptr->mBottom < mBottom) {
        if (mBottom != minBottom) {
            d = new Range(minBottom, mLeft, mBottom, mRight, q_ptr->parent());
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

SplitRangeName RangePrivate::rangeFromString(const QString value) {

    return Reference::rangeFromString(value);

}

QString RangePrivate::rangeToString(int column, int row, int width, int height) {
    QString result = Reference::columnToString(column) + Reference::rowToString(row);
    result += ":";
    result += Reference::columnToString(column + width - 1) + Reference::rowToString(row + height - 1);
    return result;
}

QString RangePrivate::rangeToString(int &row1, int &column1, bool rowStatic1, bool colStatic1,
                                    int &row2, int &column2, bool rowStatic2, bool colStatic2) {
    QString result =
        (rowStatic1 ? "$" : "") +
        Reference::columnToString(column1) +
        (colStatic1 ? "$" : "") +
        Reference::rowToString(row1) +
        ":" +
        (rowStatic2 ? "$" : "") +
        Reference::columnToString(column2) +
        (colStatic2 ? "$" : "") +
        Reference::rowToString(row2);

    return result;
}


}

