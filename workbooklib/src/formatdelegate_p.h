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
#ifndef FORMATDELEGATEPRIVATE_H
#define FORMATDELEGATEPRIVATE_H

#include <QObject>
#include <QLabel>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QTextDocument>
#include <QTextCharFormat>
#include <QTextCursor>
#include <QBrush>

class FormatDelegate;
class Format;

class FormatDelegatePrivate {
public:
    FormatDelegatePrivate(FormatDelegate *parent);
    ~FormatDelegatePrivate();

    void setOptions(QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paintBorder(QPainter *painter, QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paintTopBorder(QPainter *painter, Format *format, QRect rect) const;
    void paintBottomBorder(QPainter *painter, Format *format, QRect rect) const;
    void paintLeftBorder(QPainter *painter, Format *format, QRect rect) const;
    void paintRightBorder(QPainter *painter, Format *format, QRect rect) const;

    FormatDelegate *q_ptr;
    Q_DECLARE_PUBLIC(FormatDelegate)
};

#endif // FORMATDELEGATEPRIVATE_H
