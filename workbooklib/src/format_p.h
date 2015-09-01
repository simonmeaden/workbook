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
#ifndef FORMATPRIVATE_H
#define FORMATPRIVATE_H

#include <QObject>
#include <QFont>
#include <QBrush>
#include <QMap>

#include "types.h"

namespace QXlsx {
    class Format;
}

#include "format.h"

//class Format;
class WorksheetModel;


class FormatPrivate {
public:
    FormatPrivate(int row, int column, Format *parent);
    ~FormatPrivate();

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

    QXlsx::Format toXlsx();
    void fromXlsx(QXlsx::Format format);

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
    Format::UnderlineStyle mUnderlineStyle;
    QColor mUnderlineColor;
    inline bool underline() { return bUnderline; }
    inline Format::UnderlineStyle underlineStyle() { return mUnderlineStyle; }
    QColor underlineColor() { return mUnderlineColor; }
    void setUnderline(bool underline);
    void setUnderlineStyle(Format::UnderlineStyle style);
    void setUnderlineColor(QColor color);

    Border mTopBorder, mBottomBorder, mLeftBorder, mRightBorder;
    inline Border topBorder() { return mTopBorder; }
    inline Border bottomBorder() { return mBottomBorder; }
    inline Border leftBorder() { return mLeftBorder; }
    inline Border rightBorder() { return mRightBorder; }
    void setBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=SINGLE, double thickness = 0.75);
    void setTopBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=SINGLE, double thickness = 0.75);
    void setBottomBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=SINGLE, double thickness = 0.75);
    void setLeftBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=SINGLE, double thickness = 0.75);
    void setRightBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=SINGLE, double thickness = 0.75);
    void updateTopBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=SINGLE, double thickness = 0.75);
    void updateBottomBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=SINGLE, double thickness = 0.75);
    void updateLeftBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=SINGLE, double thickness = 0.75);
    void updateRightBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=SINGLE, double thickness = 0.75);

    int xWidth;

    Format *q_ptr;
    Q_DECLARE_PUBLIC(Format)
};

#endif // FORMATPRIVATE_H
