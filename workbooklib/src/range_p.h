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

#include <qquad.h>

#include "reference.h"
#include "cellreference.h"

class Range;

class RangePrivate : public Reference {

public:
    RangePrivate(Range *parent);
    RangePrivate(int &row1, int &column1, int &row2, int &column2, Range *parent);
    RangePrivate(CellReference topLeft, CellReference bottomRight, Range *parent);

    static bool isEqual(Range *a, Range *b);

    // static functions
    static QString rangeToString(int column, int row, int width, int height);
    static QQuad<int, int, int, int> rangeFromString(QString&);


    // Publicish methods.
    void setRange(int &row1, int &column1, int &row2, int &column2);
    QQuad<int, int, int, int> range();
    QList<Range *> intersections(Range *range);
    bool intersects(Range *range);
    bool isNull();

    // Privatish methods.
    void normalise();
    Range *removeOverlap(Range *range);

    inline int top() { return mTop; }
    inline int bottom() { return mBottom; }
    inline int left() { return mLeft; }
    inline int right() { return mRight; }

    Q_DECLARE_PUBLIC(Range)
    Range *q_ptr;

    int mTop, mBottom, mLeft, mRight;

};

#endif // RANGEPRIVATE_H
