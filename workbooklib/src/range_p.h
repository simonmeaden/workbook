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
#ifndef RANGEPRIVATE_H
#define RANGEPRIVATE_H

#include <QObject>
#include <QList>
#include <QRegularExpression>

#include "reference.h"
#include "cellreference.h"

#include "workbook_global.h"

namespace QWorkbook {

class Range;

struct RangeValue {
    int row, column, width, height;
};

class RangePrivate : public Reference {
    Q_DECLARE_PUBLIC(Range)
public:
    RangePrivate(Range *parent);
    RangePrivate(int &row1, int &column1, int &row2, int &column2, Range *parent);
    RangePrivate(int &row1, int &column1, bool rowStatic1, bool colStatic1,
                 int &row2, int &column2, bool rowStatic2, bool colStatic2, Range *parent);
    RangePrivate(CellReference topLeft, CellReference bottomRight, Range *parent);
    virtual ~RangePrivate() {}

    static bool isEqual(Range *a, Range *b);

    // static functions
    static QString rangeToString(int column, int row, int width, int height);
    static QString rangeToString(int &row1, int &column1, bool rowStatic1, bool colStatic1,
                                 int &row2, int &column2, bool rowStatic2, bool colStatic2);
    static SplitRangeName rangeFromString(const QString);


    // Publicish methods.
    void setRange(int &row1, int &column1, int &row2, int &column2);
    RangeValue range();
    QList<Range *> intersections(Range *range);
    bool intersects(Range *range);
    bool isNull();

    // Privatish methods.
    void normalise();
    Range *removeOverlap(Range *range);

    int top() { return mTop; }
    int bottom() { return mBottom; }
    int left() { return mLeft; }
    int right() { return mRight; }

    Range *q_ptr;

    int mTop, mBottom, mLeft, mRight;
    bool bRowStatic1, bRowStatic2, bColStatic1, bColStatic2;

};


}

#endif // RANGEPRIVATE_H
