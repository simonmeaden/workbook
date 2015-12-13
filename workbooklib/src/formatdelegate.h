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
#ifndef FORMATDELEGATE_H
#define FORMATDELEGATE_H

#include <QObject>
#include <QLabel>
#include <QStyledItemDelegate>
#include <QScopedPointer>

#include "workbook_global.h"
#include "formatdelegate_p.h"

namespace QWorkbook {

class QWorksheetView;

class FormatDelegate : public QStyledItemDelegate {
    Q_DECLARE_PRIVATE(FormatDelegate)
public:
    FormatDelegate(QWorksheetView *parent);
    virtual ~FormatDelegate() {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

public slots:

protected:
    QWorksheetView *pView;
    const QScopedPointer<FormatDelegatePrivate> d_ptr;

};


}

#endif // FORMATDELEGATE_H
