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
#include <QtPlugin>



#include "qworksheetview.h"
#include "qworksheetview_p.h"
#include "worksheetmodel.h"
#include "formatdelegate.h"
#include "pluginstore.h"
#include "workbookparser.h"
#include "cell.h"
#include "workbook_global.h"

#include "xlsxworksheet.h"

#include "Sheet.hpp"

namespace QWorkbook {

/*!
    \brief Constructs a table view with a parent to represent the data.
*/
QWorksheetView::QWorksheetView(QWidget *parent) :
    QTableView(parent),
    d_ptr(new QWorksheetViewPrivate(this)) {

    int type = QMetaType::type("WorkbookParser");
    if (type == QMetaType::UnknownType)
        qRegisterMetaType<WorkbookParser>("WorkbookParser");

    createActions();
}

/*!
    \brief Constructs a table view with a parent to represent the data and a parser for formulae.
*/
QWorksheetView::QWorksheetView(const PWorkbookParser &parser,
                               QWidget *parent) :
    QTableView(parent),
    d_ptr(new QWorksheetViewPrivate(parser, this)) {

    createActions();
}

void QWorksheetView::connectSignalsToParser() {
    d_ptr->connectSignalsToParser();
}

void QWorksheetView::disconnectSignalsFromParser() {
    d_ptr->disconnectSignalsFromParser();
}

void QWorksheetView::createActions() {

    connect(this, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(customCellMenuRequested(QPoint)));
    connect(horizontalHeader(), SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(customRowHeaderMenuRequested(QPoint)));
    connect(verticalHeader(), SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(customColumnHeaderMenuRequested(QPoint)));

    pCutActn = new QAction(tr("Cu&t"), this);
    connect(pCutActn, SIGNAL(triggered(bool)), this, SLOT(cut()));

    pCopyActn = new QAction(tr("&Copy"), this);
    connect(pCopyActn, SIGNAL(triggered(bool)), this, SLOT(copy()));

    pPasteActn = new QAction(tr("&Paste"), this);
    connect(pPasteActn, SIGNAL(triggered(bool)), this, SLOT(paste()));

    pPasteSpecialActn = new QAction(tr("P&aste Special"), this);
    connect(pPasteSpecialActn, SIGNAL(triggered(bool)), this, SLOT(pasteSpecial()));

    pTextActn = new QAction(tr("&Text"), this);
    connect(pTextActn, SIGNAL(triggered(bool)), this, SLOT(text()));

    pNumberActn = new QAction(tr("&Text"), this);
    connect(pNumberActn, SIGNAL(triggered(bool)), this, SLOT(number()));

    pFormulaActn = new QAction(tr("&Text"), this);
    connect(pFormulaActn, SIGNAL(triggered(bool)), this, SLOT(formula()));

    pHideActn = new QAction(tr("&Hide"), this);
    connect(pHideActn, SIGNAL(triggered(bool)), this, SLOT(hide()));

    pShowActn = new QAction(tr("&Show"), this);
    connect(pShowActn, SIGNAL(triggered(bool)), this, SLOT(show()));

    pFormatCellsActn = new QAction(tr("&Format Cells"), this);
    connect(pFormatCellsActn, SIGNAL(triggered(bool)), this, SLOT(formatCells()));

    pInsertActn = new QAction(tr("&Insert"), this);
    connect(pInsertActn, SIGNAL(triggered(bool)), this, SLOT(insertCells()));

    pDeleteActn = new QAction(tr("De&lete"), this);
    connect(pDeleteActn, SIGNAL(triggered(bool)), this, SLOT(deleteCells()));

    pDeleteContentsActn = new QAction(tr("Delete C&ontents"), this);
    connect(pDeleteContentsActn, SIGNAL(triggered(bool)), this, SLOT(deleteContents()));

    pDeleteRowContentsActn = new QAction(tr("De&lete Row Contents"), this);
    connect(pDeleteRowContentsActn, SIGNAL(triggered(bool)), this, SLOT(deleteRowContents()));

    pDeleteColumnContentsActn = new QAction(tr("Delete C&olumn Contents"), this);
    connect(pDeleteColumnContentsActn, SIGNAL(triggered(bool)), this, SLOT(deleteColumnContents()));

    pRowHeightActn = new QAction(tr("Row Hei&ght"), this);
    connect(pRowHeightActn, SIGNAL(triggered(bool)), this, SLOT(rowHeight()));

    pColumnWidthActn = new QAction(tr("Col&umn Width"), this);
    connect(pColumnWidthActn, SIGNAL(triggered(bool)), this, SLOT(columnWidth()));

    pOptimalRowHeightActn = new QAction(tr("Optimal &Row Height"), this);
    connect(pOptimalRowHeightActn, SIGNAL(triggered(bool)), this, SLOT(optimalRowHeight()));

    pOptimalColumnWidthActn = new QAction(tr("O&ptimal Column Width"), this);
    connect(pOptimalColumnWidthActn, SIGNAL(triggered(bool)), this, SLOT(optimalColumnWidth()));

    pInsertRowAboveActn = new QAction(tr("&Insert Row Above"), this);
    connect(pInsertRowAboveActn, SIGNAL(triggered(bool)), this, SLOT(insertRowAbove()));

    pInsertColumnLeftActn = new QAction(tr("&Insert Column Left"), this);
    connect(pInsertColumnLeftActn, SIGNAL(triggered(bool)), this, SLOT(insertColumnLeft()));

    pDeleteSelectedRowsActn = new QAction(tr("&Delete Selected Rows"), this);
    connect(pDeleteSelectedRowsActn, SIGNAL(triggered(bool)), this, SLOT(deleteSelectedRows()));

    pDeleteSelectedColumnsActn = new QAction(tr("&Delete Selected Columns"), this);
    connect(pDeleteSelectedColumnsActn, SIGNAL(triggered(bool)), this, SLOT(deleteSelectedColumns()));

    pClearDirectFormattingActn = new QAction(tr("&Clear &Direct Formatting"), this);
    connect(pClearDirectFormattingActn, SIGNAL(triggered(bool)), this, SLOT(clearDirectFormatting()));

}

void QWorksheetView::customCellMenuRequested(QPoint pos) {
//    d_ptr->customCellMenuRequested(pos);
    QMenu *menu = new QMenu(this);
    QMenu *pasteOnlyMenu = new QMenu(tr("Paste Only"), this);

    pasteOnlyMenu->addAction(pTextActn);
    pasteOnlyMenu->addAction(pNumberActn);
    pasteOnlyMenu->addAction(pFormulaActn);

    menu->addAction(pCutActn);
    menu->addAction(pCopyActn);
    menu->addAction(pPasteActn);
    menu->addAction(pPasteSpecialActn);
    menu->addMenu(pasteOnlyMenu);
    menu->addSeparator();
    menu->addAction(pClearDirectFormattingActn);
    menu->addSeparator();
    menu->addAction(pFormatCellsActn);
    menu->addSeparator();
    menu->addAction(pInsertActn);
    menu->addAction(pDeleteActn);
    menu->addAction(pDeleteContentsActn);

    menu->popup(viewport()->mapToGlobal(pos));
}

void QWorksheetView::customRowHeaderMenuRequested(QPoint pos) {
//    d_ptr->customRowHeaderMenuRequested(pos);
    QMenu *menu = new QMenu(this);

    menu->addAction(pFormatCellsActn);
    menu->addSeparator();
    menu->addAction(pRowHeightActn);
    menu->addAction(pOptimalRowHeightActn);
    menu->addSeparator();
    menu->addAction(pInsertRowAboveActn);
    menu->addAction(pDeleteSelectedRowsActn);
    menu->addAction(pDeleteRowContentsActn);
    menu->addSeparator();
    menu->addAction(pHideActn);
    menu->addAction(pShowActn);
    menu->addSeparator();
    menu->addAction(pCutActn);
    menu->addAction(pCopyActn);
    menu->addAction(pPasteActn);
    menu->addAction(pPasteSpecialActn);

    menu->popup(viewport()->mapToGlobal(pos));
}

void QWorksheetView::customColumnHeaderMenuRequested(QPoint pos) {
//    d_ptr->customColumnHeaderMenuRequested(pos);
    QMenu *menu = new QMenu(this);

    menu->addAction(pFormatCellsActn);
    menu->addSeparator();
    menu->addAction(pColumnWidthActn);
    menu->addAction(pOptimalColumnWidthActn);
    menu->addSeparator();
    menu->addAction(pInsertColumnLeftActn);
    menu->addAction(pDeleteSelectedColumnsActn);
    menu->addAction(pDeleteColumnContentsActn);
    menu->addSeparator();
    menu->addAction(pHideActn);
    menu->addAction(pShowActn);
    menu->addSeparator();
    menu->addAction(pCutActn);
    menu->addAction(pCopyActn);
    menu->addAction(pPasteActn);
    menu->addAction(pPasteSpecialActn);

    menu->popup(viewport()->mapToGlobal(pos));
}

void QWorksheetView::cut() {
    d_ptr->cut();
}

void QWorksheetView::copy() {
    d_ptr->copy();
}

void QWorksheetView::paste() {
    d_ptr->paste();
}

void QWorksheetView::pasteSpecial() {
    d_ptr->pasteSpecial();
}

void QWorksheetView::text() {
    d_ptr->text();
}

void QWorksheetView::number() {
    d_ptr->number();
}

void QWorksheetView::formula() {
    d_ptr->formula();
}

void QWorksheetView::hide() {
    d_ptr->hide();
}

void QWorksheetView::show() {
    d_ptr->show();
}

void QWorksheetView::formatCells() {
    d_ptr->formatCells();
}

void QWorksheetView::insertCells() {
    d_ptr->insertCells();
}

void QWorksheetView::deleteCells() {
    d_ptr->deleteCells();
}

void QWorksheetView::deleteContents() {
    d_ptr->deleteContents();
}

void QWorksheetView::deleteRowContents() {
    d_ptr->deleteRowContents();
}

void QWorksheetView::deleteColumnContents() {
    d_ptr->deleteColumnContents();
}

void QWorksheetView::rowHeight() {
    d_ptr->rowHeight();
}

void QWorksheetView::columnWidth() {
    d_ptr->columnWidth();
}

void QWorksheetView::optimalRowHeight() {
    d_ptr->optimalRowHeight();
}

void QWorksheetView::optimalColumnWidth() {
    d_ptr->optimalColumnWidth();
}

void QWorksheetView::insertRowAbove() {
    d_ptr->insertRowAbove();
}

void QWorksheetView::insertColumnLeft() {
    d_ptr->insertColumnLeft();
}

void QWorksheetView::deleteSelectedRows() {
    d_ptr->deleteSelectedRows();
}

void QWorksheetView::deleteSelectedColumns() {
    d_ptr->deleteSelectedColumns();
}

void QWorksheetView::clearDirectFormatting() {
    d_ptr->clearDirectFormatting();
}

/*!
    \brief Saves the worksheet to file.

    This version requires that the filename and file type be already set up. Basically
    used to resave an already saved file. Sends a file not set dialog box to warn the user.
*/
void QWorksheetView::saveWorksheet() {
    d_ptr->saveWorksheet();
}

/*!
    \brief Saves the worksheet to file.

    This version sets the filename for the file and saves it to the default WorksheetType
    which is ODS.
*/
void QWorksheetView::saveWorksheet(QString filename) {
    d_ptr->saveWorksheet(filename);
}

/*!
    \brief Saves the worksheet to file.

    This version sets the filename for the file and saves it to the specified WorksheetType.
*/
void QWorksheetView::saveWorksheet(QString filename, WorksheetType type) {
    d_ptr->saveWorksheet(filename, type);
}

/*!
    \brief Saves the worksheet to file.

    This version is for the use of QWorkbook and requires a document already created.
*/
void QWorksheetView::writeWorksheet(QXlsx::Worksheet *sheet) {
    d_ptr->saveWorksheet(sheet);
}

/*!
    \brief Saves the worksheet to file.

    This version is for the use of QWorkbook and requires a document already created.
*/
void QWorksheetView::writeWorksheet(ods::Sheet *sheet) {
    d_ptr->saveWorksheet(sheet);
}

/*!
    \brief Set
    \param name
*/
void QWorksheetView::setSheetName(QString name) {
    d_ptr->setSheetName(name);
}

QString QWorksheetView::sheetName() {
    return d_ptr->sheetName();
}

QWorksheetView* QWorksheetView::clone() {
    return d_ptr->clone();
}

//void QWorksheetView::parse() {
//    d_ptr->parse();
//}

/*!
    \internal

    \brief triggers a cell selection on the top left cell.

    This trigger is used internally to set up the toolbars
    correctly on initialising.
*/
void QWorksheetView::triggerInitialSelection() {
    d_ptr->triggerInitialSelection();
}

/*!
    \internal

    \brief triggers a cell selection on the current cell.

    This trigger is used internally to set up the toolbars
    correctly on workbsheet change..
*/
void QWorksheetView::triggerCurrentSelection() {
    d_ptr->triggerCurrentSelection();
}

bool QWorksheetView::eventFilter(QObject *obj, QEvent *event) {
    return d_ptr->eventFilter(obj, event);
}

void QWorksheetView::selectionHasChanged(const QItemSelection selected, const QItemSelection deselected) {
    d_ptr->selectionHasChanged(selected, deselected);
}

void QWorksheetView::cellHasChanged(QModelIndex current, QModelIndex previous) {
    d_ptr->cellHasChanged(current, previous);
}

void QWorksheetView::changeCellContents(QString value) {
    d_ptr->changeCellContents(value);
}

void QWorksheetView::setSelectionBold(bool value) {
    d_ptr->setSelectionBold(value);
}

void QWorksheetView::setSelectionItalic(bool value) {
    d_ptr->setSelectionItalic(value);
}

void QWorksheetView::setSelectionUnderline(bool value) {
    d_ptr->setSelectionUnderline(value);
}

void QWorksheetView::setSelectionFont(QFont font) {
    d_ptr->setSelectionFont(font);
}

void QWorksheetView::setSelectionFontSize(int size) {
    d_ptr->setSelectionFontSize(size);
}

void QWorksheetView::setSelectionAlignment(Qt::Alignment alignment) {
    d_ptr->setSelectionAlignment(alignment);
}

void QWorksheetView::setSelectionMerge(/*bool merge*/) {
    d_ptr->setSelectionMerge(/*merge*/);
}

void QWorksheetView::setSpan(int row, int column, int rowSpan, int colSpan) {
    Q_ASSERT(row > 0 && column > 0);
    d_ptr->setSpan(row - 1, column - 1, rowSpan, colSpan);
}

WorksheetModel* QWorksheetView::model() {
    return qobject_cast<WorksheetModel*>(QTableView::model());
}

void QWorksheetView::setModel(WorksheetModel *model) {
    QTableView::setModel(model);
}

void QWorksheetView::setModel(QAbstractItemModel *model) {
    WorksheetModel *m = dynamic_cast<WorksheetModel*>(model);
    if (m)
        QTableView::setModel(model);
}

QModelIndexList QWorksheetView::selectedIndexes() {
    return selectionModel()->selectedIndexes();
}

QVariant QWorksheetView::read(int row, int column) {
    Q_ASSERT(row > 0 && column > 0);
    return d_ptr->read(row - 1, column - 1);
}

QVariant QWorksheetView::read(const CellReference& reference) {
    return read(reference);
}

void QWorksheetView::write(int row, int column, QVariant item) {
    Q_ASSERT(row > 0 && column > 0);
    d_ptr->write(row - 1, column - 1, item);
}

void QWorksheetView::write(const CellReference& reference, QVariant item) {
    d_ptr->write(reference, item);
}

void QWorksheetView::write(Range& range, QVariant item) {
    d_ptr->write(range, item);
}

void QWorksheetView::fileNotNamedMesssage() {
    d_ptr->fileNotNamedMesssage();
}

Format* QWorksheetView::format(int row, int column) {
    Q_ASSERT(row > 0 && column > 0);
    return d_ptr->format(row - 1, column - 1);
}

Format* QWorksheetView::format(const CellReference& reference) {
    return d_ptr->format(reference);
}

void QWorksheetView::setFormat(int row, int column, Format *format) {
    Q_ASSERT(row > 0 && column > 0);
    d_ptr->setFormat(row - 1, column - 1, format);
}

void QWorksheetView::setSelectedFormat(Format *format) {
    d_ptr->setSelectedFormat(format);
}

QMap<QModelIndex, Format*> QWorksheetView::selectedFormats() {
    return d_ptr->selectedFormats();
}

void QWorksheetView::setFormat(const CellReference& reference, Format *format) {
    d_ptr->setFormat(reference, format);

}

void QWorksheetView::setFormat(Range& range, Format *format) {
    d_ptr->setFormat(range, format);
}

bool QWorksheetView::isLocked(CellReference &ref) {
    return d_ptr->isLocked(ref.row(), ref.column());
}

bool QWorksheetView::isLocked(int row, int column) {
    Q_ASSERT(row > 0 && column > 0);
    return d_ptr->isLocked(row, column);
}

void QWorksheetView::lockSheet() {
    d_ptr->lockSheet();
}

void QWorksheetView::unlockSheet() {
    d_ptr->unlockSheet();
}

void QWorksheetView::lockCell(int row, int column) {
    Q_ASSERT(row > 0 && column > 0);
    d_ptr->lockCell(row, column);
}

void QWorksheetView::lockCell(CellReference &ref) {
    d_ptr->lockCell(ref.row(), ref.column());
}

void QWorksheetView::lockRow(int &row) {
    Q_ASSERT(row > 0);
    d_ptr->lockRow(row);
}

void QWorksheetView::lockColumn(int &column) {
    Q_ASSERT(column > 0);
    d_ptr->lockColumn(column);
}

void QWorksheetView::lockRange(Range &range) {
    d_ptr->lockRange(range);
}

void QWorksheetView::unlockCell(int row, int column) {
    Q_ASSERT(row > 0 && column > 0);
    d_ptr->unlockCell(row, column);
}

void QWorksheetView::unlockCell(CellReference &ref) {
    d_ptr->unlockCell(ref.row(), ref.column());
}

void QWorksheetView::unlockRow(int &row) {
    Q_ASSERT(row > 0);
    d_ptr->unlockRow(row);
}

void QWorksheetView::unlockColumn(int &column) {
    Q_ASSERT(column > 0);
    d_ptr->unlockColumn(column);
}

void QWorksheetView::unlockRange(Range &range) {
    d_ptr->unlockRange(range);
}


}

