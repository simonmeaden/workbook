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
#ifndef WORKSHEETVIEWPRIVATE_H
#define WORKSHEETVIEWPRIVATE_H

#include <QObject>
#include <QVariant>
#include <QItemSelection>
#include <QMessageBox>
#include <QList>
#include <QKeyEvent>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QHeaderView>

#include "workbook_global.h"
#include "cellreference.h"
#include "range.h"
#include "types.h"
#include "workbookparser.h"

namespace QXlsx {
    class Worksheet;
}

namespace ods {
    class Sheet;
}


namespace QWorkbook {

class QWorksheetView;
class PluginStore;
class Format;


class QWorksheetViewPrivate {
    Q_DECLARE_PUBLIC(QWorksheetView)
public:
    QWorksheetViewPrivate(QWorksheetView *parent);
    QWorksheetViewPrivate(const PWorkbookParser parser,
                          QWorksheetView *parent);
    virtual ~QWorksheetViewPrivate() {}

//    QAction *pCutActn, *pCopyActn, *pPasteActn, *pPasteSpecialActn, *pHideActn, *pShowActn;
//    QAction *pTextActn, *pNumberActn, *pFormulaActn;
//    QAction *pFormatCellsActn, *pInsertActn, *pDeleteActn;
//    QAction *pDeleteContentsActn, *pDeleteRowContentsActn, *pDeleteColumnContentsActn;
//    QAction *pRowHeightActn, *pColumnWidthActn, *pOptimalRowHeightActn, *pOptimalColumnWidthActn;
//    QAction *pInsertRowAboveActn, *pInsertColumnLeftActn, *pDeleteSelectedRowsActn, *pDeleteSelectedColumnsActn;
//    QAction *pClearDirectFormattingActn;
//    void createActions();
//    void customCellMenuRequested(QPoint pos);
//    void customRowHeaderMenuRequested(QPoint pos);
//    void customColumnHeaderMenuRequested(QPoint pos);
    void cut();
    void copy();
    void paste();
    void pasteSpecial();
    void text();
    void number();
    void formula();
    void hide();
    void show();
    void formatCells();
    void insertCells();
    void deleteCells();
    void deleteContents();
    void deleteRowContents();
    void deleteColumnContents();
    void rowHeight();
    void columnWidth();
    void optimalRowHeight();
    void optimalColumnWidth();
    void insertRowAbove();
    void insertColumnLeft();
    void deleteSelectedRows();
    void deleteSelectedColumns();
    void clearDirectFormatting();


    const PWorkbookParser pParser;

    QWorksheetView* clone();

    void saveWorksheet();
    void saveWorksheet(QString filename);
    void saveWorksheet(QString filename, WorksheetType type);
    void saveWorksheet(QXlsx::Worksheet *sheet);
    void saveWorksheet(ods::Sheet *sheet);

    QVariant read(int row, int column);
    QVariant read(const CellReference& reference);

    void write(int row, int column, QVariant item);
    void write(const CellReference& reference, QVariant item);
    void write(Range& range, QVariant item);

    Format* format(int row, int column);
    Format* format(const CellReference& reference);
    void setFormat(int row, int column, Format *format);
    void setSelectedFormat(Format *format);
    QMap<QModelIndex, Format*> selectedFormats();
    void setFormat(const CellReference& reference, Format *format);
    void setFormat(Range& range, Format *format);

    void triggerInitialSelection();
    void triggerCurrentSelection();

    // toolbar interaction
    void changeCellContents(QString);
//    void setValue(QVariant);
    void setSelectionBold(bool);
    void setSelectionItalic(bool);
    void setSelectionUnderline(bool);
    void setSelectionFont(QFont);
    void setSelectionFontSize(int);
    void setSelectionAlignment(Qt::Alignment);
    void setSelectionMerge();

    bool isLocked(int row, int column);
    bool isLocked(CellReference &ref);
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

    virtual void setSpan(int, int, int, int);
    void merge(int, int, int, int);
    void demerge(int, int, int, int);
    virtual MergeStatus checkClearSpan(int, int, int, int);
    void mergeDataToFirstCell(int row, int column, int rowSpan, int colSpan);
    void firstCellRetainedRestStored(int row, int column, int rowSpan, int colSpan);


    bool eventFilter(QObject *obj, QEvent *event);
    void commitAndMove(QModelIndex &currentIndex, int &row, int &column);

    bool bContiguous;
    FormatStatus mFormatStatus;
    QModelIndexList mItems;

    void selectionHasChanged(QItemSelection, QItemSelection);
    void cellHasChanged(QModelIndex, QModelIndex);

    void fileNotNamedMesssage();

    void init();
    void connectSignalsToParser();
    void disconnectSignalsFromParser();
    void setSheetName(QString);
    QString sheetName();

    QString mFilename;
    WorksheetType mFileType;

    QWorksheetView*  const q_ptr;

};


}

#endif // WORKSHEETVIEWPRIVATE_H
