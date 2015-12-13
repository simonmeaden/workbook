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
#include <qmath.h>

#include "formatdelegate_p.h"
#include "formatdelegate.h"
#include "worksheetmodel.h"
#include "qworksheetview.h"
#include "format.h"

#include "workbook_global.h"

namespace QWorkbook {

FormatDelegatePrivate::FormatDelegatePrivate(FormatDelegate *parent) :
    q_ptr(parent) {

}

void FormatDelegatePrivate::setOptions(QStyleOptionViewItem &option, const QModelIndex &index) const {

//    QString value = index.model()->data(index, Qt::DisplayRole).toString();
    const WorksheetModel* m = qobject_cast<const WorksheetModel*>(index.model());
    Format *format = m->format(index);
    if (format) {
        option.font = format->font();
        option.font.setBold(format->bold());
        option.font.setItalic(format->italic());
        option.font.setOverline(format->overline());
        option.font.setStrikeOut(format->strikeout());
        option.font.setUnderline(format->underline());

//        // Set the indent level for this cell.
//        // So far only if the cell is a QLabel which I believe it mostly is.
//        int indent = format->indentSize();
//        if (indent > 0) {
//            QLabel *lbl = dynamic_cast<QLabel*>(const_cast<QWidget*>(option.widget));
//            if (lbl)
//                lbl->setIndent(indent);
//        }

        option.displayAlignment = format->alignment();

        option.backgroundBrush = format->backgroundColor();


    }
}

QWidget* FormatDelegatePrivate::createEditor(QWidget *parent,
        const QStyleOptionViewItem option,
        const QModelIndex &index) const {

    QWidget* widget = q_ptr->QStyledItemDelegate::createEditor(parent, option, index);

    QLineEdit *le = dynamic_cast<QLineEdit*>(widget);
    if (le) {
        q_ptr->connect(le, SIGNAL(textChanged(QString)),
                       q_ptr->pView, SIGNAL(cellContentsChanged(QString)), Qt::UniqueConnection);
        q_ptr->connect(q_ptr->pView, SIGNAL(contentsChanged(QString)),
                       le, SIGNAL(textChanged(QString)), Qt::UniqueConnection);
        QPalette p = le->palette();
        // need to reset the highlight colour as the standard one
        // is lost in the edit colour.
        QBrush highlightBrush("cornflowerblue");
        QBrush highlightTextBrush(Qt::white);
        p.setBrush(QPalette::Highlight, highlightBrush);
        p.setBrush(QPalette::HighlightedText, highlightTextBrush);
        le->setPalette(p);
    }

    return widget;
}

void FormatDelegatePrivate::paint(QPainter *painter,
                                  QStyleOptionViewItem &option,
                                  const QModelIndex &index) const {

    setOptions(option, index);

    q_ptr->QStyledItemDelegate::paint(painter, option, index);

    paintBorder(painter, option, index);

}

void FormatDelegatePrivate::paintBorder(QPainter *painter, QStyleOptionViewItem &option, const QModelIndex &index) const {
    const WorksheetModel* m = qobject_cast<const WorksheetModel*>(index.model());
    Format *format = m->format(index);
    painter->save();
    // paint the borders. these all return immediately if not required.
    paintTopBorder(painter, format, option.rect);
    paintLeftBorder(painter, format, option.rect);
    paintBottomBorder(painter, format, option.rect);
    paintRightBorder(painter, format, option.rect);
    painter->restore();
}

void FormatDelegatePrivate::paintRightBorder(QPainter *painter, Format *format, QRect rect) const {
    Border border = format->rightBorder();
    if (!border.isEnabled()) return;

    float thickness;
    QPen pen = painter->pen();

    switch (border.style()) {
    case BS_SINGLE: {// for these the Format::BorderStyle is the same as the Qt::BorderStyle
        pen.setStyle(static_cast<Qt::PenStyle>(border.style()));
        thickness = qRound(border.thickness() * 1.333333333);
        pen.setWidth(thickness);
        pen.setColor(border.color());
        painter->setPen(pen);

        QPointF tr(rect.topRight());
        tr.rx() += (thickness / 2.0)/*1.0*/;
        tr.ry() += (thickness / 2.0);

        QPointF br(rect.bottomRight());
        br.rx() += (thickness / 2.0)/*1.0*/;
        br.ry() += ((thickness / 2.0)/* + 1*/);

        painter->drawLine(tr, br);
        break;
    }
    case BS_DOTTED:
    case BS_LARGEDASH:
    case BS_DASH_DOT:
    case BS_DASH_DOT_DOT: {
        pen.setStyle(static_cast<Qt::PenStyle>(border.style()));
        thickness = qRound(border.thickness() * 1.333333333);
        pen.setWidth(thickness);
        pen.setColor(border.color());
        painter->setPen(pen);

        QPointF tr(rect.topRight());
//        tr.rx() -= /*(thickness / 2.0)*/1;
        tr.ry() += (thickness / 2.0);

        QPointF br(rect.bottomRight());
//        br.rx() -= /*(thickness / 2.0)*/1;
        br.ry() += ((thickness / 2.0)/* + 1*/);

        painter->drawLine(tr, br);
        break;
    }
    case BS_DOUBLE: {  // For this it is different so do it myself

        pen.setWidth(1); // each individual line is only 1 pixel wide.

        // basically the thickness in this case is the gap between the lines.
        float offset = ((border.thickness() * 1.333333333) + 1) / 2.0;
        QPointF topO, bottomO, topI, bottomI;
        Border borderT = format->topBorder();
        Border borderB = format->bottomBorder();

        topI = rect.topRight();
        if (borderT.isEnabled() && borderT.style() == BS_DOUBLE) {
            topI.rx() -= offset;
            topI.ry() += offset;
            topO.rx() += offset;
            topO.ry() -= offset;
        }

        bottomI = rect.bottomRight();
        if (borderB.isEnabled() && borderB.style() == BS_DOUBLE) {
            bottomI.rx() -= offset;
            bottomI.ry() -= offset;
            bottomO.rx() += offset;
            bottomO.ry() += offset;
        }

        painter->setPen(pen);
        painter->drawLine(topI, bottomI);
        painter->drawLine(topO, bottomO);
        break;
    }
    case BS_SMALLDASH: { // For this it is different so do it myself
        QVector<qreal> dashes;
        dashes << 3 << 5;
        pen.setDashPattern(dashes);
        thickness = qRound(border.thickness() * 1.333333333) + 1;
        pen.setWidth(thickness);
        painter->setPen(pen);
        painter->drawLine(rect.topRight(), rect.bottomRight());
        break;
    }
    default:
        break;
    }

}

void FormatDelegatePrivate::paintLeftBorder(QPainter *painter, Format *format, QRect rect) const {
    Border border = format->leftborder();
    if (!border.isEnabled()) return;

    float thickness;
    QPen pen = painter->pen();

    switch (border.style()) {
    case BS_SINGLE: {// for these the Format::BorderStyle is the same as the Qt::BorderStyle
        pen.setStyle(static_cast<Qt::PenStyle>(border.style()));
        thickness = /*qRound(*/border.thickness() * 1.333333333/*)*/;
        pen.setWidth(thickness);
        pen.setColor(border.color());
        painter->setPen(pen);

        QPointF tl(rect.topLeft());
        tl.rx() += (thickness / 2.0)/*1.0*/;
        tl.ry() += (thickness / 2.0);

        QPointF bl(rect.bottomLeft());
        bl.rx() += (thickness / 2.0)/*1.0*/;
        bl.ry() += ((thickness / 2.0)/* + 1*/);

        painter->drawLine(tl, bl);
        break;
    }
    case BS_DOTTED:
    case BS_LARGEDASH:
    case BS_DASH_DOT:
    case BS_DASH_DOT_DOT: {
        pen.setStyle(static_cast<Qt::PenStyle>(border.style()));
        thickness = /*qRound(*/border.thickness() * 1.333333333/*)*/;
        pen.setWidth(thickness);
        pen.setColor(border.color());
        painter->setPen(pen);

        QPointF tl(rect.topLeft());
        tl.rx() += /*(thickness / 2.0)*/1;
        tl.ry() += (thickness / 2.0);

        QPointF bl(rect.bottomLeft());
        bl.rx() += /*(thickness / 2.0)*/1;
        bl.ry() += ((thickness / 2.0)/* + 1*/);

        painter->drawLine(tl, bl);
        break;
    }
    case BS_DOUBLE: {  // For this it is different so do it myself

        // basically the thickness in this case is the gap between the lines.
        float offset = ((border.thickness() * 1.333333333) + 1) / 2.0;
        QPointF topO, bottomO, topI, bottomI;
        Border borderT = format->topBorder();
        Border borderB = format->bottomBorder();

        topI = rect.topLeft();
        if (borderT.isEnabled() && borderT.style() == BS_DOUBLE) {
            topI.rx() += offset;
            topI.ry() += offset;
            topO.rx() -= offset;
            topO.ry() -= offset;
        }

        bottomI = rect.bottomLeft();
        if (borderB.isEnabled() && borderB.style() == BS_DOUBLE) {
            bottomI.rx() += offset;
            bottomI.ry() -= offset;
            bottomO.rx() -= offset;
            bottomO.ry() += offset;
        }

        painter->setPen(pen);
        painter->drawLine(topI, bottomI);
        painter->drawLine(topO, bottomO);
        break;
    }
    case BS_SMALLDASH: { // For this it is different so do it myself
        QVector<qreal> dashes;
        dashes << 3 << 5;
        pen.setDashPattern(dashes);
        thickness = qRound(border.thickness() * 1.333333333) + 1;
        pen.setWidth(thickness);
        painter->setPen(pen);
        painter->drawLine(rect.topLeft(), rect.bottomLeft());
        break;
    }
    default:
        break;
    }

}

void FormatDelegatePrivate::paintBottomBorder(QPainter *painter, Format *format, QRect rect) const {
    Border border = format->bottomBorder();
    if (!border.isEnabled()) return;

    float thickness;
    QPen pen = painter->pen();

    switch (border.style()) {
    case BS_SINGLE: {// for these the Format::BorderStyle is the same as the Qt::BorderStyle
        pen.setStyle(static_cast<Qt::PenStyle>(border.style()));
        thickness = qRound(border.thickness() * 1.333333333);
        pen.setWidth(thickness);
        pen.setColor(border.color());
        painter->setPen(pen);

        QPointF bl(rect.bottomLeft());
        bl.rx() += (thickness / 2.0);
        bl.ry() += (thickness / 2.0)/*2.0*/;

        QPointF br(rect.bottomRight());
        br.rx() += ((thickness / 2.0)/* + 1*/);
        br.ry() += (thickness / 2.0)/*2.0*/;

        painter->drawLine(bl, br);
        break;
    }
    case BS_DOTTED:
    case BS_LARGEDASH:
    case BS_DASH_DOT: {
        pen.setStyle(static_cast<Qt::PenStyle>(border.style()));
        thickness = qRound(border.thickness() * 1.333333333);
        pen.setWidth(thickness);
        pen.setColor(border.color());
        painter->setPen(pen);

        QPointF bl(rect.bottomLeft());
        bl.rx() += (thickness / 2.0);
        bl.ry() += /*(thickness / 2.0)*/1.0;

        QPointF br(rect.bottomRight());
        br.rx() += ((thickness / 2.0)/* + 1*/);
        br.ry() += /*(thickness / 2.0)*/1.0;

        painter->drawLine(bl, br);
        break;
    }
    case BS_DOUBLE: {  // For this it is different so do it myself

        pen.setWidth(1); // each individual line is only 1 pixel wide.

        float offset = ((border.thickness() * 1.333333333) + 1) / 2.0;
        QPointF topO, bottomO, topI, bottomI;
        Border borderL = format->leftborder();
        Border borderR = format->rightBorder();

        topI = rect.topLeft();
        if (borderL.isEnabled() && borderL.style() == BS_DOUBLE) {
            topI.rx() += offset;
            topI.ry() += offset;
            topO.rx() -= offset;
            topO.ry() -= offset;
        }

        bottomI = rect.bottomLeft();
        if (borderR.isEnabled() && borderR.style() == BS_DOUBLE) {
            bottomI.rx() += offset;
            bottomI.ry() -= offset;
            bottomO.rx() -= offset;
            bottomO.ry() += offset;
        }

        painter->setPen(pen);
        painter->drawLine(topI, bottomI);
        painter->drawLine(topO, bottomO);
        break;
    }
    case BS_SMALLDASH: { // For this it is different so do it myself
        QVector<qreal> dashes;
        dashes << 3 << 5;
        pen.setDashPattern(dashes);
        thickness = qRound(border.thickness() * 1.333333333) + 1;
        pen.setWidth(thickness);
        painter->setPen(pen);
        painter->drawLine(rect.bottomLeft(), rect.bottomRight());
        break;
    }
    default:
        break;
    }
}

void FormatDelegatePrivate::paintTopBorder(QPainter *painter, Format *format, QRect rect) const {
    Border border = format->topBorder();
    if (!border.isEnabled()) return;

    float thickness;
    QPen pen = painter->pen();

    switch (border.style()) {
    case BS_SINGLE: {// for these the Format::BorderStyle is the same as the Qt::BorderStyle
        pen.setStyle(static_cast<Qt::PenStyle>(border.style()));
        thickness = qRound(border.thickness() * 1.333333333);
        pen.setWidth(thickness);
        pen.setColor(border.color());
        painter->setPen(pen);

        QPointF tl(rect.topLeft());
        tl.rx() += (thickness / 2.0);
        tl.ry() += (thickness / 2.0);

        QPointF tr(rect.topRight());
        tr.rx() += ((thickness / 2.0)/* + 1*/);
        tr.ry() += (thickness / 2.0);

        painter->drawLine(tl, tr);
        break;
    }
    case BS_DOTTED:
    case BS_LARGEDASH:
    case BS_DASH_DOT:
    case BS_DASH_DOT_DOT: {
        pen.setStyle(static_cast<Qt::PenStyle>(border.style()));
        thickness = qRound(border.thickness() * 1.333333333);
        pen.setWidth(thickness);
        pen.setColor(border.color());
        painter->setPen(pen);

        QPointF tl(rect.topLeft());
        tl.rx() += (thickness / 2.0);
        tl.ry() += (thickness / 2.0);

        QPointF tr(rect.topRight());
        tr.rx() += ((thickness / 2.0)/* + 1*/);
        tr.ry() += (thickness / 2.0);

        painter->drawLine(tl, tr);
//        painter->drawLine(rect.topLeft(), rect.topRight());
        break;
    }
    case BS_DOUBLE: {  // For this it is different so do it myself

        pen.setStyle(Qt::SolidLine);
        pen.setWidth(1); // each individual line is only 1 pixel wide.
        pen.setColor(border.color());

        // basically the thickness in this case is the gap between the lines.
        float offset = float(qRound(((border.thickness() * 1.333333333) + 1))) / 2.0;
        QPointF leftO, rightO, leftI, rightI;
        Border borderL = format->leftborder();
        Border borderR = format->rightBorder();

        leftO = rect.topLeft();
        leftI = leftO;
        if (borderL.isEnabled() && borderL.style() == BS_DOUBLE) {
            leftO.rx() -= offset;
            leftO.ry() -= offset;
            leftI.rx() += offset;
            leftI.ry() += offset;
        }

        rightO = rect.topRight();
        rightI = rightO;
        if (borderR.isEnabled() && borderR.style() == BS_DOUBLE) {
            rightO.rx() += offset;
            rightO.ry() -= offset;
            rightI.rx() -= offset;
            rightI.ry() += offset;
        }

        painter->setPen(pen);
        painter->drawLine(leftO, rightO);
        painter->drawLine(leftI, rightI);
        break;
    }
    case BS_SMALLDASH: { // For this it is different so do it myself
        QVector<qreal> dashes;
        dashes << 3 << 5;
        pen.setDashPattern(dashes);
        thickness = qRound(border.thickness() * 1.333333333) + 1;
        pen.setWidth(thickness);
        pen.setColor(border.color());
        painter->setPen(pen);
        painter->drawLine(rect.topLeft(), rect.topRight());
        break;
    }
    default:
        break;
    }
}

}

