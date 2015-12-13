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
#ifndef RANGE_H
#define RANGE_H

#include <QObject>
#include <QList>
#include <QScopedPointer>

#include "qquad.h"

#include "cellreference.h"

#include "workbook_global.h"
#include "range_p.h"

namespace QWorkbook {


class WORKBOOKSHARED_EXPORT Range : public QObject {
    Q_DECLARE_PRIVATE(Range)
public:
    explicit Range(QObject *parent);
    explicit Range(int &row1, int &column1, int &row2, int &column2, QObject *parent);
    explicit Range(CellReference topLeft, CellReference bottomRight, QObject *parent);
    virtual ~Range() {}

    static QString rangeToString(int column, int row, int width, int height);
    static QString rangeToString(int &row1, int &column1, bool rowStatic1, bool colStatic1,
                                 int &row2, int &column2, bool rowStatic2, bool colStatic2);
    static SplitRangeName rangeFromString(const QString &);


    QList<Range *> intersections(Range *range);
    bool intersects(Range *range);

    void setRange(int &row1, int &column1, int &row2, int &column2);
    RangeValue range();

    bool operator==(Range *range);
    bool isNull();

    int top();
    int bottom();
    int left();
    int right();

signals:

public slots:

protected:
    QScopedPointer<RangePrivate> d_ptr;

    Range *removeOverlap(Range *range);

private:

};


}

#endif // RANGE_H
