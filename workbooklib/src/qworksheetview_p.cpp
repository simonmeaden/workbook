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
#include "qworksheetview_p.h"
#include "qworksheetview.h"
#include "formatdelegate.h"
#include "worksheetmodel.h"

#include "workbook_global.h"
#include "pluginstore.h"
#include "workbookparser.h"
#include "cell.h"
#include "mergedcell.h"

#include "workbookparser.h"

#include "xlsxworksheet.h"

#include <Sheet.hpp>

namespace QWorkbook {

QWorksheetViewPrivate::QWorksheetViewPrivate(QWorksheetView *parent) :
    pParser(PWorkbookParser(new WorkbookParser(parent))),
    q_ptr(parent) {

    init();
    connectSignalsToParser();

    pParser->start();

}

QWorksheetViewPrivate::QWorksheetViewPrivate(const PWorkbookParser parser,
        QWorksheetView *parent) :
    pParser(parser),
    q_ptr(parent) {

    init();

    pParser->start();

}


void QWorksheetViewPrivate::saveWorksheet() {
    if (mFilename.isEmpty()) {
        fileNotNamedMesssage();
    } else {
        mFileType = ODS;
        saveWorksheet(mFilename);
    }
}

void QWorksheetViewPrivate::saveWorksheet(QString filename) {
    mFilename = filename;
    saveWorksheet(mFilename, mFileType);
}

void QWorksheetViewPrivate::saveWorksheet(QString filename, WorksheetType type) {
    q_ptr->model()->saveWorksheet(filename, type);
}

void QWorksheetViewPrivate::saveWorksheet(QXlsx::Worksheet *sheet) {
    q_ptr->model()->saveWorksheet(sheet);
}

void QWorksheetViewPrivate::saveWorksheet(ods::Sheet *sheet) {
    q_ptr->model()->saveWorksheet(sheet);
}

QWorksheetView* QWorksheetViewPrivate::clone() {
    QWorksheetView *view = new QWorksheetView(pParser, qobject_cast<QWidget*>(q_ptr->parent()));
    view->setModel(q_ptr->model()->clone());
    return view;
}

void QWorksheetViewPrivate::init() {

    WorksheetModel *model = new WorksheetModel(q_ptr);
    q_ptr->setModel(model);
    q_ptr->setItemDelegate(new FormatDelegate(q_ptr));

    q_ptr->connect(model, SIGNAL(fileHasNotBeenNamedMessage()),
                   q_ptr, SLOT(fileNotNamedMesssage()));

    q_ptr->setContextMenuPolicy(Qt::CustomContextMenu);
//    q_ptr->connect(q_ptr, SIGNAL(customContextMenuRequested(QPoint)),
//                   q_ptr, SLOT(customCellMenuRequested(QPoint)));
//    q_ptr->connect(q_ptr->horizontalHeader(), SIGNAL(customContextMenuRequested(QPoint)),
//                   q_ptr, SLOT(customRowHeaderMenuRequested(QPoint)));
//    q_ptr->connect(q_ptr->verticalHeader(), SIGNAL(customContextMenuRequested(QPoint)),
//                   q_ptr, SLOT(customColumnHeaderMenuRequested(QPoint)));

    bContiguous = true;

    q_ptr->setSelectionMode(QTableView::ExtendedSelection);

    QItemSelectionModel *sModel = q_ptr->selectionModel();
    q_ptr->connect(sModel,
                   SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
                   q_ptr,
                   SLOT(selectionHasChanged(QItemSelection, QItemSelection)));
    q_ptr->connect(sModel, SIGNAL(currentChanged(QModelIndex,QModelIndex)),
                   q_ptr, SLOT(cellHasChanged(QModelIndex,QModelIndex)));


    // catches all events, and passes on whatever it doesn't want
    q_ptr->installEventFilter(q_ptr);

//    createActions();

}

//void QWorksheetViewPrivate::createActions() {

//    pCutActn = new QAction(q_ptr->tr("Cu&t"), q_ptr);
//    q_ptr->connect(pCutActn, SIGNAL(triggered(bool)), q_ptr, SLOT(cut()));

//    pCopyActn = new QAction(q_ptr->tr("&Copy"), q_ptr);
//    q_ptr->connect(pCopyActn, SIGNAL(triggered(bool)), q_ptr, SLOT(copy()));

//    pPasteActn = new QAction(q_ptr->tr("&Paste"), q_ptr);
//    q_ptr->connect(pPasteActn, SIGNAL(triggered(bool)), q_ptr, SLOT(paste()));

//    pPasteSpecialActn = new QAction(q_ptr->tr("P&aste Special"), q_ptr);
//    q_ptr->connect(pPasteSpecialActn, SIGNAL(triggered(bool)), q_ptr, SLOT(pasteSpecial()));

//    pTextActn = new QAction(q_ptr->tr("&Text"), q_ptr);
//    q_ptr->connect(pTextActn, SIGNAL(triggered(bool)), q_ptr, SLOT(text()));

//    pNumberActn = new QAction(q_ptr->tr("&Text"), q_ptr);
//    q_ptr->connect(pNumberActn, SIGNAL(triggered(bool)), q_ptr, SLOT(number()));

//    pFormulaActn = new QAction(q_ptr->tr("&Text"), q_ptr);
//    q_ptr->connect(pFormulaActn, SIGNAL(triggered(bool)), q_ptr, SLOT(formula()));

//    pHideActn = new QAction(q_ptr->tr("&Hide"), q_ptr);
//    q_ptr->connect(pHideActn, SIGNAL(triggered(bool)), q_ptr, SLOT(hide()));

//    pShowActn = new QAction(q_ptr->tr("&Show"), q_ptr);
//    q_ptr->connect(pShowActn, SIGNAL(triggered(bool)), q_ptr, SLOT(show()));

//    pFormatCellsActn = new QAction(q_ptr->tr("&Format Cells"), q_ptr);
//    q_ptr->connect(pFormatCellsActn, SIGNAL(triggered(bool)), q_ptr, SLOT(formatCells()));

//    pInsertActn = new QAction(q_ptr->tr("&Insert"), q_ptr);
//    q_ptr->connect(pInsertActn, SIGNAL(triggered(bool)), q_ptr, SLOT(insertCells()));

//    pDeleteActn = new QAction(q_ptr->tr("De&lete"), q_ptr);
//    q_ptr->connect(pDeleteActn, SIGNAL(triggered(bool)), q_ptr, SLOT(deleteCells()));

//    pDeleteContentsActn = new QAction(q_ptr->tr("Delete C&ontents"), q_ptr);
//    q_ptr->connect(pDeleteContentsActn, SIGNAL(triggered(bool)), q_ptr, SLOT(deleteContents()));

//    pDeleteRowContentsActn = new QAction(q_ptr->tr("De&lete Row Contents"), q_ptr);
//    q_ptr->connect(pDeleteRowContentsActn, SIGNAL(triggered(bool)), q_ptr, SLOT(deleteRowContents()));

//    pDeleteColumnContentsActn = new QAction(q_ptr->tr("Delete C&olumn Contents"), q_ptr);
//    q_ptr->connect(pDeleteColumnContentsActn, SIGNAL(triggered(bool)), q_ptr, SLOT(deleteColumnContents()));

//    pRowHeightActn = new QAction(q_ptr->tr("Row Hei&ght"), q_ptr);
//    q_ptr->connect(pRowHeightActn, SIGNAL(triggered(bool)), q_ptr, SLOT(rowHeight()));

//    pColumnWidthActn = new QAction(q_ptr->tr("Col&umn Width"), q_ptr);
//    q_ptr->connect(pColumnWidthActn, SIGNAL(triggered(bool)), q_ptr, SLOT(columnWidth()));

//    pOptimalRowHeightActn = new QAction(q_ptr->tr("Optimal &Row Height"), q_ptr);
//    q_ptr->connect(pOptimalRowHeightActn, SIGNAL(triggered(bool)), q_ptr, SLOT(optimalRowHeight()));

//    pOptimalColumnWidthActn = new QAction(q_ptr->tr("O&ptimal Column Width"), q_ptr);
//    q_ptr->connect(pOptimalColumnWidthActn, SIGNAL(triggered(bool)), q_ptr, SLOT(optimalColumnWidth()));

//    pInsertRowAboveActn = new QAction(q_ptr->tr("&Insert Row Above"), q_ptr);
//    q_ptr->connect(pInsertRowAboveActn, SIGNAL(triggered(bool)), q_ptr, SLOT(insertRowAbove()));

//    pInsertColumnLeftActn = new QAction(q_ptr->tr("&Insert Column Left"), q_ptr);
//    q_ptr->connect(pInsertColumnLeftActn, SIGNAL(triggered(bool)), q_ptr, SLOT(insertColumnLeft()));

//    pDeleteSelectedRowsActn = new QAction(q_ptr->tr("&Delete Selected Rows"), q_ptr);
//    q_ptr->connect(pDeleteSelectedRowsActn, SIGNAL(triggered(bool)), q_ptr, SLOT(deleteSelectedRows()));

//    pDeleteSelectedColumnsActn = new QAction(q_ptr->tr("&Delete Selected Columns"), q_ptr);
//    q_ptr->connect(pDeleteSelectedColumnsActn, SIGNAL(triggered(bool)), q_ptr, SLOT(deleteSelectedColumns()));

//    pClearDirectFormattingActn = new QAction(q_ptr->tr("&Clear &Direct Formatting"), q_ptr);
//    q_ptr->connect(pClearDirectFormattingActn, SIGNAL(triggered(bool)), q_ptr, SLOT(clearDirectFormatting()));

//}

//void QWorksheetViewPrivate::customCellMenuRequested(QPoint pos) {
//    QMenu *menu = new QMenu(q_ptr);
//    QMenu *pasteOnlyMenu = new QMenu(q_ptr->tr("Paste Only"), q_ptr);

//    pasteOnlyMenu->addAction(pTextActn);
//    pasteOnlyMenu->addAction(pNumberActn);
//    pasteOnlyMenu->addAction(pFormulaActn);

//    menu->addAction(pCutActn);
//    menu->addAction(pCopyActn);
//    menu->addAction(pPasteActn);
//    menu->addAction(pPasteSpecialActn);
//    menu->addMenu(pasteOnlyMenu);
//    menu->addSeparator();
//    menu->addAction(pClearDirectFormattingActn);
//    menu->addSeparator();
//    menu->addAction(pFormatCellsActn);
//    menu->addSeparator();
//    menu->addAction(pInsertActn);
//    menu->addAction(pDeleteActn);
//    menu->addAction(pDeleteContentsActn);

//    menu->popup(q_ptr->viewport()->mapToGlobal(pos));
//}

//void QWorksheetViewPrivate::customRowHeaderMenuRequested(QPoint pos) {
//    QMenu *menu = new QMenu(q_ptr);

//    menu->addAction(pFormatCellsActn);
//    menu->addSeparator();
//    menu->addAction(pRowHeightActn);
//    menu->addAction(pOptimalRowHeightActn);
//    menu->addSeparator();
//    menu->addAction(pInsertRowAboveActn);
//    menu->addAction(pDeleteSelectedRowsActn);
//    menu->addAction(pDeleteRowContentsActn);
//    menu->addSeparator();
//    menu->addAction(pHideActn);
//    menu->addAction(pShowActn);
//    menu->addSeparator();
//    menu->addAction(pCutActn);
//    menu->addAction(pCopyActn);
//    menu->addAction(pPasteActn);
//    menu->addAction(pPasteSpecialActn);

//    menu->popup(q_ptr->viewport()->mapToGlobal(pos));
//}

//void QWorksheetViewPrivate::customColumnHeaderMenuRequested(QPoint pos) {
//    QMenu *menu = new QMenu(q_ptr);

//    menu->addAction(pFormatCellsActn);
//    menu->addSeparator();
//    menu->addAction(pColumnWidthActn);
//    menu->addAction(pOptimalColumnWidthActn);
//    menu->addSeparator();
//    menu->addAction(pInsertColumnLeftActn);
//    menu->addAction(pDeleteSelectedColumnsActn);
//    menu->addAction(pDeleteColumnContentsActn);
//    menu->addSeparator();
//    menu->addAction(pHideActn);
//    menu->addAction(pShowActn);
//    menu->addSeparator();
//    menu->addAction(pCutActn);
//    menu->addAction(pCopyActn);
//    menu->addAction(pPasteActn);
//    menu->addAction(pPasteSpecialActn);

//    menu->popup(q_ptr->viewport()->mapToGlobal(pos));
//}

void QWorksheetViewPrivate::cut() {
    // TODO
}

void QWorksheetViewPrivate::copy() {
    // TODO
}

void QWorksheetViewPrivate::paste() {
    // TODO
}

void QWorksheetViewPrivate::pasteSpecial() {
    // TODO
}

void QWorksheetViewPrivate::text() {
    // TODO
}

void QWorksheetViewPrivate::number() {
    // TODO
}

void QWorksheetViewPrivate::formula() {
    // TODO
}

void QWorksheetViewPrivate::hide() {
    // TODO
}

void QWorksheetViewPrivate::show() {
    // TODO
}

void QWorksheetViewPrivate::formatCells() {
    // TODO
}

void QWorksheetViewPrivate::insertCells() {
    // TODO
}

void QWorksheetViewPrivate::deleteCells() {
    // TODO
}

void QWorksheetViewPrivate::deleteContents() {
    // TODO
}

void QWorksheetViewPrivate::deleteRowContents() {
    // TODO
}

void QWorksheetViewPrivate::deleteColumnContents() {
    // TODO
}

void QWorksheetViewPrivate::rowHeight() {
    // TODO
}

void QWorksheetViewPrivate::columnWidth() {
    // TODO
}

void QWorksheetViewPrivate::optimalRowHeight() {
    // TODO
}

void QWorksheetViewPrivate::optimalColumnWidth() {
    // TODO
}

void QWorksheetViewPrivate::insertRowAbove() {
    // TODO
}

void QWorksheetViewPrivate::insertColumnLeft() {
    // TODO
}

void QWorksheetViewPrivate::deleteSelectedRows() {
    // TODO
}

void QWorksheetViewPrivate::deleteSelectedColumns() {
    // TODO
}

void QWorksheetViewPrivate::clearDirectFormatting() {
    // TODO
}


void QWorksheetViewPrivate::connectSignalsToParser() {
    q_ptr->connect(q_ptr->model(), SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
                   pParser.data(), SLOT(dataHasChanged(QModelIndex,QModelIndex,QVector<int>)));
}

void QWorksheetViewPrivate::disconnectSignalsFromParser() {
    q_ptr->disconnect(q_ptr->model(), SIGNAL(fileHasNotBeenNamedMessage()),
                      q_ptr, SLOT(fileNotNamedMesssage()));
    q_ptr->disconnect(q_ptr->model(), SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
                      pParser.data(), SLOT(dataHasChanged(QModelIndex,QModelIndex,QVector<int>)));

}

void QWorksheetViewPrivate::triggerInitialSelection() {
    QModelIndex index = q_ptr->model()->index(0, 0);
    QItemSelection selection(index, index);
    selectionHasChanged(selection, selection);
}

void QWorksheetViewPrivate::triggerCurrentSelection() {
    QModelIndex index = q_ptr->currentIndex();
    QItemSelection selection(index, index);
    selectionHasChanged(selection, selection);
}

void QWorksheetViewPrivate:: commitAndMove(QModelIndex &currentIndex, int &newRow, int &newColumn) {
    q_ptr->currentChanged(currentIndex, currentIndex);

    QModelIndex index = q_ptr->model()->index(newRow, newColumn);
    q_ptr->setCurrentIndex(index);
}

bool QWorksheetViewPrivate::eventFilter(QObject *obj, QEvent *event) {

    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        int key = keyEvent->key();
        Qt::KeyboardModifiers modifiers = keyEvent->modifiers();
        QModelIndex currentIndex = q_ptr->currentIndex();
        int row = currentIndex.row();
        int column = currentIndex.column();

        switch (key) {
        case Qt::Key_Right:
            // TODO get this to work when editing. The editor grabs the right/left key first.
            column++;
            commitAndMove(currentIndex, row, column);
            break;
        case Qt::Key_Left:
            // TODO get this to work when editing. The editor grabs the right/left key first.
            if (column > 0)
                column--;
            commitAndMove(currentIndex, row, column);
            break;
        case Qt::Key_Up:
            if (row > 0)
                row--;
            commitAndMove(currentIndex, row, column);
            break;
        case Qt::Key_Down:
            row++;
            commitAndMove(currentIndex, row, column);
            break;
        case Qt::Key_Enter:
        case Qt::Key_Return:
            if (modifiers.testFlag(Qt::ShiftModifier)) {
                if (row > 0) {
                    row--;
                }
            } else {
                row++;
            }
            commitAndMove(currentIndex, row, column);
            break;
        case Qt::Key_Tab:
            if (modifiers.testFlag(Qt::ShiftModifier)) {
                if (column > 0) {
                    column--;
                }
            } else {
                column++;
            }
            commitAndMove(currentIndex, row, column);
            break;
        case Qt::Key_Home:
            column = 0;
            commitAndMove(currentIndex, row, column);
            break;
        case Qt::Key_End:
            column = q_ptr->model()->maxColumn();
            commitAndMove(currentIndex, row, column);
            break;
        case Qt::Key_PageUp:
            row = 0;
            commitAndMove(currentIndex, row, column);
            break;
        case Qt::Key_PageDown:
            row = q_ptr->model()->maxRow();
            commitAndMove(currentIndex, row, column);
            break;
        default:
            // I don't need it so pass it back.
            return q_ptr->QObject::eventFilter(obj, event);
        }
        return true;
    } else {
        // standard event processing
        return q_ptr->QObject::eventFilter(obj, event);
    }
    return false;
}

void QWorksheetViewPrivate::setSheetName(QString name) {
    q_ptr->model()->setSheetName(name);
}

QString QWorksheetViewPrivate::sheetName() {
    return q_ptr->model()->sheetName();
}

void QWorksheetViewPrivate::cellHasChanged(QModelIndex current, QModelIndex /*previous*/) {
    Q_Q(QWorksheetView);

    QVariant value = q_ptr->model()->data(current);
    emit q->cellChanged(value);
    emit q->contentsChanged(value.toString());
}

void QWorksheetViewPrivate::selectionHasChanged(QItemSelection /*selected*/, QItemSelection /*deselected*/) {
//    QModelIndex index;
    /*  DONT USE THE ABOVE selected & deselected AS THEY GIVE WIERD RESULTS
        USE selectionModel()->selectedIndexes() instead.
        why they miss items out i am not entirely sure.
    */

    Q_Q(QWorksheetView);

    mFormatStatus.clear();

    mItems = q_ptr->selectionModel()->selectedIndexes();
    QList<Format*> formats;
    Format* format;
    int row, col;

    if (mItems.size() == 1) {
        QString v = q_ptr->model()->data(mItems.at(0)).toString();
        // TODO emit change to cell editor bar
    }

    foreach (QModelIndex index, mItems) {
        row = index.row();
        col = index.column();
        mFormatStatus.mCount++;
        mFormatStatus.mMinRow = (row < mFormatStatus.mMinRow ? row : mFormatStatus.mMinRow);
        mFormatStatus.mMaxRow = (row > mFormatStatus.mMaxRow ? row : mFormatStatus.mMaxRow);
        mFormatStatus.mMinCol = (col < mFormatStatus.mMinCol ? col : mFormatStatus.mMinCol);
        mFormatStatus.mMaxCol = (col > mFormatStatus.mMaxCol ? col : mFormatStatus.mMaxCol);

        if (index.isValid()) {
            format = q_ptr->model()->format(index);
            formats.append(format);
        }

    }

    int maxPossibleRange = (mFormatStatus.mMaxRow - mFormatStatus.mMinRow + 1) *
                           (mFormatStatus.mMaxCol - mFormatStatus.mMinCol + 1);

    if (maxPossibleRange > mFormatStatus.mCount)
        mFormatStatus.bContiguous = false;
    else
        mFormatStatus.bContiguous = true;

    bContiguous = mFormatStatus.bContiguous;

//    qDebug() << (bContiguous ? "contiguous" : "non-contiguous");

    if (formats.size() == 0) {
        emit q->selectionChanged(NULL);
        return;
    }


    format = formats.at(0);
    QFont font = format->font();
    int fontSize = font.pointSize();
    bool bold = format->bold();
    bool italic = format->italic();
    bool underline = format->underline();
    Qt::Alignment alignment = format->alignment();
    UnderlineStyle uStyle = format->underlineStyle();
    QColor uColor = format->underlineColor();
    bool overline = format->overline();
    bool strikeout = format->strikeout();

    mFormatStatus.bAllBold = !bold;
    mFormatStatus.bAllItalic = !italic;
    mFormatStatus.bAllOverline = !overline;
    mFormatStatus.bAllStrikeout = !strikeout;
    mFormatStatus.bAllUnderline = !underline;
//    mFormatStatus.bAllUnderline = (uStyle == format->underlineStyle());
//    mFormatStatus.bAllUnderline = (uColor == format->underlineColor());
    mFormatStatus.bAllSameFont = (font == format->font());
//    mFormatStatus.bAllSameAlignment = true; // already done

    for(int i = 1; i < formats.size(); i++) {
        format = formats.at(i);

        if (mFormatStatus.bAllBold)
            if (bold != format->bold())
                mFormatStatus.bAllBold = false;

        if (mFormatStatus.bAllItalic)
            if (italic != format->italic())
                mFormatStatus.bAllItalic = false;

        if (mFormatStatus.bAllOverline)
            if (overline != format->overline())
                mFormatStatus.bAllOverline = false;

        if (mFormatStatus.bAllStrikeout)
            if (strikeout != format->strikeout())
                mFormatStatus.bAllStrikeout = false;

        if (mFormatStatus.bAllUnderline)
            if (underline != format->underline())
                mFormatStatus.bAllUnderline = false;

        if (mFormatStatus.bAllUnderline)
            if (uStyle != format->underlineStyle())
                mFormatStatus.bAllUnderline = false;

        if (mFormatStatus.bAllUnderline)
            if (uColor != format->underlineColor())
                mFormatStatus.bAllUnderline = false;

        if (mFormatStatus.bAllSameFont)
            if (font != format->font())
                mFormatStatus.bAllSameFont = false;

        if (mFormatStatus.bAllSameAlignment)
            if (alignment != format->alignment())
                mFormatStatus.bAllSameAlignment = false;

        if (mFormatStatus.allSet()) break;
    }

    if (mFormatStatus.bAllSameFont) {
        mFormatStatus.mFont = font;
        mFormatStatus.mFontSize = fontSize;
    }

    if (mFormatStatus.bAllSameAlignment) {
        mFormatStatus.mAlignment = alignment;
    }

    emit q->selectionChanged(&mFormatStatus);

}

void QWorksheetViewPrivate::changeCellContents(QString value) {
    QModelIndex index = q_ptr->selectionModel()->currentIndex();
    if (index.isValid()) {
        q_ptr->model()->setData(index, value, Qt::EditRole);
    }
}

void QWorksheetViewPrivate::setSelectionBold(bool value) {

    Format* format;
    int row, col;

    foreach (QModelIndex index, mItems) {

        if (index.isValid()) {
            row = index.row();
            col = index.column();

            format = q_ptr->model()->format(index);
            format->setBold(value);
            q_ptr->setFormat(row, col, format);
        }

    }
}

void QWorksheetViewPrivate::setSelectionItalic(bool value) {

    Format* format;
    int row, col;

    foreach (QModelIndex index, mItems) {

        if (index.isValid()) {
            row = index.row();
            col = index.column();

            format = q_ptr->model()->format(index);
            format->setItalic(value);
            q_ptr->setFormat(row, col, format);
        }

    }
}

void QWorksheetViewPrivate::setSelectionUnderline(bool value) {

    Format* format;
    int row, col;

    foreach (QModelIndex index, mItems) {

        if (index.isValid()) {
            row = index.row();
            col = index.column();

            format = q_ptr->model()->format(index);
            format->setUnderline(value);
            q_ptr->setFormat(row, col, format);
        }

    }
}

void QWorksheetViewPrivate::setSelectionFont(QFont font) {

    Format* format;
    int row, col;

    foreach (QModelIndex index, mItems) {

        if (index.isValid()) {
            row = index.row();
            col = index.column();

            format = q_ptr->model()->format(index);
            format->setFont(font);
//            qDebug() << font.family() << " : " << font.pointSize();
            q_ptr->setFormat(row, col, format);
        }

    }
}

void QWorksheetViewPrivate::setSelectionFontSize(int size) {

    Format* format;
    int row, col;

    foreach (QModelIndex index, mItems) {

        if (index.isValid()) {
            row = index.row();
            col = index.column();

            format = q_ptr->model()->format(index);
            format->setPointSize(size);
            q_ptr->setFormat(row, col, format);
        }

    }
}

void QWorksheetViewPrivate::setSelectionAlignment(Qt::Alignment alignment) {

    Format* format;
    int row, col;

    foreach (QModelIndex index, mItems) {

        if (index.isValid()) {
            row = index.row();
            col = index.column();

            format = q_ptr->model()->format(index);
            format->setAlignment(alignment);
            q_ptr->setFormat(row, col, format);
        }

    }
}

void QWorksheetViewPrivate::setSelectionMerge(/*bool merge*/) {
    if (bContiguous) {
        int row = mFormatStatus.mMinRow;
        int col = mFormatStatus.mMinCol;
        int rowSpan = mFormatStatus.mMaxRow - mFormatStatus.mMinRow + 1;
        int colSpan = mFormatStatus.mMaxCol - mFormatStatus.mMinCol + 1;
        setSpan(row, col, rowSpan, colSpan);
    }
}

void QWorksheetViewPrivate::setSpan(int row, int column, int rowSpan, int colSpan) {

    MergeStatus status = checkClearSpan(row, column, rowSpan, colSpan);

    switch (status) {
    case MergePossible: {

        merge(row, column, rowSpan, colSpan);

        break;
    }
    case DemergePossible: {

        demerge(row, column, rowSpan, colSpan);

        break;
    }
    case ContainsMerge:
        QMessageBox::warning(q_ptr,
                             qApp->applicationDisplayName(),
                             q_ptr->tr("Cell merge not possible if cells already merged"),
                             QMessageBox::Ok,
                             QMessageBox::Ok);
        break;
    }

}

void QWorksheetViewPrivate::merge(int row, int column, int rowSpan, int colSpan) {

    QMessageBox::StandardButton btn = QMessageBox::question(q_ptr,
                                      qApp->applicationDisplayName(),
                                      q_ptr->tr("Should the contents of the hidden cells be moved into the first cell?"),
                                      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                                      QMessageBox::No);

    switch (btn) {
    case QMessageBox::Yes: // all contents merged. Old data lost.
        mergeDataToFirstCell(row, column, rowSpan, colSpan);
        // actually do the merge
        q_ptr->QTableView::setSpan(row, column, rowSpan, colSpan);
        break;

    case QMessageBox::No: // first item kept. Rest stored
        firstCellRetainedRestStored(row, column, rowSpan, colSpan);
        // actually do the merge
        q_ptr->QTableView::setSpan(row, column, rowSpan, colSpan);
        break;
    case QMessageBox::Cancel:
    default:
        break;
    }

}

void QWorksheetViewPrivate::demerge(int row, int column, int /*rowSpan*/, int /*colSpan*/) {

    /*
        Convert the first cell from a merged cell to a normal cell with the same data.
    */
    Cell *cell = q_ptr->model()->cellAsCell(row, column);
    MergedCell *mCell = qobject_cast<MergedCell*>(cell);
    if (!mCell || mCell->isEmpty()) {
        cell = new Cell(mCell->row(), mCell->column(), q_ptr);
        q_ptr->model()->setCellAsCell(cell->row(), cell->column(), cell);
    } else {
        cell = new Cell(mCell->row(), mCell->column(), mCell->value(), q_ptr);
        q_ptr->model()->setCellAsCell(cell->row(), cell->column(), cell);
    }

    /*
        Restores all the other cells to their existing data, if any.
    */
    QList<Cell*> list = mCell->overwritten();
    QListIterator<Cell*> it(list);
    while (it.hasNext()) {
        cell = it.next();

        // doesn't matter if it is empty. Empty cells are discarded in setCellAsCell.
        q_ptr->model()->setCellAsCell(cell->row(), cell->column(), cell);
    }

    q_ptr->QTableView::setSpan(row, column, 1, 1);

}

MergeStatus QWorksheetViewPrivate::checkClearSpan(int row, int column, int rowSpan, int colSpan) {

    // check that the first cell is a Merged cell
    Cell *cell = q_ptr->model()->cellAsCell(row, column);
    MergedCell *mCell  = qobject_cast<MergedCell*>(cell);
    if (mCell) {
        /*
            Check that they are the same cell (ie one merge).
            If they are reverse the merge, otherwise
            merge the contents.
        */
        int count = 0;
        for (int r = row; r < row + rowSpan; r++) {
            for (int c = column; c < column + colSpan; c++) {

                cell = q_ptr->model()->cellAsCell(r, c);
                if ((qobject_cast<MergedCell*>(cell))) {
                    // some of the cells are already merged but not all
                    // or possible more than one merge exists.
                    count++;
                }
            }
        }

        if (count == 1 && (rowSpan > 1 || colSpan > 1))
            // as empty cells/mergedcells are discarded and all cells in mergeDataToFirstCell are
            // merged into first cell the others come back as empty Cell* not MergedCell*.
            return DemergePossible;
        else if (count != (rowSpan * colSpan))
            return ContainsMerge;

        return DemergePossible; // All of the cells are merged and the same merge.

    } else {

        for (int r = row; r < row + rowSpan; r++) {
            for (int c = column; c < column + colSpan; c++) {

                if (r == row && c == column) continue;
                cell = q_ptr->model()->cellAsCell(r, c);
                if (!(qobject_cast<MergedCell*>(cell) == mCell)) {
                    // some of the cells are already merged but not all
                    // or possible more than one merge exists.
                    return ContainsMerge;
                }
            }
        }

    }

    // No cells in the range are merged so a merge is possible.
    return MergePossible;
}

/*
    In OpenOffice when merge with contents moved to first cell
    other cells are emptied.
*/
void QWorksheetViewPrivate::mergeDataToFirstCell(int row, int column, int rowSpan, int colSpan) {
    MergedCell *topLeft;
    QVariant data;
    QString result;

    // merges data as strings separated by a space.
    for (int r = row; r < row + rowSpan; r++) {
        for (int c = column; c < column + colSpan; c++) {
            data = q_ptr->read(r, c);
            result += data.toString();
            result += " ";
        }
    }

    // add first mergedcell into first cell.
    // others saved empty cells and new empty merged cell stored in table.
    topLeft = new MergedCell(row, column, rowSpan, colSpan, q_ptr);
    for (int r = row; r < row + rowSpan; r++) {
        for (int c = column; c < column + colSpan; c++) {
            if (r == row && c == column) { // first cell
                topLeft->setValue(result);
                q_ptr->model()->setCellAsCell(row, column, topLeft);
            } else {
                Cell* cell = new Cell(r, c, q_ptr);
                q_ptr->model()->setCellAsCell(r, c, cell);
            }
        }
    }
}

/*
    In OpenOffice when merge with contents not moved to first cell
    other cells are saved as hidden cells. This can be partially undone,
    whatever happens to the first cell cannot, however the others can be recovered..
*/
void QWorksheetViewPrivate::firstCellRetainedRestStored(int row, int column, int rowSpan, int colSpan) {
    MergedCell *topLeft;
    Cell *cell;
    QList<Cell*> list;

    topLeft = new MergedCell(row, column, rowSpan, colSpan, q_ptr);
    for (int r = row; r < row + rowSpan; r++) {
        for (int c = column; c < column + colSpan; c++) {
            cell = q_ptr->model()->cellAsCell(r, c);
            if (r == row && c == column) {
                if (cell)
                    // set the mergedcell data to first item if it has anything in it.
                    topLeft->setValue(cell->value());
                q_ptr->model()->setCellAsCell(r, c, topLeft);
                continue;
            } else {
                if (cell)
                    list.append(cell);
                else {
                    cell = new Cell(r, c, q_ptr); // empty cells are not stored and clear old cell if it exists.
                    list.append(cell);
                }

                q_ptr->model()->setCellAsCell(r, c, cell);
            }
        }
    }
    topLeft->setOverwritten(list);
}

QVariant QWorksheetViewPrivate::read(int row, int column) {

    QModelIndex index = q_ptr->model()->index(row, column);
    if (index.isValid())
        return q_ptr->model()->data(index);

    return QVariant();
}


QVariant QWorksheetViewPrivate::read(const CellReference& reference) {
    int row = reference.row();
    int column = reference.column();
    return read(row, column);
}

void QWorksheetViewPrivate::write(int row, int column, QVariant item) {
    q_ptr->model()->setData(row, column, item, Qt::EditRole);
}

void QWorksheetViewPrivate::write(const CellReference& reference, QVariant item) {
    int row = reference.row();
    int column = reference.column();
    write(row, column, item);
}

void QWorksheetViewPrivate::write(Range& range, QVariant item) {
    for (int row = range.top(); row <= range.bottom(); row++) {
        for (int col = range.left(); col <= range.right(); col++) {
            write(row, col, item);
        }
    }
}

Format* QWorksheetViewPrivate::format(int row, int column) {
    QModelIndex index = q_ptr->model()->index(row, column);
    if (index.isValid())
        return q_ptr->model()->format(index);

    return NULL;
}

Format* QWorksheetViewPrivate::format(const CellReference& reference) {
    int row = reference.row();
    int column = reference.column();
    return format(row, column);
}

void QWorksheetViewPrivate::setFormat(int row, int column, Format *format) {
    QModelIndex index = q_ptr->model()->index(row, column);
    if (index.isValid())
        q_ptr->model()->setFormat(index, format, Qt::EditRole);

}

void QWorksheetViewPrivate::setSelectedFormat(Format *format) {
    QModelIndexList list = q_ptr->selectedIndexes();
    QListIterator<QModelIndex> it(list);
    while(it.hasNext()) {
        QModelIndex index = it.next();
        if (index.isValid())
            setFormat(index.row(), index.column(), format);
    }
}

QMap<QModelIndex, Format*> QWorksheetViewPrivate::selectedFormats() {
    QMap<QModelIndex, Format*> formats;

    QModelIndexList list = q_ptr->selectedIndexes();
    QListIterator<QModelIndex> it(list);
    while(it.hasNext()) {
        QModelIndex index = it.next();
        if (index.isValid())
            formats.insert(index, format(index.row(), index.column()));
    }
    return formats;
}

void QWorksheetViewPrivate::setFormat(const CellReference& reference, Format *format) {
    int row = reference.row();
    int column = reference.column();

    QModelIndex index = q_ptr->model()->index(row, column);
    if (index.isValid())
        q_ptr->model()->setFormat(index, format, Qt::EditRole);

}

void QWorksheetViewPrivate::setFormat(Range& range, Format *format) {
    for (int row = range.top(); row <= range.bottom(); row++) {
        for (int col = range.left(); col <= range.right(); col++) {
            setFormat(row, col, format);
        }
    }
}

void QWorksheetViewPrivate::fileNotNamedMesssage() {
    QMessageBox::warning(
        q_ptr,
        q_ptr->tr("QWorksheet Error!"),
        q_ptr->tr("The file has not been named!"),
        QMessageBox::Ok,
        QMessageBox::Ok);
}

bool QWorksheetViewPrivate::isLocked(CellReference &ref) {
    return q_ptr->model()->isLocked(ref.row(), ref.column());
}

bool QWorksheetViewPrivate::isLocked(int row, int column) {
    return q_ptr->model()->isLocked(row, column);
}

void QWorksheetViewPrivate::lockSheet() {
    q_ptr->model()->lockSheet();
}

void QWorksheetViewPrivate::unlockSheet() {
    q_ptr->model()->unlockSheet();
}

void QWorksheetViewPrivate::lockCell(int row, int column) {
    q_ptr->model()->lockCell(row, column);
}

void QWorksheetViewPrivate::lockCell(CellReference &ref) {
    q_ptr->model()->lockCell(ref.row(), ref.column());
}

void QWorksheetViewPrivate::lockRow(int &row) {
    q_ptr->model()->lockRow(row);
}

void QWorksheetViewPrivate::lockColumn(int &column) {
    q_ptr->model()->lockColumn(column);
}

void QWorksheetViewPrivate::lockRange(Range &range) {
    q_ptr->model()->lockRange(range);
}

void QWorksheetViewPrivate::unlockCell(int row, int column) {
    q_ptr->model()->unlockCell(row, column);
}

void QWorksheetViewPrivate::unlockCell(CellReference &ref) {
    q_ptr->model()->unlockCell(ref.row(), ref.column());
}

void QWorksheetViewPrivate::unlockRow(int &row) {
    q_ptr->model()->unlockRow(row);
}

void QWorksheetViewPrivate::unlockColumn(int &column) {
    q_ptr->model()->unlockColumn(column);
}

void QWorksheetViewPrivate::unlockRange(Range &range) {
    q_ptr->model()->unlockRange(range);
}


}

