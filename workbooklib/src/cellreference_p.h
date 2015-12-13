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

#include "workbook_global.h"

namespace QWorkbook {

class CellReference;

class CellReferencePrivate : public Reference {
public:
    explicit CellReferencePrivate();
    explicit CellReferencePrivate(CellReference *parent);
    virtual ~CellReferencePrivate() {}

    bool isValid();
    int row() const {
        return mRow;
    }
    int column() const {
        return mColumn;
    }
    void setPosition(int&, int&);
    void setPosition(int&, int&, bool&, bool&);
    void setPosition(QString &reference);
    QString toString();


    Q_DECLARE_PUBLIC(CellReference)
    CellReference *q_ptr;
    int mRow, mColumn;
    bool bStaticRow, bStaticColumn;
};


}

#endif // CELLREFERENCE_P_H
