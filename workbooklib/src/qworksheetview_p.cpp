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

#include "pluginstore.h"
#include "workbookparser.h"
#include "cell.h"
#include "mergedcell.h"
#include "qstd.h"

QWorksheetViewPrivate::QWorksheetViewPrivate(QWorksheetView *parent) :
    q_ptr(parent) {

    pPluginStore = new PluginStore(q_ptr);
    pParser = new WorkbookParser(pPluginStore, q_ptr);

    init();

}

QWorksheetViewPrivate::QWorksheetViewPrivate(WorkbookParser *parser, PluginStore *store, QWorksheetView *parent) :
    pParser(parser),
    pPluginStore(store),
    q_ptr(parent) {

    init();

}

QWorksheetViewPrivate::~QWorksheetViewPrivate() {

}

void QWorksheetViewPrivate::init() {

    pSheet = new Worksheet(pPluginStore, q_ptr);
    q_ptr->setModel(new WorksheetModel(pSheet, pPluginStore, q_ptr));
    q_ptr->setItemDelegate(new FormatDelegate(q_ptr));

    bContiguous = true;

    q_ptr->setSelectionMode(QTableView::ExtendedSelection);

    QItemSelectionModel *sm = q_ptr->selectionModel();
    q_ptr->connect(sm,
                   SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
                   q_ptr,
                   SLOT(selectionHasChanged(QItemSelection, QItemSelection)));

    // catches all events, and passes on whatever it doesn't want
    q_ptr->installEventFilter(q_ptr);

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

Worksheet* QWorksheetViewPrivate::worksheet() {
    return pSheet;
}

void QWorksheetViewPrivate::setSheetName(QString name) {
    pSheet->setSheetName(name);
}

QString QWorksheetViewPrivate::sheetName() {
    return pSheet->sheetName();
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

    cout << (bContiguous ? "contiguous" : "non-contiguous") << endl << flush;

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
            cout << font.family() << " : " << font.pointSize() << endl << flush;
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
void QWorksheetViewPrivate::setSelectionMerge(bool merge) {
    if (bContiguous) {
        int row = mFormatStatus.mMinRow;
        int col = mFormatStatus.mMinCol;
        int rowSpan = mFormatStatus.mMaxRow - mFormatStatus.mMinRow + 1;
        int colSpan = mFormatStatus.mMaxCol - mFormatStatus.mMinCol + 1;
        if (merge) {
            setSpan(row, col, rowSpan, colSpan);
            q_ptr->QTableView::setSpan(row, col, rowSpan, colSpan);
        } else {
            checkClearSpan(row, col, rowSpan, colSpan);
            q_ptr->QTableView::setSpan(row, col, rowSpan, colSpan);
        }
    }
}

void QWorksheetViewPrivate::setSpan(int row, int column, int rowSpan, int colSpan) {

    QWorksheetViewPrivate::MergeStatus status = checkClearSpan(row, column, rowSpan, colSpan);

    switch (status) {
    case MergePossible: {
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

        break;
    }
    case DemergePossible: {

        /*
            Convert the first cell from a merged cell to a normal cell with the same data.
        */
        Cell *cell = q_ptr->model()->cellAsCell(row, column);
        MergedCell *mCell = qobject_cast<MergedCell*>(cell);
        if (!mCell || mCell->isEmpty()) {
            QModelIndex index = q_ptr->model()->index(row, column);
            q_ptr->model()->setData(index, QVariant(), Qt::EditRole);
        } else {
            cell = new Cell(mCell->row(), mCell->column(), mCell->value(), q_ptr);
            q_ptr->model()->setCellAsCell(cell->row(), cell->column(), cell);
        }

        /*
            Restores all the other cells to their existing data, if any.
        */
        QListIterator<Cell*> it(mCell->overwritten());
        while (it.hasNext()) {
            cell = it.next();

            if (cell->isEmpty()) {
                // null qvariant removes this cell - saves storage space
                QModelIndex index = q_ptr->model()->index(row, column);
                q_ptr->model()->setData(index, QVariant(), Qt::EditRole);
                continue;
            }
            q_ptr->model()->setCellAsCell(cell->row(), cell->column(), cell);
        }

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

QWorksheetViewPrivate::MergeStatus QWorksheetViewPrivate::checkClearSpan(int row, int column, int rowSpan, int colSpan) {

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

        if (count != (rowSpan * colSpan))
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
    QList<Cell*> list;

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
    topLeft = new MergedCell(row, column, q_ptr);
    for (int r = row; r < row + rowSpan; r++) {
        for (int c = column; c < column + colSpan; c++) {
            if (r == row && c == column) {
                topLeft->setValue(result);
                q_ptr->model()->setCellAsCell(row, column, topLeft);
            } else {
                list.append(new Cell(r, c, q_ptr));
                q_ptr->model()->setCellAsCell(r, c, new MergedCell(r, c, q_ptr));
            }
        }
    }
    topLeft->setOverwritten(list);
}

/*
    In OpenOffice when merge with contents not moved to first cell
    other cells are saved as hidden cells. This can be partially undone,
    whatever happens to the first cell cannot, however the others can be recovered..
*/
void QWorksheetViewPrivate::firstCellRetainedRestStored(int row, int column, int rowSpan, int colSpan) {
    MergedCell *topLeft;
    Cell *cell;
    QList<Cell*> cells;

    topLeft = new MergedCell(row, column, q_ptr);
    for (int r = row; r < row + rowSpan; r++) {
        for (int c = column; c < column + colSpan; c++) {
            cell = q_ptr->model()->cellAsCell(r, c);
            if (r == row && c == column) {
                // set the mergedcell data to first item.
                topLeft->setValue(cell->value());
                q_ptr->model()->setCellAsCell(r, c, topLeft);
                continue;
            } else {
                if (!cell) {
                    cells.append(cell);
                    q_ptr->model()->setCellAsCell(r, c, new MergedCell(r, c, cell->value(), q_ptr));
                } else {
                    cells.append(new Cell(r, c, q_ptr));
                    q_ptr->model()->setCellAsCell(r, c, new MergedCell(r, c, q_ptr));
                }
            }
        }
    }
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
    QModelIndex index = q_ptr->model()->index(row, column);
    if (index.isValid())
        q_ptr->model()->setData(index, item, Qt::EditRole);
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
