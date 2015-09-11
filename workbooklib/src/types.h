/*
    This Workbook library is © Simon Meaden 2015. It is licensed under the LGPL V3 license.

    This Workbook library dynamically links to unmodified Nokia Qt5 Library. The Qt5
    Library is © 2011 Nokia Corporation and/or its subsidiary(-ies), and is licensed
    under the GNU Lesser General Public License version 2.1 with Nokia Qt LGPL exception
    version 1.1.

    Qt5 library is free software; you can redistribute it and/or modify it under the
    terms of the GNU Lesser General Public License, version 2.1, as published by the
    Free Software Foundation.

    Qt5 library is provided “AS IS”, without WARRANTIES OR CONDITIONS OF ANY KIND, EITHER
    EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY WARRANTIES OR CONDITIONS OF
    TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.

    As an additional permission to the GNU Lesser General Public License version 3.0, the
    object code form of a “work that uses the Library” may incorporate material from a
    header file that is part of the Library. You may distribute such object code under
    terms of your choice, provided that: (i) the header files of the Library have not
    been modified; and (ii) the incorporated material is limited to numerical parameters,
    data structure layouts, accessors, macros, inline functions and templates; and (iii)
    you comply with the terms of Section 6 of the GNU Lesser General Public License version 3.0.

    Moreover, you may apply this exception to a modified version of the Library, provided
    that such modification does not involve copying material from the Library into the
    modified Library’s header files unless such material is limited to (i) numerical
    parameters; (ii) data structure layouts; (iii) accessors; and (iv) small macros,
    templates and inline functions of five lines or less in length.

    Furthermore, you are not required to apply this additional permission to a modified
    version of the Library.

    You should have received a copy of the GNU Lesser General Public License along
    with this package; if not, write to the Free Software Foundation, Inc., 51 Franklin
    Street, Fifth Floor, Boston, MA 02110-1301 USA

    The source code for Qt 5.4.X SDK is available from Nokia here:
    http://get.qt.nokia.com/qt/source/qt-everywhere-opensource-src-4.7.X.zip.

    It is also available on request from Simon Meaden info@smelecomp.co.uk.
*/
#ifndef TYPES
#define TYPES

#include <QFont>
#include <QColor>
#include <qnamespace.h>

enum WorksheetType {
    NOT_A_SPREADSHEET, // Not one of the allowed files;
    ODS, // ODF format spreadsheet - default.
    XLS, // Windoze Excel spreadsheet format
    XLSX, // Windoze Excel XML spreadsheet format
};

enum BorderStyle {
    NONE,
    SINGLE = Qt::SolidLine,
    DOUBLE = 0x10,
    DOTTED = Qt::DotLine,
    LARGEDASH = Qt::DashLine,
    SMALLDASH = 0x11,
    DASH_DOT = Qt::DashDotLine,
    DASH_DOT_DOT = Qt::DashDotDotLine,
};

enum CellType {
    TextType,
    NumberType,
    BooleanType,
    FormulaType,
    ErrorType,
};

enum UnderlineStyle {
    UnderlineNone,
    UnderlineSingle,
    UnderlineDouble,
    UnderlineSingleWiggly,
    UnderlineSpellCheck,
};

const static QString buttonStyle = "padding: 0px; " \
                                   "margin: 0px; " \
                                   ;

struct FormatStatus {
public:
    bool bAllBold, bAllItalic, bAllUnderline, bAllOverline, bAllStrikeout;
    bool bAllSameBorder, bAllSameIndent;

    int mMinRow, mMinCol, mMaxRow, mMaxCol, mCount;
    bool bContiguous;

    bool bAllSameFont;
    QFont mFont;
    int mFontSize;

    bool bAllSameAlignment;
    Qt::Alignment mAlignment;

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
        mMinRow = 0;
        mMaxRow = 0;
        mMinCol = 0;
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
        mStyle(BorderStyle::NONE),
        mThickness(0) {

    }

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
Q_DECLARE_FLAGS(ParserErrors, ParserError)
Q_DECLARE_OPERATORS_FOR_FLAGS(ParserErrors)
Q_DECLARE_METATYPE(ParserError)


// Static variables and constants
const QString REGEXSTRING_ROW = "\\$?(\\d+)";
const QString REGEXSTRING_COLUMN = "\\$?([A-Z]{1,3})";


#endif // TYPES

