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
#ifndef MERGEDCELL_H
#define MERGEDCELL_H

#include <QObject>
#include <QScopedPointer>

#include "cell.h"
#include "mergedcell_p.h"

#include "workbook_global.h"

namespace QWorkbook {

class MergedCell : public Cell {
    Q_OBJECT
public:

    explicit MergedCell(QObject *);
    explicit MergedCell(int , int , int , int , QObject *);
    explicit MergedCell(int , int, int, int, const QVariant &, QObject *) ;
    explicit MergedCell(CellReference, int , int , QObject *);
    explicit MergedCell(CellReference, CellReference, QObject *);
    explicit MergedCell(CellReference, int, int, QVariant &, QObject *);
    explicit MergedCell(CellReference, CellReference, QVariant &, QObject *);
    virtual ~MergedCell() {}

    QList<Cell*> overwritten();
    int rowSpan();
    int columnSpan();

public slots:
    void setOverwritten(QList<Cell*> cells);
    void setMergedData();
    void setFirstCell();

protected:
    MergedCell(MergedCellPrivate &d, QObject *parent) : Cell(d, parent) {}
    int mRowSpan, mColumnSpan;

private:
    Q_DECLARE_PRIVATE(MergedCell)

    friend class WorksheetPrivate;
};


}

#endif // MERGEDCELL_H
