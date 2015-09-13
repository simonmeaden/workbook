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

class MergedCell : public Cell {
    Q_OBJECT
public:

    explicit MergedCell(QObject *parent);
    explicit MergedCell(int row, int column, QObject *parent);
    explicit MergedCell(int row, int column, const QVariant &value, QObject *parent=0) ;
    explicit MergedCell(CellReference reference, QVariant &value, QObject *parent=0);
    explicit MergedCell(CellReference reference, QObject *parent=0);
    ~MergedCell();

    QList<Cell*> overwritten();

public slots:
    void setOverwritten(QList<Cell*> cells);
    void setMergedData();
    void setFirstCell();

protected:
    MergedCell(MergedCellPrivate &d, QObject *parent) : Cell(d, parent) {}

private:
    Q_DECLARE_PRIVATE(MergedCell)

    friend class WorksheetPrivate;
};

#endif // MERGEDCELL_H
