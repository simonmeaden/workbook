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
#include <QFontMetrics>

#include "format_p.h"
#include "format.h"
#include "worksheetmodel.h"



FormatPrivate::FormatPrivate(int row, int column, Format *parent) :
    q_ptr(parent) {
    bBold = false;
    bItalic = false;
    bOverline = false;
    bUnderline = false;
    bStrikeout = false;
    mRow = row;
    mColumn = column;
    mFont = QFont("Times", 10, QFont::Normal);
    QFontMetrics fm(mFont);
//    xWidth = fm.width("x");
    xWidth = 0;
    mAlignment = Qt::AlignLeft | Qt::AlignVCenter;
    mUnderlineStyle = UnderlineNone;
    mUnderlineColor = QColor("black");
    mWhite = QColor("white");
    mBackground = mWhite;
    mTopBorder = Border();
    mBottomBorder = Border();
    mLeftBorder = Border();
    mRightBorder = Border();
    mIndentCount = 0;
    mFontColor = QColor("black");
}

FormatPrivate::~FormatPrivate() {

}

void FormatPrivate::indent() {
    mIndentCount++;
    emit q_ptr->formatChanged(q_ptr);
}

void FormatPrivate::undent() {
    mIndentCount--;
    if (mIndentCount < 0) mIndentCount = 0;
    emit q_ptr->formatChanged(q_ptr);
}



QXlsx::Format FormatPrivate::toXlsx() {
    QXlsx::Format format;

    switch (mUnderlineStyle) {
    case UnderlineSingle:
        format.setFontUnderline(QXlsx::Format::FontUnderlineSingle);
        break;
    case UnderlineDouble:
        format.setFontUnderline(QXlsx::Format::FontUnderlineDouble);
        break;
    default:
        format.setFontUnderline(QXlsx::Format::FontUnderlineNone);
        break;
    }

    format.setFontBold(bBold);
    format.setFontItalic(bItalic);
    format.setFontStrikeOut(bStrikeout);

    if (bOverline)
        mFont.setOverline(bOverline);

    format.setFontColor(mFontColor);

    // TODO Only solid fill supported so far
    format.setFillPattern(QXlsx::Format::PatternSolid);
    format.setPatternBackgroundColor(mBackground);

    format.setFont(mFont);

    if (mTopBorder.isEnabled()) {
        int thickness = qRound(mTopBorder.thickness());
        switch(thickness) {
        case 0:
            format.setTopBorderStyle(QXlsx::Format::BorderNone);
            break;
        case 1:
            format.setTopBorderStyle(QXlsx::Format::BorderHair);
            break;
        case 2:
            format.setTopBorderStyle(QXlsx::Format::BorderMedium);
            break;
        case 3:
            format.setTopBorderStyle(QXlsx::Format::BorderThick);
            break;
        default:
            format.setTopBorderStyle(QXlsx::Format::BorderNone);
            break;
        }
        format.setTopBorderColor(mTopBorder.color());
    }

    if (mLeftBorder.isEnabled()) {
        int thickness = qRound(mLeftBorder.thickness());
        switch(thickness) {
        case 0:
            format.setLeftBorderStyle(QXlsx::Format::BorderNone);
            break;
        case 1:
            format.setLeftBorderStyle(QXlsx::Format::BorderHair);
            break;
        case 2:
            format.setLeftBorderStyle(QXlsx::Format::BorderMedium);
            break;
        case 3:
            format.setLeftBorderStyle(QXlsx::Format::BorderThick);
            break;
        default:
            format.setLeftBorderStyle(QXlsx::Format::BorderNone);
            break;
        }
        format.setLeftBorderColor(mLeftBorder.color());
    }

    if (mRightBorder.isEnabled()) {
        int thickness = qRound(mRightBorder.thickness());
        switch(thickness) {
        case 0:
            format.setRightBorderStyle(QXlsx::Format::BorderNone);
            break;
        case 1:
            format.setRightBorderStyle(QXlsx::Format::BorderHair);
            break;
        case 2:
            format.setRightBorderStyle(QXlsx::Format::BorderMedium);
            break;
        case 3:
            format.setRightBorderStyle(QXlsx::Format::BorderThick);
            break;
        default:
            format.setRightBorderStyle(QXlsx::Format::BorderNone);
            break;
        }
        format.setRightBorderColor(mRightBorder.color());
    }

    if (mBottomBorder.isEnabled()) {
        int thickness = qRound(mBottomBorder.thickness());
        switch(thickness) {
        case 0:
            format.setBottomBorderStyle(QXlsx::Format::BorderNone);
            break;
        case 1:
            format.setBottomBorderStyle(QXlsx::Format::BorderHair);
            break;
        case 2:
            format.setBottomBorderStyle(QXlsx::Format::BorderMedium);
            break;
        case 3:
            format.setBottomBorderStyle(QXlsx::Format::BorderThick);
            break;
        default:
            format.setBottomBorderStyle(QXlsx::Format::BorderNone);
            break;
        }
        format.setBottomBorderColor(mBottomBorder.color());
    }

    return format;
}

void FormatPrivate::fromXlsx(QXlsx::Format format) {
    switch(format.fontUnderline()) {
    case QXlsx::Format::FontUnderlineSingle:
    case QXlsx::Format::FontUnderlineSingleAccounting:
        mUnderlineStyle = UnderlineSingle;
        break;
    case QXlsx::Format::FontUnderlineDouble:
    case QXlsx::Format::FontUnderlineDoubleAccounting:
        mUnderlineStyle = UnderlineDouble;
        break;
    default:
        mUnderlineStyle = UnderlineNone;
        break;
    }
}

void FormatPrivate::setAlignment(Qt::Alignment alignment) {
    mAlignment = alignment;
    emit q_ptr->formatChanged(q_ptr);

}

void FormatPrivate::setPointSize(int size) {
    mFont.setPointSize(size);
    emit q_ptr->formatChanged(q_ptr);

}

void FormatPrivate::setPixelSize(int size) {
    mFont.setPixelSize(size);
    emit q_ptr->formatChanged(q_ptr);

}

void FormatPrivate::setPointSizeF(float size) {
    mFont.setPointSizeF(size);
    emit q_ptr->formatChanged(q_ptr);

}

void FormatPrivate::setFont(QFont font) {
    mFont = font;
    QFontMetrics fm(mFont);
    xWidth = fm.width("x");
    emit q_ptr->formatChanged(q_ptr);

    bool value;
    value = mFont.overline();
    if (value)
        bOverline = true;

    value = mFont.strikeOut();
    if (value)
        bStrikeout = true;

    value = mFont.underline();
    if (value)
        bUnderline = true;

    value = mFont.bold();
    if (value)
        bBold = true;

    value = mFont.italic();
    if (value)
        bItalic = value;


}

void FormatPrivate::setBold(bool bold) {
    bBold = bold;
    QFontMetrics fm(mFont);
    xWidth = fm.width("x");
    emit q_ptr->formatChanged(q_ptr);

}

void FormatPrivate::setItalic(bool italic) {
    bItalic = italic;
    QFontMetrics fm(mFont);
    xWidth = fm.width("x");
    emit q_ptr->formatChanged(q_ptr);

}

void FormatPrivate::setOverline(bool overline) {
    bOverline = overline;
    emit q_ptr->formatChanged(q_ptr);

}

void FormatPrivate::setUnderline(bool underline) {
    bUnderline = underline;
    emit q_ptr->formatChanged(q_ptr);

}

void FormatPrivate::setUnderlineColor(QColor color) {
    mUnderlineColor = color;
    emit q_ptr->formatChanged(q_ptr);

}

void FormatPrivate::setUnderlineStyle(UnderlineStyle style) {
    mUnderlineStyle = style;
    emit q_ptr->formatChanged(q_ptr);

}

void FormatPrivate::setStrikeout(bool strikeout) {
    bStrikeout = strikeout;
    emit q_ptr->formatChanged(q_ptr);

}

void FormatPrivate::setFontColor(QColor color) {
    mFontColor = color;
    emit q_ptr->formatChanged(q_ptr);
}

void FormatPrivate::setBackgroundColor(QColor background) {
    mBackground = background;
    emit q_ptr->formatChanged(q_ptr);
}

void FormatPrivate::setBorder(bool enabled, QColor color, BorderStyle style, double thickness) {
    setTopBorder(enabled, color, style, thickness);
    setBottomBorder(enabled, color, style, thickness);
    setLeftBorder(enabled, color, style, thickness);
    setRightBorder(enabled, color, style, thickness);
}

void FormatPrivate::setTopBorder(bool enabled, QColor color, BorderStyle style, double thickness) {
    mTopBorder.setEnabled(enabled);
    mTopBorder.setColor(color);
    mTopBorder.setStyle(style);
    mTopBorder.setThickness(thickness);

    emit q_ptr->topBorderChanged(q_ptr);
    emit q_ptr->formatChanged(q_ptr);
}

void FormatPrivate::setBottomBorder(bool enabled, QColor color, BorderStyle style, double thickness) {
    mBottomBorder.setEnabled(enabled);
    mBottomBorder.setColor(color);
    mBottomBorder.setStyle(style);
    mBottomBorder.setThickness(thickness);

    emit q_ptr->bottomBorderChanged(q_ptr);
    emit q_ptr->formatChanged(q_ptr);
}

void FormatPrivate::setLeftBorder(bool enabled, QColor color, BorderStyle style, double thickness) {
    mLeftBorder.setEnabled(enabled);
    mLeftBorder.setColor(color);
    mLeftBorder.setStyle(style);
    mLeftBorder.setThickness(thickness);

    emit q_ptr->leftBorderChanged(q_ptr);
    emit q_ptr->formatChanged(q_ptr);
}

void FormatPrivate::setRightBorder(bool enabled, QColor color, BorderStyle style, double thickness) {
    mRightBorder.setEnabled(enabled);
    mRightBorder.setColor(color);
    mRightBorder.setStyle(style);
    mRightBorder.setThickness(thickness);

    emit q_ptr->rightBorderChanged(q_ptr);
    emit q_ptr->formatChanged(q_ptr);
}

void FormatPrivate::updateTopBorder(bool enabled, QColor color, BorderStyle style, double thickness) {
    mTopBorder.setEnabled(enabled);
    mTopBorder.setColor(color);
    mTopBorder.setStyle(style);
    mTopBorder.setThickness(thickness);
}

void FormatPrivate::updateBottomBorder(bool enabled, QColor color, BorderStyle style, double thickness) {
    mBottomBorder.setEnabled(enabled);
    mBottomBorder.setColor(color);
    mBottomBorder.setStyle(style);
    mBottomBorder.setThickness(thickness);
}

void FormatPrivate::updateLeftBorder(bool enabled, QColor color, BorderStyle style, double thickness) {
    mLeftBorder.setEnabled(enabled);
    mLeftBorder.setColor(color);
    mLeftBorder.setStyle(style);
    mLeftBorder.setThickness(thickness);
}

void FormatPrivate::updateRightBorder(bool enabled, QColor color, BorderStyle style, double thickness) {
    mRightBorder.setEnabled(enabled);
    mRightBorder.setColor(color);
    mRightBorder.setStyle(style);
    mRightBorder.setThickness(thickness);
}


