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
#ifndef WORKSHEET_H
#define WORKSHEET_H

// Function plugin stuff. ===================================================
#if defined(USE_PLUGINS)
#   include <QPluginLoader>
#   include "interface.h"
#endif
// ==========================================================================

#include <QObject>
#include <QMap>
#include <QVariant>
#include <QDir>

#include <workbook_global.h>
#include "cellreference.h"
#include "types.h"
#include "range.h"
#include "pluginstore.h"
#include "worksheetmodel.h"

class WorksheetPrivate;
class Cell;
class Format;
class WorksheetModel;

namespace QXlsx {
class Document;
class Workbook;
class Worksheet;
}

class WORKBOOKSHARED_EXPORT Worksheet : public QObject {
    Q_OBJECT
public:

    explicit Worksheet(PluginStore *store, QObject *parent = 0);
    explicit Worksheet(QString name, PluginStore *store, QObject *parent = 0);
    ~Worksheet();

    void setSheetName(QString name);
    QString sheetName();

    QVariant cell(int row, int column);
    QVariant cell(CellReference &ref);

    Format* format(int row, int column);
    Format* format(CellReference &ref);

    Format* rowFormat(int row);
    Format* columnFormat(int column);
    void setRowFormat(int row, Format* format);
    void setColumnFormat(int column, Format* format);
    bool showGrid();
    bool isLocked(int row, int column);
    bool isLocked(CellReference &ref);
    int maxColumn(int row);
    int maxRow();

    PluginStore* pluginStore();

signals:
    void formatHasChanged(int row, int column);
    void badPath(QString message);
    void updateBorder(int, int, Format*);

public slots:

    void formatChanged(Format*);
    void setModel(WorksheetModel *model);
    void setCell(int row, int column, QVariant cell);
    void setCell(CellReference &ref, QVariant cell);
    void setFormat(Format *format);
    void saveWorksheet();
    void saveWorksheet(QString path);
    void saveWorksheet(WorksheetType type);
    void saveWorksheet(WorksheetType type, QString path);
    void writeXlsx(QXlsx::Worksheet *sheet);
    void setShowGrid(bool showGrid);
    void lockCell(int row, int column);
    void lockCell(CellReference &ref);
    void lockRow(int &row);
    void lockColumn(int &column);
    void lockRange(Range &range);
    void lockSheet();
    void unlockCell(int row, int column);
    void unlockCell(CellReference &ref);
    void unlockRow(int &row);
    void unlockColumn(int &column);
    void unlockRange(Range &range);
    void unlockSheet();
    void readXlsx(QXlsx::Worksheet *sheet, int index);

protected slots:

    void leftBorderChanged(Format *format);
    void topBorderChanged(Format *format);
    void rightBorderChanged(Format *format);
    void bottomBorderChanged(Format *format);

protected:
    WorksheetPrivate *d_ptr;

    Cell* cellAsCell(int row, int column);

    friend class WorksheetModel;

};


#endif // WORKSHEET_H
