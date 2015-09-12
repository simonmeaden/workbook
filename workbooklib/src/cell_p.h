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
#ifndef CELL_P_H
#define CELL_P_H

#include <QObject>
#include <QVariant>

#include <qquad.h>

#include "types.h"

namespace QXlsx {
    class Cell;
    class Worksheet;
}

class Cell;
class Format;

class CellPrivate {
    Q_DECLARE_PUBLIC(Cell)
public:
    CellPrivate();
    CellPrivate(Cell *q);

    int mRow;
    inline int row() const {
        return mRow;
    }

    int mColumn;
    inline int column() const {
        return mColumn;
    }

    QVariant mValue;
    QVariant value() const;
    void setValue(QVariant &value);

    bool isEmpty();

    bool bLocked;
    inline bool locked() { return bLocked; }
    void setLocked(bool locked);

    CellType mType;
    CellType type();

    QString toString();

    QString mName;
    QString name();
    void setName(QString name);

protected:
    Cell *q_ptr;


};

#endif // CELL_P_H
