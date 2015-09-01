/*
 * This Workbook library is © Simon Meaden 2015. It is licensed under the LGPL V3 license.
 *
 * This Workbook library dynamically links to unmodified Nokia Qt5 Library. The Qt5
 * Library is © 2011 Nokia Corporation and/or its subsidiary(-ies), and is licensed
 * under the GNU Lesser General Public License version 2.1 with Nokia Qt LGPL exception
 * version 1.1.
 *
 * Qt5 library is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License, version 2.1, as published by the
 * Free Software Foundation.
 *
 * Qt5 library is provided “AS IS”, without WARRANTIES OR CONDITIONS OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY WARRANTIES OR CONDITIONS OF
 * TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 * As an additional permission to the GNU Lesser General Public License version 3.0, the
 * object code form of a “work that uses the Library” may incorporate material from a
 * header file that is part of the Library. You may distribute such object code under
 * terms of your choice, provided that: (i) the header files of the Library have not
 * been modified; and (ii) the incorporated material is limited to numerical parameters,
 * data structure layouts, accessors, macros, inline functions and templates; and (iii)
 * you comply with the terms of Section 6 of the GNU Lesser General Public License version 3.0.
 *
 * Moreover, you may apply this exception to a modified version of the Library, provided
 * that such modification does not involve copying material from the Library into the
 * modified Library’s header files unless such material is limited to (i) numerical
 * parameters; (ii) data structure layouts; (iii) accessors; and (iv) small macros,
 * templates and inline functions of five lines or less in length.
 *
 * Furthermore, you are not required to apply this additional permission to a modified
 * version of the Library.
 *
 * You should have received a copy of the GNU Lesser General Public License along
 * with this package; if not, write to the Free Software Foundation, Inc., 51 Franklin
 * Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * The source code for Qt 5.4.X SDK is available from Nokia here:
 * http://get.qt.nokia.com/qt/source/qt-everywhere-opensource-src-4.7.X.zip.
 *
 * It is also available on request from Simon Meaden info@smelecomp.co.uk.
 */


#include <qmath.h>

#include "formatdelegate_p.h"
#include "formatdelegate.h"
#include "worksheetmodel.h"
#include "format.h"

FormatDelegatePrivate::FormatDelegatePrivate(FormatDelegate *parent) :
    q_ptr(parent) {

}

FormatDelegatePrivate::~FormatDelegatePrivate() {

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
    case SINGLE: {// for these the Format::BorderStyle is the same as the Qt::BorderStyle
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
    case DOTTED:
    case LARGEDASH:
    case DASH_DOT:
    case DASH_DOT_DOT: {
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
    case DOUBLE: {  // For this it is different so do it myself

        pen.setWidth(1); // each individual line is only 1 pixel wide.

        // basically the thickness in this case is the gap between the lines.
        float offset = ((border.thickness() * 1.333333333) + 1) / 2.0;
        QPointF topO, bottomO, topI, bottomI;
        Border borderT = format->topBorder();
        Border borderB = format->bottomBorder();

        topI = rect.topRight();
        if (borderT.isEnabled() && borderT.style() == DOUBLE) {
            topI.rx() -= offset;
            topI.ry() += offset;
            topO.rx() += offset;
            topO.ry() -= offset;
        }

        bottomI = rect.bottomRight();
        if (borderB.isEnabled() && borderB.style() == DOUBLE) {
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
    case SMALLDASH: { // For this it is different so do it myself
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
    case SINGLE: {// for these the Format::BorderStyle is the same as the Qt::BorderStyle
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
    case DOTTED:
    case LARGEDASH:
    case DASH_DOT:
    case DASH_DOT_DOT: {
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
    case DOUBLE: {  // For this it is different so do it myself

        // basically the thickness in this case is the gap between the lines.
        float offset = ((border.thickness() * 1.333333333) + 1) / 2.0;
        QPointF topO, bottomO, topI, bottomI;
        Border borderT = format->topBorder();
        Border borderB = format->bottomBorder();

        topI = rect.topLeft();
        if (borderT.isEnabled() && borderT.style() == DOUBLE) {
            topI.rx() += offset;
            topI.ry() += offset;
            topO.rx() -= offset;
            topO.ry() -= offset;
        }

        bottomI = rect.bottomLeft();
        if (borderB.isEnabled() && borderB.style() == DOUBLE) {
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
    case SMALLDASH: { // For this it is different so do it myself
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
    case SINGLE: {// for these the Format::BorderStyle is the same as the Qt::BorderStyle
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
    case DOTTED:
    case LARGEDASH:
    case DASH_DOT: {
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
    case DOUBLE: {  // For this it is different so do it myself

        pen.setWidth(1); // each individual line is only 1 pixel wide.

        float offset = ((border.thickness() * 1.333333333) + 1) / 2.0;
        QPointF topO, bottomO, topI, bottomI;
        Border borderL = format->leftborder();
        Border borderR = format->rightBorder();

        topI = rect.topLeft();
        if (borderL.isEnabled() && borderL.style() == DOUBLE) {
            topI.rx() += offset;
            topI.ry() += offset;
            topO.rx() -= offset;
            topO.ry() -= offset;
        }

        bottomI = rect.bottomLeft();
        if (borderR.isEnabled() && borderR.style() == DOUBLE) {
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
    case SMALLDASH: { // For this it is different so do it myself
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
    case SINGLE: {// for these the Format::BorderStyle is the same as the Qt::BorderStyle
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
    case DOTTED:
    case LARGEDASH:
    case DASH_DOT:
    case DASH_DOT_DOT: {
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
    case DOUBLE: {  // For this it is different so do it myself

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
        if (borderL.isEnabled() && borderL.style() == DOUBLE) {
            leftO.rx() -= offset;
            leftO.ry() -= offset;
            leftI.rx() += offset;
            leftI.ry() += offset;
        }

        rightO = rect.topRight();
        rightI = rightO;
        if (borderR.isEnabled() && borderR.style() == DOUBLE) {
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
    case SMALLDASH: { // For this it is different so do it myself
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
