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
#ifndef REFERENCE_H
#define REFERENCE_H

#include <QString>
#include <QRegularExpression>
#include <QtMath>

#include <qquad.h>
#include "regex.h"
#include "types.h"

#include "workbook_global.h"

namespace QWorkbook {

struct SplitCellName {

    int row, column;
    bool isGood, rowStatic, colStatic;

    bool isValid() {
        return (row >= 0 && column >= 0);
    }
};
struct SplitRangeName {

    SplitCellName from, to;

    bool isValid() {
        return (from.isValid() && to.isValid());
    }

};

/*!
    \brief The Reference class is the base class for several different classes.

    Mainly supplies static conversion methods for use converting cell reference
    names to row & column positions.
*/
class Reference {
public:
    Reference() {}
    virtual ~Reference() {}

protected:


    static QString cellToString(int column, int row) {
        QString result =  columnToString(column) + rowToString(row);
        return result;
    }

    /*!
        /brief Converts a table row value to an spreadsheet row value.

        Note : Spreadsheet offsets start at 1 while most others start at 0. The
        function increments to allow zero based offsets.

        Row is easy as it just a number a1 - n
    */
    static QString rowToString(int row) {
        QString result =  QString::number(row + 1);
        return result;
    }
    /*!
        \brief Converts a spreadsheet numerical row string to it's table row number.

        Static method that converts a numerical one based row number to it's
        zero based row number or -1 if the number is invalid.
    */
    static int rowFromString(QString rowRef) {

        bool test;
        int row = rowRef.toInt(&test);

        if (test) // rows are 1 based, indexes to the table are 0 based.
            return row - 1;
        return -1;
    }

    /*!
        \brief Converts a cell reference to it's row/column numerical values.
    */
    static SplitCellName cellFromString(QString cellRef) {

        SplitRangeName range = init(cellRef);

        return range.from;

    }

    /*!
        \brief Converts a range reference to it's row/column numerical values.
    */
    static SplitRangeName rangeFromString(QString cellRef) {

        SplitRangeName range = init(cellRef);

        return range;

    }

    static SplitRangeName init(QString ref) {

        SplitRangeName range;

        QRegularExpression re = QRegularExpression(REGEX_ROW);
        QRegularExpressionMatch match = re.match(ref);
        if (re.captureCount() == 1) {
            if (match.hasMatch()) {
                range.from.row = match.captured(0).toInt();
                range.to.row = -1;
            }
        } else if (re.captureCount() == 2) {
            if (match.hasMatch()) {
                range.from.row = match.captured(0).toInt();
                range.to.row = match.captured(2).toInt();
            }
        }

        re = QRegularExpression(REGEX_COLUMN);
        match = re.match(ref);
        if (re.captureCount() == 1) {
            if (match.hasMatch()) {
                range.from.column = columnFromString(match.captured(0));
                range.from.column = -1;
            }
        } else if (re.captureCount() == 2) {
            if (match.hasMatch()) {
                range.from.column = columnFromString(match.captured(0));
                range.from.column = columnFromString(match.captured(2));
            }
        }

        return range;

    }

protected:
    /*!
        \brief Converts a spreadsheet numerical column string to it's table column number.

        A = 0, B = 1, AA = 27 etc.

    */
    static int columnFromString(QString columnRef) {
        int result = colFromString(columnRef) - 1;
        return result;
    }

private:
    static int colFromString(QString column) {
        char c = column.right(1).toLatin1().at(0);
        QString rest = column.left(column.length() - 1);
        int result = (c - 'A' + 1);

        if (rest.length() > 0)
            result += (colFromString(rest) * 26);

        return result;
    }

protected:
    /*!
        \brief Converts a table column value to an spreadsheet column value A - Z, AA - ZZ.

        Note : Spreadsheet offsets start at 1 while tables start at 0. The
        function increments to allow zero based offsets.

        0 = A
        1 = B
        ...
        26 = AA
        27 = AB etc.
    */
    static QString columnToString(int column) {


        QString result = colToString(column);

        return result;
    }

private:
    static QString colToString(int column) {
        int divisor = 26;
        int mod = column % divisor;
        int div = column / divisor;

        QString result(mod + 'A');

        if (div > 0)
            result.prepend(colToString(div - 1));

        return result;
    }

};


}

#endif // REFERENCE_H
