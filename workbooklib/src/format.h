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
#ifndef FORMAT_H
#define FORMAT_H

#include <QObject>
#include <QFont>
#include <QBrush>
#include <QScopedPointer>

#include "workbook_global.h"
#include "format_p.h"
#include "types.h"

namespace QXlsx {
    class Format;
}

namespace ods {
    class Style;
}

namespace QWorkbook {

class WorksheetModel;
//class FormatPrivate;

class NumberFormat {
public:
    NumberFormat() : mType(General), sFormat("General") { }
    NumberFormat(NumberFormatType t, QString f) : mType(t), sFormat(f) { }
    virtual ~NumberFormat() {}

    NumberFormatType type() { return mType; }
    QString format() { return sFormat; }

    NumberFormatType mType;
    QString sFormat;
};

class DefaultNumberFormats {
public:

    DefaultNumberFormats();
    virtual ~DefaultNumberFormats() {}


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
    virtual ~Format() {}

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

    Format* clone();

    QXlsx::Format *toXlsx();
    ods::Style *toOds();

signals:
    void formatChanged(Format* format);
    void topBorderChanged(Format* format);
    void leftBorderChanged(Format* format);
    void bottomBorderChanged(Format* format);
    void rightBorderChanged(Format* format);

public slots:
    void fromXlsx(QXlsx::Format *format);
    void fromOds(ods::Style *style);

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
    void setBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=BS_SINGLE, double thickness = 0.75);
    void setTopBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=BS_SINGLE, double thickness = 0.75);
    void setBottomBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=BS_SINGLE, double thickness = 0.75);
    void setLeftBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=BS_SINGLE, double thickness = 0.75);
    void setRightBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=BS_SINGLE, double thickness = 0.75);
    void updateTopBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=BS_SINGLE, double thickness = 0.75);
    void updateBottomBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=BS_SINGLE, double thickness = 0.75);
    void updateLeftBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=BS_SINGLE, double thickness = 0.75);
    void updateRightBorder(bool enabled, QColor color=QColor("black"), BorderStyle style=BS_SINGLE, double thickness = 0.75);

//    bool operator== (Format f) {

//    }

protected:
    Q_DECLARE_PRIVATE(Format)
    const QScopedPointer<FormatPrivate> d_ptr;

};


}

#endif // FORMAT_H
