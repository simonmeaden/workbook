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
#include "formatdelegate.h"
#include "formatdelegate_p.h"
#include "cell.h"
#include "format.h"
#include "worksheetmodel.h"
#include "qworksheetview.h"

FormatDelegate::FormatDelegate(QWorksheetView *parent) :
    QStyledItemDelegate(parent),
    pView(parent),
    d_ptr(new FormatDelegatePrivate(this)) {

}

FormatDelegate::~FormatDelegate() {

}

void FormatDelegate::paint(QPainter *painter, const
                           QStyleOptionViewItem &option,
                           const QModelIndex &index) const {

    QStyleOptionViewItem opt = option;

    initStyleOption(&opt, index);

    d_ptr->paint(painter, opt, index);

}

QWidget* FormatDelegate::createEditor(QWidget *parent,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const {

    return d_ptr->createEditor(parent, option, index);

}
