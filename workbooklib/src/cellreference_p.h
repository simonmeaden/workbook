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
#ifndef CELLREFERENCE_P_H
#define CELLREFERENCE_P_H

#include <QObject>
#include <QString>
#include <QRegularExpression>

#include <qquad.h>
#include "reference.h"

class CellReference;

class CellReferencePrivate : public Reference {
public:
    explicit CellReferencePrivate();
    explicit CellReferencePrivate(CellReference *parent);

    static QString columnToString(int column);
    static QString rowToString(int row);
    static QString cellToString(int column, int row);
    static QPair<int, int> cellFromString(QString&);
    static int columnFromString(QString&columnRef);
    static int rowFromString(QString&rowRef);

    bool isValid();
    int row() const {
        return mRow;
    }
    int column() const {
        return mColumn;
    }

    Q_DECLARE_PUBLIC(CellReference)
    CellReference *q_ptr;
    int mRow, mColumn;
};



#endif // CELLREFERENCE_P_H
