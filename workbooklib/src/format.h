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
#ifndef FORMAT_H
#define FORMAT_H

#include <QObject>
#include <QFont>
#include <QBrush>
#include <QScopedPointer>

#include "xlsxformat.h"

#include <workbook_global.h>
#include "format_p.h"
#include "types.h"

class WorksheetModel;

class NumberFormat {
public:
    NumberFormat() : mType(General), sFormat("General") { }
    NumberFormat(NumberFormatType t, QString f) : mType(t), sFormat(f) { }

    NumberFormatType type() { return mType; }
    QString format() { return sFormat; }

    NumberFormatType mType;
    QString sFormat;
};

class DefaultNumberFormats {
public:

    DefaultNumberFormats();


    QList<int> styleIds() {
        return mStyles.keys();
    }
    QStringList formats() {
        return mIds.keys();
    }
    NumberFormat format(int id) { return mStyles.value(id); }
    int id(QString format) { return mIds.value(format); }

    void insertStyle(int id, NumberFormatType type, QString format);

protected:
    QMap<int, NumberFormat> mStyles;
    QMap<QString, int> mIds;
};


class WORKBOOKSHARED_EXPORT Format : public QObject {
    Q_OBJECT
public:

    explicit Format(int row, int column, QObject *parent);
    explicit Format(Format &format);
    ~Format();

    int row();
    int column();
    bool bold() ;
    bool italic();
    bool underline();
    UnderlineStyle underlineStyle();
    QColor underlineColor();
    bool overline();
    bool strikeout();
    QFont font();
    int pointSize();
    int pixelSize();
    int pointSizeF();
    Qt::Alignment alignment();
    QBrush backgroundColor();
    int indentSize();

    QXlsx::Format toXlsx();    

signals:
    void formatChanged(Format* format);
    void topBorderChanged(Format* format);
    void leftBorderChanged(Format* format);
    void bottomBorderChanged(Format* format);
    void rightBorderChanged(Format* format);

public slots:
    void fromXlsx(QXlsx::Format format);

    void setFont(QFont font);
    void setPointSize(int size);
    void setPixelSize(int size);
    void setPointSizeF(float size);
    void setBold(bool bold);
    void setItalic(bool italic);
    void setOverline(bool overline);
    void setUnderline(bool underline);
    void setUnderlineStyle(UnderlineStyle style);
    void setUnderlineColor(QColor color);
    void setStrikeout(bool strikeout);
    void setModel(WorksheetModel *model);
    void setCell(int row, int column);
    void setAlignment(Qt::Alignment alignment);
    void setBackgroundColor(QColor backgroundColor);
    void indent();
    void undent();
    Border topBorder();
    Border bottomBorder();
    Border leftborder();
    Border rightBorder();
    void setBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=SINGLE, double thickness = 0.75);
    void setTopBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=SINGLE, double thickness = 0.75);
    void setBottomBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=SINGLE, double thickness = 0.75);
    void setLeftBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=SINGLE, double thickness = 0.75);
    void setRightBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=SINGLE, double thickness = 0.75);
    void updateTopBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=SINGLE, double thickness = 0.75);
    void updateBottomBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=SINGLE, double thickness = 0.75);
    void updateLeftBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=SINGLE, double thickness = 0.75);
    void updateRightBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=SINGLE, double thickness = 0.75);

//    bool operator== (Format f) {

//    }

protected:
    Q_DECLARE_PRIVATE(Format)
    const QScopedPointer<FormatPrivate> d_ptr;

};

#endif // FORMAT_H
