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
#ifndef CELL_H
#define CELL_H

#include <QObject>
#include <QDebug>
#include <QMetaType>
#include <QScopedPointer>
#include <QModelIndex>

#include "types.h"
#include "cell_p.h"

#include "workbook_global.h"

namespace QWorkbook {

class CellReference;

class Cell : public QObject {
    Q_OBJECT
public:
    explicit Cell();
    explicit Cell(QObject *parent);
    explicit Cell(QModelIndex&, QObject *parent);
    explicit Cell(QModelIndex&, QVariant, QObject *parent);
    explicit Cell(int row, int column, QObject *parent);
    explicit Cell(int row, int column, QVariant, QObject *parent) ;
    explicit Cell(CellReference reference, QVariant value, QObject *parent);
    explicit Cell(CellReference reference, QObject *parent);
    Cell(const Cell&);
    virtual ~Cell() {}

    QVariant value() const;
    int row() const;
    int column() const;
    bool empty();
    bool locked();
//    CellType type();
    bool isEmpty();

    QString toString();
    QString name();


signals:
    void lock(bool);
    void cellChanged(Cell*);

public slots:

    void setPosition(int &row, int &column);
    void setPosition(CellReference &reference);
    void setValue(const QVariant value);
    void setLocked(bool locked);
    void setName(QString name);

protected:
    Cell(CellPrivate &d, QObject *parent) :
        QObject(parent),
        d_ptr(&d) {}
    const QScopedPointer<CellPrivate> d_ptr;

private:
    Q_DECLARE_PRIVATE(Cell)

    friend class WorksheetPrivate;
};




}

Q_DECLARE_METATYPE(QWorkbook::Cell)

#endif // CELL_H

