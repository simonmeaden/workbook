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
#ifndef FORMATPRIVATE_H
#define FORMATPRIVATE_H

#include <QObject>
#include <QFont>
#include <QBrush>
#include <QMap>

#include "workbook_global.h"
#include "types.h"

namespace QXlsx {
    class Format;
}

namespace ods {
    class Style;
}

namespace QWorkbook {

class WorksheetModel;
class Format;

class FormatPrivate {
public:
    FormatPrivate(int row, int column, Format *parent);
    virtual ~FormatPrivate() {}

    void setFont(QFont font);
    void setPointSize(int size);
    void setPixelSize(int size);
    void setPointSizeF(float size);
    void setBold(bool bold);
    void setItalic(bool italic);
    void setOverline(bool overline);
    void setStrikeout(bool strikeout);
    void setAlignment(Qt::Alignment alignment);
    void setBackgroundColor(QColor backgroundColor);
    void setShowBackgroundBrush(bool showBackgroundColor);

    inline QFont font() { return mFont; }
    inline int pointSize() { return mFont.pointSize(); }
    inline int pixelSize() { return mFont.pixelSize(); }
    inline float pointSizeF() { return mFont.pointSizeF(); }
    inline bool bold() { return bBold; }
    inline bool italic() { return bItalic; }
    inline bool overline() { return bOverline; }
    inline bool strikeout() { return bStrikeout; }
    inline Qt::Alignment alignment() { return mAlignment; }
    inline QBrush backgroundColor() { return mBackground; }

    void indent();
    void undent();

    QXlsx::Format* toXlsx();
    ods::Style* toOds();
    void fromXlsx(QXlsx::Format *format);
    void fromOds(ods::Style *style);

    WorksheetModel *pModel;
    int mRow, mColumn;
    int mIndentCount;
    Qt::Alignment mAlignment;
    QColor mBackground, mWhite, mStandby;
    bool bBold, bItalic, bOverline, bStrikeout;
    QFont mFont;

    QColor mFontColor;
    inline QColor fontColor() { return mFontColor; }
    void setFontColor(QColor color);

    bool bUnderline;
    UnderlineStyle mUnderlineStyle;
    QColor mUnderlineColor;
    bool underline() { return bUnderline; }
    UnderlineStyle underlineStyle() { return mUnderlineStyle; }
    QColor underlineColor() { return mUnderlineColor; }
    void setUnderline(bool underline);
    void setUnderlineStyle(UnderlineStyle style);
    void setUnderlineColor(QColor color);

    Border mTopBorder, mBottomBorder, mLeftBorder, mRightBorder;
    Border topBorder() { return mTopBorder; }
    Border bottomBorder() { return mBottomBorder; }
    Border leftBorder() { return mLeftBorder; }
    Border rightBorder() { return mRightBorder; }
    void setBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=BS_SINGLE, double thickness = 0.75);
    void setTopBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=BS_SINGLE, double thickness = 0.75);
    void setBottomBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=BS_SINGLE, double thickness = 0.75);
    void setLeftBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=BS_SINGLE, double thickness = 0.75);
    void setRightBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=BS_SINGLE, double thickness = 0.75);
    void updateTopBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=BS_SINGLE, double thickness = 0.75);
    void updateBottomBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=BS_SINGLE, double thickness = 0.75);
    void updateLeftBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=BS_SINGLE, double thickness = 0.75);
    void updateRightBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=BS_SINGLE, double thickness = 0.75);

    int xWidth;

    Format *q_ptr;
    Q_DECLARE_PUBLIC(Format)
};


}

#endif // FORMATPRIVATE_H
