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

#include <QtXlsx/xlsxworksheet.h>
#include <QtXlsx/xlsxdocument.h>

#include "worksheetmodel_p.h"
#include "worksheetmodel.h"
#include "cell.h"
#include "mergedcell.h"
#include "formulacell.h"
#include "cellreference.h"
#include "format.h"
#include "range.h"
#include "cellreference.h"

#include "workbook_global.h"

namespace QWorkbook {

WorksheetModelPrivate::WorksheetModelPrivate(WorksheetModel *q) :
    q_ptr(q) {

    mStatus.mMaxRow = INITIALROWS;
    mStatus.mMaxCol = INITIALCOLUMNS;
    bSheetLocked = false;

    pSheet->setModel(q_ptr);
    q_ptr->connect(pSheet.data(), SIGNAL(formatHasChanged(int,int)),
                   q_ptr, SLOT(formatChanged(int,int)));
    q_ptr->connect(pSheet.data(), SIGNAL(fileHasNotBeenNamedMessage()),
                   q_ptr, SIGNAL(fileHasNotBeenNamedMessage()));

}

bool WorksheetModelPrivate::setData(QModelIndex &index, const QVariant value, int role) {

    if (!index.isValid()) {
        index = q_ptr->createIndex(row, column);
    }

    switch (role) {
    case Qt::EditRole: {
        if (column > mStatus.mMaxCol)
            q_ptr->beginInsertColumns(index, mStatus.mMaxCol + 1, column);

        if (row > mStatus.mMaxRow)
            q_ptr->beginInsertRows(index, mStatus.mMaxRow + 1, row);


        if (row > mStatus.mMaxRow) {
            q_ptr->endInsertRows();
            mStatus.mMaxRow = row;
        }

        if (column > mStatus.mMaxCol) {
            q_ptr->endInsertColumns();
            mStatus.mMaxCol = column;
        }

        mCellData.insert(index, value);

        emit q_ptr->dataChanged(index, index);

        return true;
    }
    default:
        break;
    }

}

//void WorksheetModelPrivate::setWorksheet(Worksheet *sheet) {
//    pSheet.reset(sheet);
//}

WorksheetModel* WorksheetModelPrivate::clone() {

    WorksheetModel *wm = new WorksheetModel(thi);
    WorksheetModelPrivate *wmp = new WorksheetModelPrivate(wm);

    // shouldn't need to deep copy these as COW should do it if anything changes.
    // if this causes problems use detach() on the maps.
    wmp->mCellData = mCellData;
    wmp->mCellFormat = mCellFormat;
    wmp->mRowFormat = mRowFormat;
    wmp->mColFormat = mColFormat;
    wmp->mRowLocked = mRowLocked;
    wmp->mColLocked = mColLocked;
    wmp->mStatus = mStatus;
    wmp->bSheetLocked = bSheetLocked;

    return wm;
}

int WorksheetModelPrivate::maxRow() {
    return mStatus.mMaxRow;
}

int WorksheetModelPrivate::maxColumn() {
    return mStatus.mMaxCol;
}

QModelIndex WorksheetModelPrivate::getIndex(int row, int column) {
    QModelIndex index = q_ptr->index(row, column);
    if (!index.isValid())
        return q_ptr->createIndex(row, column);
    return index;
}

bool WorksheetModelPrivate::isLocked(CellReference &ref) {
    if (bSheetLocked) return true;

    return mRowLocked.value(row);

    return mColLocked.value(column);

    Cell *cell = cellAsCell(row, column);
    if (cell)
        return cell->locked();

    return false;
}

bool WorksheetModelPrivate::isLocked(int row, int column) {
    QModelIndex = getIndex(row, column);
    return sLocked(index);
}

void WorksheetModelPrivate::lockSheet() {
    pSheet->lockSheet();
    emit q_ptr->layoutChanged();
}

void WorksheetModelPrivate::unlockSheet() {
    pSheet->unlockSheet();
    emit q_ptr->layoutChanged();
}

void WorksheetModelPrivate::lockCell(QModelIndex index) {
    Cell *cell = cellAsCell(index);
    if (cell)
        cell->setLocked(true);
    emit q_ptr->dataChanged(i, i);
}

void WorksheetModelPrivate::lockCell(int row, int column) {
    QModelIndex i = getIndex(row, column);
    lockCell(i);
}

void WorksheetModelPrivate::lockCell(CellReference &ref) {
    QModelIndex i = getIndex(ref.row(), ref.column());
    lockCell(i);
}

void WorksheetModelPrivate::lockRow(int &row) {
    mRowLocked.insert(row, true);

    QModelIndex i1 = q_ptr->index(row, 0);
    QModelIndex i2 = q_ptr->index(row, mStatus.mMaxCol);
    emit q_ptr->dataChanged(i1, i2);
}

void WorksheetModelPrivate::lockColumn(int &column) {
    mColLocked.insert(column, true);

    QModelIndex i1 = q_ptr->index(0, column);
    QModelIndex i2 = q_ptr->index(mStatus.mMaxRow, column);
    emit q_ptr->dataChanged(i1, i2);
}

void WorksheetModelPrivate::lockRange(Range &range) {
    for (int tb = range.top(); i <= range.bottom(); tb++) {
        for (int lr = range.left(); rl <= range.right(); lr++) {
            QModelIndex index = q_ptr->getIndex(tb, lr);
            lockCell(index);
        }
    }

    QModelIndex i1 = q_ptr->index(range.top(), range.left());
    QModelIndex i2 = q_ptr->index(range.bottom(), range.right());
    emit q_ptr->dataChanged(i1, i2);
}

void WorksheetModelPrivate::unlockCell(QModelIndex index) {
    Cell *cell = cellAsCell(index);
    if (cell)
        cell->setLocked(false);
    emit q_ptr->dataChanged(i, i);
}

void WorksheetModelPrivate::unlockCell(int row, int column) {
    QModelIndex i = getIndex(row, column);
    unlockCell(i);
}

void WorksheetModelPrivate::unlockCell(CellReference &ref) {
    QModelIndex i = getIndex(ref.row(), ref.column());
    unlockCell(i);
}

void WorksheetModelPrivate::unlockRow(int &row) {
    mRowLocked.insert(row, false);

    QModelIndex i1 = q_ptr->index(row, 0);
    QModelIndex i2 = q_ptr->index(row, mStatus.mMaxCol);
    emit q_ptr->dataChanged(i1, i2);
}

void WorksheetModelPrivate::unlockColumn(int &column) {
    mColLocked.insert(column, false);

    QModelIndex i1 = q_ptr->index(row, 0);
    QModelIndex i2 = q_ptr->index(row, mStatus.mMaxCol);
    emit q_ptr->dataChanged(i1, i2);
}

void WorksheetModelPrivate::unlockRange(Range &range) {
    for (int tb = range.top(); i <= range.bottom(); tb++) {
        for (int lr = range.left(); rl <= range.right(); lr++) {
            QModelIndex index = q_ptr->getIndex(tb, lr);
            unlockCell(index);
        }
    }

    QModelIndex i1 = q_ptr->index(range.top(), range.left());
    QModelIndex i2 = q_ptr->index(range.bottom(), range.right());
    emit q_ptr->dataChanged(i1, i2);
}

Qt::ItemFlags WorksheetModelPrivate::flags(const QModelIndex &index) const {
    Qt::ItemFlags flags = q_ptr->QAbstractTableModel::flags(index);
    if (isLocked(index))
        flags &= ~Qt::ItemIsEditable;
    else
        flags |= Qt::ItemIsEditable;
    return flags;
}

void WorksheetModelPrivate::saveWorksheet(QString path, WorksheetType type) {
    switch (type) {
    case XLSX:
        writeXlsx(path);
        break;
    case ODS:
        writeXlsx(path);
        break;
    default:
        break;
    }
}

void WorksheetModelPrivate::writeXlsx(QString path) {
    QXlsx::Document *doc = new QXlsx::Document(path, q_ptr);
    doc->addSheet(mSheetName);
    QXlsx::Worksheet *sheet = doc->currentWorksheet();
    writeXlsx(sheet);
}

void WorksheetModelPrivate::writeXlsx(QXlsx::Worksheet *sheet) {

    QMapIterator<int, QMap<int, Cell*> > cellrowIt(mCellData);
    while (cellrowIt.hasNext()) {
        cellrowIt.next();

        // first save all the cells with associated formats
        QMapIterator<int, Cell*> cellColumnIt(cellrowIt.value());
        while (cellColumnIt.hasNext()) {
            cellColumnIt.next();

            QVariant value;
            Cell *c = cellColumnIt.value();
            int row = c->row() + 1;
            int column = c->column() + 1;
            Format *f = format(row, column);

            MergedCell *mCell = qobject_cast<MergedCell*>(c);
            FormulaCell *fCell =  qobject_cast<FormulaCell*>(c);

            if (mCell) {
                /*
                    Actually merged cells don't do anything to the data,
                    they are only used to handle the creation and removal
                    of cells that are effected by a cell merge action, so
                    I might take this out.
                */

                value = mCell->value();
                switch (value.type()) {
                case QVariant::Bool:
                    sheet->writeBool(row, column, value.toBool(), *f->toXlsx());
                    break;
                case QVariant::Int:
                case QVariant::Double:
                    // TODO NumberFormat
                    sheet->writeNumeric(row, column, value.toDouble(), *f->toXlsx());
                    break;
                case QVariant::Date:
                case QVariant::DateTime:
                    sheet->writeDateTime(row, column, value.toDateTime(), *f->toXlsx());
                    break;
                case QVariant::Time:
                    sheet->writeDateTime(row, column, value.toDateTime(), *f->toXlsx());
                    break;
                case QVariant::String:
                    sheet->write(row, column, value.toString(), *f->toXlsx());
                    break;
//                case ErrorType:
//                    // TODO error handling
//                    break;
                default:
                    break;
                }

            } else if (fCell) {

            } else {

                value = c->value();
                switch (value.type()) {
                case QVariant::Bool:
                    sheet->writeBool(row, column, value.toBool(), *f->toXlsx());
                    break;
                case QVariant::Int:
                case QVariant::Double:
                    // TODO NumberFormat
                    sheet->writeNumeric(row, column, value.toDouble(), *f->toXlsx());
                    break;
                case QVariant::Date:
                case QVariant::DateTime:
                    sheet->writeDateTime(row, column, value.toDateTime(), *f->toXlsx());
                    break;
                case QVariant::Time:
                    sheet->writeDateTime(row, column, value.toDateTime(), *f->toXlsx());
                case QVariant::String:
                    sheet->write(row, column, value.toString(), *f->toXlsx());
                    break;
                default:
                    break;
                }

            }

            // now save data less formats.
            QMapIterator<int, QMap<int, Format*> > formatRowIt(mCellFormat);
            while (formatRowIt.hasNext()) {
                formatRowIt.next();

                // now save all the formats with no associated cells.
                QMapIterator<int, Format*> formatColumnIt(formatRowIt.value());
                while (formatColumnIt.hasNext()) {
                    formatColumnIt.next();
                    Format* format = formatColumnIt.value();
                    int row = format->row();
                    int column = format->column();
                    Cell* c = cell(row, column).value<Cell*>();

                    if (c->isEmpty()) {
                        sheet->writeBlank(row, column, *format->toXlsx());
                    }
                }
            }
        }
    }
}

void WorksheetModelPrivate::readXlsx() {
    // TODO read this shit
//    QXlsx::Worksheet *sheet = qobject_cast<QXlsx::Worksheet*>(book->sheet(index));

//    QXlsx::CellRange sheetRange = sheet->dimension();
//    for (int row = sheetRange.firstRow();
//            row <= sheetRange.lastRow();
//            row++) {

//        for (int col = sheetRange.firstColumn();
//                col <= sheetRange.lastColumn();
//                col++) {

//            QXlsx::Cell *cell = sheet->cellAt(row, col);
//            if (cell) {
//                QVariant value = cell->value();

//                Format *format = new Format(row - 1, col - 1, q_ptr);
//                format->fromXlsx(cell->format());

//                setCell(row -1, col -1, value);
//                setFormat(row -1, col - 1, format);
//            }
//        }
//    }

}

void WorksheetModelPrivate::readOds() {
    // TODO read this shit
}

void WorksheetModelPrivate::writeOds(QString path) {
    // TODO write this shit
}

void WorksheetModelPrivate::writeOds(ods::Sheet *sheet) {
    // TODO write this shit
}


void WorksheetModelPrivate::formatChanged(QModelIndex index) {
    emit q_ptr->dataChanged(index, index);
}

int WorksheetModelPrivate::rowCount() const {
    return mStatus.mMaxRow;
}

int WorksheetModelPrivate::columnCount() const {
    return mStatus.mMaxCol;
}

QVariant WorksheetModelPrivate::data(const QModelIndex &index, int role) const {
    switch (role) {
    case Qt::EditRole:
    case Qt::DisplayRole: {
        QVariant cellValue = mCellData.value(index)->value();
        return cellValue;
    }
    default:
        break;
    }
    return QVariant();
}

Format* WorksheetModelPrivate::format(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        Format *format = mCellFormat.value(index);
        // you can have formats set for cells that do not have data in them yet. This signal saves formats
        // when they have been modified.
        return format;
    }
    return Q_NULLPTR;
}

void WorksheetModelPrivate::formatHasChanged(Format* format) {
    pSheet->setFormat(format);
}

void WorksheetModelPrivate::setFormat(const QModelIndex &index, Format *format, int role)  {
    if (index.isValid()) {
        switch (role) {
        case Qt::EditRole: {
            int row = index.row();
            int column = index.column();

            if (column > mStatus.mMaxCol)
                q_ptr->beginInsertColumns(index, mStatus.mMaxCol + 1, column);

            if (row > mStatus.mMaxRow)
                q_ptr->beginInsertRows(index, mStatus.mMaxRow + 1, row);

            mCellFormat.insert(index, format);

            emit q_ptr->dataChanged(index, index);

            if (row > mStatus.mMaxRow) {
                q_ptr->endInsertRows();
                mStatus.mMaxRow = row;
            }

            if (column > mStatus.mMaxCol) {
                q_ptr->endInsertColumns();
                mStatus.mMaxCol = column;
            }
        }
        }
    }
}

void WorksheetModelPrivate::setFormat(int row, int column, Format *format, int role) {
    QModelIndex index = getIndex(row, column);
    setFormat(index, format, role);
}

QVariant WorksheetModelPrivate::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal)
            return Reference::columnToString(section);
        else if (orientation == Qt::Vertical)
            return QString::number(section + 1);
    }

    return QVariant();
}

void WorksheetModelPrivate::setSheetName(QString name) {
    mSheetName = name;
}

QString WorksheetModelPrivate::sheetName() {
    return mSheetName;
}

/*
    This is only called internally, normally when a cell has to be read but something else other
    than it's value . If the value needs to be changed use setCell() or if something else needs to
    be changed internally use cellCreateAsNeeded().
*/
Cell* WorksheetModelPrivate::cellAsCell(int row, int column) {
    QModelIndex index = getIndex(row, column);
    Cell* cell = mCellData.value(index);
    if (cell)
        return cell;
    return Q_NULLPTR;
}

/*
    This is only called internally, normally when a cell has to be written to by something else other
    than it's value . If the value needs to be changed use setCell() or if something else needs to
    be changed internally use cellCreateAsNeeded().
*/
void WorksheetModelPrivate::setCellAsCell(int row, int column, Cell *cell) {
    QModelIndex index = getIndex(row, column);

    if (cell->isEmpty()) {
        if (mCellData.value(index))
            mCellData.remove(index);
    } else
        mCellData.insert(index, cell);

}

}

