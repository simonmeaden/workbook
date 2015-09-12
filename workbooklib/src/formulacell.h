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
#ifndef FORMULACELL_H
#define FORMULACELL_H

#include <QObject>
#include <QScopedPointer>

#include "cell.h"
#include "formulacell_p.h"

class FormulaCell : public Cell {
    Q_OBJECT
public:
    explicit FormulaCell(QObject *parent);
    explicit FormulaCell(int row, int column, QObject *parent);
    explicit FormulaCell(int row, int column, const QVariant &value, QObject *parent=0) ;
    explicit FormulaCell(CellReference reference, QVariant &value, QObject *parent=0);
    explicit FormulaCell(CellReference reference, QObject *parent=0);
    ~FormulaCell();

public slots:

protected:
    FormulaCell(FormulaCellPrivate &d, QObject *parent) : Cell(d, parent) {}
    const QScopedPointer<FormulaCell> d_ptr;

private:
    Q_DECLARE_PRIVATE(FormulaCell)

    friend class WorksheetPrivate;
};

#endif // FORMULACELL_H
