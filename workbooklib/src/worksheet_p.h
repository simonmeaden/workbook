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
#ifndef WORKSHEETPRIVATE_H
#define WORKSHEETPRIVATE_H

#include <QMap>
#include <QList>
#include <QVariant>
#include <QTextDocument>
#include <QTextDocumentWriter>
#include <QTextTableFormat>
#include <QTextCursor>
#include <QFile>
#include <QDir>

#include "types.h"
#include "pluginstore.h"

class Format;
class Cell;
class Range;
class WorksheetModel;
class Worksheet;

namespace QXlsx {
    class Worksheet;
}

class WorksheetPrivate {
public:
    WorksheetPrivate(PluginStore *store, Worksheet *parent);
    ~WorksheetPrivate();

    void setSheetName(QString name);
    QString sheetName();
    WorksheetType type();
    void setType(WorksheetType type);

    QVariant cell(int row, int column);
    void setCell(int row, int column, QVariant data);
    Cell* cellAsCell(int row, int column);
    Cell* cellCreateAsNeeded(int row, int column);

    bool isLocked(int row, int column);

    Format* format(int row, int column);
    void setFormat(Format *format);

    QList<QVariant> rowCells(int row);
    QList<QVariant> columnCells(int column);
    QList<QVariant> cells(Range *range);

    Format* rowFormat(int row);
    Format* columnFormat(int column);
    void setRowFormat(int row, Format* format);
    void setColumnFormat(int column, Format* format);

    void setModel(WorksheetModel *model);

    int maxColumn(int row);
    int maxRow();
    int maxColumn();

    inline bool showGrid() { return bShowGrid; }
    inline void setShowGrid(bool showGrid) { bShowGrid = showGrid; }

    void saveWorksheet();
    void saveWorksheet(QString filename);
    void saveWorksheet(WorksheetType type);
    void saveWorksheet(WorksheetType type, QString filename);
    void writeOds(QString filename);
    void writeXls(QString filename);
    void saveXlsx(QString filename);
    void readXlsx(QString filename);

    void writeXlsx(QXlsx::Worksheet *sheet);
    void readXlsx(QXlsx::Worksheet *sheet, int index);

    void lockCell(int row, int column);
    void lockRow(int &row);
    void lockColumn(int &column);
    void lockRange(Range &range);
    void lockSheet();
    void unlockCell(int row, int column);
    void unlockRow(int &row);
    void unlockColumn(int &column);
    void unlockRange(Range &range);
    void unlockSheet();

    void rightBorderChanged(Format *format);
    void bottomBorderChanged(Format *format);
    void leftBorderChanged(Format *format);
    void topBorderChanged(Format *format);

    WorksheetType mType;
    QString sSheetName;
    QMap<int, QMap<int, Cell*> > mCellData;
    QList<Cell*> m_cells;
    QMap<int, QMap<int, Format*> > mCellFormat;
    QList<Format*> mFormats;
    QMap<int, bool> mRowLocked;
    QMap<int, bool> mColLocked;
    QMap<int, Format*> mRowFormat;
    QMap<int, Format*> mColFormat;
    WorksheetModel *pModel;
    bool bShowGrid, bSheetLocked;

    QString sPath;

    PluginStore *pPluginStore;
    PluginStore* pluginStore() { return pPluginStore; }

    Worksheet *q_ptr;
    Q_DECLARE_PUBLIC(Worksheet)

};

#endif // WORKSHEETPRIVATE_H
