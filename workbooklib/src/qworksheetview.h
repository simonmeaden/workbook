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
#ifndef QWORKSHEETVIEW_H
#define QWORKSHEETVIEW_H

#include <QObject>
#include <QWidget>
#include <QTableView>
#include <QVariant>
#include <QVariantList>
#include <QScopedPointer>
#include <QAction>
#include <QMenu>

#include "qworkbookview.h"
#include "cellreference.h"
#include "range.h"
#include "format.h"
#include "workbook_global.h"
#include "workbook_p.h"
#include "qworksheetview_p.h"

namespace QXlsx {
    class Worksheet;
}

namespace ods {
    class Sheet;
}

namespace QWorkbook {

class WorksheetModel;
class PluginStore;
class WorkbookParser;
class Cell;

class WORKBOOKSHARED_EXPORT QWorksheetView : public QTableView {
    Q_OBJECT
public:
    QWorksheetView(QWidget *parent);
    virtual ~QWorksheetView() {}


    QVariant read(int row, int column);
    QVariant read(const CellReference& reference);
    Format *format(int row, int column);
    Format *format(const CellReference& reference);

    QMap<QModelIndex, Format*> selectedFormats();

    QString sheetName();
    bool isLocked(int row, int column);
    bool isLocked(CellReference &ref);

signals:
    void selectionChanged(FormatStatus*);
    void cellChanged(QVariant); // called by current worksheet view when cell changes
    void contentsChanged(QString); // called by current worksheet view when cell changes
    void cellContentsChanged(QString); // called by cell editor when cell contents change before commit.

public slots:
    void setSheetName(QString);
//    void parse();

    void saveWorksheet();
    void saveWorksheet(QString filename);
    void saveWorksheet(QString filename, WorksheetType type);

    void write(int, int, QVariant);
    void write(const CellReference&, QVariant);
    void write(Range &, QVariant);

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

    void setFormat(int, int, Format*);
    void setFormat(const CellReference&, Format*);
    void setFormat(Range &, Format*);
    void setSelectedFormat(Format*);

    void changeCellContents(QString);

    void setSelectionBold(bool);
    void setSelectionItalic(bool);
    void setSelectionUnderline(bool);
    void setSelectionFont(QFont);
    void setSelectionFontSize(int);
    void setSelectionAlignment(Qt::Alignment);
    void setSelectionMerge();

    virtual void setSpan(int, int, int, int);

    void selectionHasChanged(const QItemSelection, const QItemSelection);
    void cellHasChanged(QModelIndex, QModelIndex);

    void fileNotNamedMesssage();

    void triggerInitialSelection();
    void triggerCurrentSelection();

protected slots:
    virtual bool eventFilter(QObject *obj, QEvent *event);
    void writeWorksheet(QXlsx::Worksheet *sheet);
    void writeWorksheet(ods::Sheet *sheet);

    void setModel(QAbstractItemModel *model);
    void setModel(WorksheetModel *model);

    void connectSignalsToParser();
    void disconnectSignalsFromParser();

    void createActions();
    void customCellMenuRequested(QPoint pos);
    void customRowHeaderMenuRequested(QPoint pos);
    void customColumnHeaderMenuRequested(QPoint pos);
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

protected:
    QWorksheetView(const PWorkbookParser &parser,
                   QWidget *parent);

    QModelIndexList selectedIndexes();
    WorksheetModel* model();

    QWorksheetView* clone();

    QAction *pCutActn, *pCopyActn, *pPasteActn, *pPasteSpecialActn, *pHideActn, *pShowActn;
    QAction *pTextActn, *pNumberActn, *pFormulaActn;
    QAction *pFormatCellsActn, *pInsertActn, *pDeleteActn;
    QAction *pDeleteContentsActn, *pDeleteRowContentsActn, *pDeleteColumnContentsActn;
    QAction *pRowHeightActn, *pColumnWidthActn, *pOptimalRowHeightActn, *pOptimalColumnWidthActn;
    QAction *pInsertRowAboveActn, *pInsertColumnLeftActn, *pDeleteSelectedRowsActn, *pDeleteSelectedColumnsActn;
    QAction *pClearDirectFormattingActn;

private:
    QScopedPointer<QWorksheetViewPrivate> d_ptr;
    Q_DECLARE_PRIVATE(QWorksheetView)

    friend class QWorkbookViewPrivate;
    friend class QWorkbookView;
    friend class WorkbookPrivate;
    friend class WorkbookParserPrivate;

};


}

#endif // WORKSHEETVIEW_H
