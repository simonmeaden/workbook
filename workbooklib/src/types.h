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
#ifndef TYPES
#define TYPES

#include <QFont>
#include <QColor>
#include <qnamespace.h>

#include <limits>

#include "workbook_global.h"

namespace QWorkbook {


enum WorksheetType {
    NOT_A_SPREADSHEET, // Not one of the allowed files;
    ODS, // ODF format spreadsheet - default.
    XLS, // Windoze Excel spreadsheet format
    XLSX,// Windoze Excel XML spreadsheet format
    CSV, // standard comma separated text
    DIF, // Document Interchange Format
};

enum BorderStyle {
    BS_NONE,
    BS_SINGLE = Qt::SolidLine,
    BS_DOUBLE = 0x10,
    BS_DOTTED = Qt::DotLine,
    BS_LARGEDASH = Qt::DashLine,
    BS_SMALLDASH = 0x11,
    BS_DASH_DOT = Qt::DashDotLine,
    BS_DASH_DOT_DOT = Qt::DashDotDotLine,
};

enum UnderlineStyle {
    UnderlineNone,
    UnderlineSingle,
    UnderlineDouble,
    UnderlineSingleWiggly,
    UnderlineSpellCheck,
};

enum MergeStatus {
    MergePossible,
    DemergePossible,
    ContainsMerge,
};


const static QString ButtonStyle = "padding: 0px; " \
                                   "margin: 0px; " \
                                   ;

struct SizeStatus {

    int mMaxRow, mMaxCol;

    SizeStatus() {
        clear();
    }

    void clear() {
        mMaxRow = 0;
        mMaxCol = 0;
    }
};

struct FormatStatus {

    bool bAllBold, bAllItalic, bAllUnderline, bAllOverline, bAllStrikeout;
    bool bAllSameBorder, bAllSameIndent;

    int mMinRow, mMinCol, mMaxRow, mMaxCol, mCount;
    bool bContiguous;

    bool bAllSameFont;
    QFont mFont;
    int mFontSize;

    bool bAllSameAlignment;
    Qt::Alignment mAlignment;

    FormatStatus() {
        clear();
    }
    virtual ~FormatStatus() {}

    void clear() {
        bAllBold = true;
        bAllItalic = true;
        bAllUnderline = true;
        bAllOverline = true;
        bAllStrikeout = true;
        bAllSameFont = true;
        bAllSameBorder = true;
        bAllSameIndent = true;
        bAllSameAlignment = true;
        mCount = 0;
        mMinRow = std::numeric_limits<int>::max();
        mMaxRow = 0;
        mMinCol = std::numeric_limits<int>::max();
        mMaxCol = 0;
    }

    bool allSet() {
        if (
            bAllBold == false &&
            bAllItalic == false &&
            bAllUnderline == false &&
            bAllOverline == false &&
            bAllStrikeout == false &&
            bAllSameFont == false &&
            bAllSameAlignment == false) return true;
        return false;
    }
};

class Border {
public:
    Border() :
        bEnabled(false),
        mColor(QColor("black")),
        mStyle(BorderStyle::BS_NONE),
        mThickness(0) {

    }
    virtual ~Border() {}

    bool isEnabled() {
        return bEnabled;
    }
    void setEnabled(bool enabled) {
        bEnabled = enabled;
    }
    QColor color() {
        return mColor;
    }
    void setColor(QColor color) {
        mColor = color;
    }
    BorderStyle style() {
        return mStyle;
    }
    void setStyle(BorderStyle style) {
        mStyle = style;
    }
    double thickness() {
        return mThickness;
    }
    void setThickness(double thickness) {
        mThickness = thickness;
    }

    bool isEqual(Border border) {
        if (border.color() == mColor &&
                border.thickness() == mThickness &&
                border.style() == mStyle)
            return true;
        return false;
    }

    bool operator== (Border b) {
        if (b.thickness() == mThickness &&
                b.style() == mStyle &&
                b.color() == mColor &&
                b.isEnabled() == bEnabled) return true;
        return false;
    }

    bool operator!= (Border b) {
        if (b.thickness() != mThickness ||
                b.style() != mStyle ||
                b.color() != mColor ||
                b.isEnabled() != bEnabled) return true;
        return false;
    }

protected:
    bool bEnabled;
    QColor mColor;
    BorderStyle mStyle;
    double mThickness;
};

enum NumberFormatType {
    General,
    Decimal,
    Currency,
    Percent,
    Scientific,
    Fraction,
    Date,
    Time,
    DateTime,
    Account,
    Text,
};

enum ParserError {
    NoError=0x0,
    UnbalancedParethesis=0x1,
    UnhandledPartialExpression=0x2,
    NotAFunction=0x4,
    FunctionNotFollowedByParenthesis=0x8,
    EmptyFunction=0x10,
    WrongNumberOfFunctionParameters = 0x20,
    WrongParameterType=0x40,
    BrokenExpression=0x80,
    NoFunctionAvailable=0x100,
};

// Static variables and constants
Q_DECLARE_FLAGS(ParserErrors, ParserError)
Q_DECLARE_OPERATORS_FOR_FLAGS(ParserErrors)

}

Q_DECLARE_METATYPE(QWorkbook::ParserError)





#endif // TYPES

