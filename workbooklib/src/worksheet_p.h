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
    void setCellAsCell(int, int, Cell*);
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
