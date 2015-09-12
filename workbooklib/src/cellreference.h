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
#ifndef CELLREFERENCE_H
#define CELLREFERENCE_H

#include <QObject>
#include <QString>
#include <QScopedPointer>

#include <workbook_global.h>
#include "cellreference_p.h"

class WORKBOOKSHARED_EXPORT CellReference : public QObject {
    Q_OBJECT
public:
    explicit CellReference();
    explicit CellReference(QObject *parent);
    explicit CellReference(int row, int column, QObject *parent);
    explicit CellReference(QString reference, QObject *parent);
    CellReference(CellReference &d) :
        QObject(d.parent()),
        d_ptr(new CellReferencePrivate(&d)) {
    }

    bool operator==(const CellReference& comp) {
        return ((this->row() == comp.row()) && (this->column() == comp.column()));
    }
    bool operator<(const CellReference& comp) {
        return ((this->row() < comp.row()) && (this->column() < comp.column()));
    }
    bool operator> (const CellReference& comp) {
        return ((this->row() > comp.row()) && (this->column() > comp.column()));
    }
    bool operator<=(const CellReference& comp) {
        return ((this->row() <= comp.row()) && (this->column() <= comp.column()));
    }
    bool operator>=(const CellReference& comp) {
        return ((this->row() >= comp.row()) && (this->column() >=comp.column()));
    }
    bool operator!=(const CellReference& comp) {
        return !((this->row() == comp.row()) && (this->column() == comp.column()));
    }

    static QString columnToString(int column);
    static QString rowToString(int row);
    static QString cellToString(int column, int row);
    static QPair<int, int> cellFromString(QString&);
    static int columnFromString(QString&);
    static int rowFromString(QString&);

    bool isValid();
    int row() const;
    int column() const;
    void setRow(int&);
    void setColumn(int &);
    void setPosition(int&, int&);
    void setPosition(QString &reference);
    QString toString();

signals:

public slots:

protected:
    const QScopedPointer<CellReferencePrivate> d_ptr;
    CellReference(CellReferencePrivate &d, QObject *parent) :
        QObject(parent),
        d_ptr(&d) {
    }

private:
    Q_DECLARE_PRIVATE(CellReference)

};



#endif // CELLREFERENCE_H
