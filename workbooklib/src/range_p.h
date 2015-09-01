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
    RangePrivate(const int &row1, const int &column1, const int &row2, const int &column2, Range *parent);
    RangePrivate(const CellReference topLeft, const CellReference bottomRight, Range *parent);

    static bool isEqual(const Range *a, const Range *b);

    // static functions
    static QString rangeToString(int column, int row, int width, int height);
    static QQuad<int, int, int, int> rangeFromString(QString&);


    // Publicish methods.
    void setRange(const int &row1, const int &column1, const int &row2, const int &column2);
    QQuad<int, int, int, int> range();
    QList<Range *> intersections(const Range *range);
    bool intersects(const Range *range);
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
