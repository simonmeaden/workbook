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
#include <QScopedPointer>

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

class  Worksheet : public QObject {
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
    QScopedPointer<WorksheetPrivate> d_ptr;

    Cell* cellAsCell(int row, int column);
    void setCellAsCell(int row, int column, Cell* cell);

    friend class WorksheetModel;

};


#endif // WORKSHEET_H
