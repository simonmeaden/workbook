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

#include <QApplication>

#include "qstd.h"

#include "worksheet_p.h"
#include "cell.h"
#include "cellreference.h"
#include "range.h"
#include "worksheetmodel.h"
#include "format.h"

#include <xlsxdocument.h>
#include <xlsxworkbook.h>
#include <xlsxworksheet.h>

WorksheetPrivate::WorksheetPrivate(PluginStore *store, Worksheet *parent) :
    pPluginStore(store),
    q_ptr(parent) {

    sPath = "";
    pModel = NULL;
    bShowGrid = true;
    bSheetLocked = false;

}

WorksheetPrivate::~WorksheetPrivate() {
}

void WorksheetPrivate::setModel(WorksheetModel *model) {
    pModel = model;
}

void WorksheetPrivate::saveWorksheet() {
    if (!sPath.isEmpty()) {
        saveWorksheet(sPath);
    }
}

void WorksheetPrivate::saveWorksheet(QString filename) {
    saveWorksheet(ODS, filename);
}

void WorksheetPrivate::saveWorksheet(WorksheetType type) {

    if (!sPath.isEmpty()) {

        switch(type) {
        case ODS:
            writeOds(sPath);
            break;
        case XLS:
            writeXls(sPath);
            break;
        case XLSX:
            saveXlsx(sPath);
        default:
            saveWorksheet(type, sPath);
            break;
        }

    } else {

        QString msg("There is no existing file path. Select a path before attempting to save a file.");

        emit q_ptr->badPath(msg);

    }
}

void WorksheetPrivate::saveWorksheet(WorksheetType type, QString filename) {
    switch (type) {
    case ODS:
        writeOds(filename);
        break;
    case XLS:
        writeXls(filename);
        break;
    case XLSX:
        saveXlsx(filename);
        break;
    case NOT_A_SPREADSHEET:
        break;
    }
}

void WorksheetPrivate::writeOds(QString filename) {
    Q_UNUSED(filename)
    // TODO save ids
}

void WorksheetPrivate::writeXls(QString filename) {
    Q_UNUSED(filename)
    // TODO save xls
}

/*!
 * \brief Add the worksheet to an existing XSLX document.
 *
 * \param document - the xslx document to add the worksheet to.
 */
void WorksheetPrivate::writeXlsx(QXlsx::Worksheet *sheet) {

    QMapIterator<int, QMap<int, Cell*> > cellrowIt(mCellData);
    while (cellrowIt.hasNext()) {
        cellrowIt.next();

        // first save all the cells with associated formats
        QMapIterator<int, Cell*> cellColumnIt(cellrowIt.value());
        while (cellColumnIt.hasNext()) {
            cellColumnIt.next();

            Cell *cell = cellColumnIt.value();
            int row = cell->row() + 1;
            int column = cell->column() + 1;
            Format *f = format(row, column);

            switch (cell->type()) {
            case TextType:
                sheet->write(row, column, cell->value().toString(), f->toXlsx());
                break;
            case BooleanType:
                sheet->writeBool(row, column, cell->value().toBool(), f->toXlsx());
                break;
            case NumberType:
                // TODO NumberFormat
                sheet->writeNumeric(row, column, cell->value().toDouble(), f->toXlsx());
                break;
            case FormulaType:
                // TODO formulas.
                break;
            case ErrorType:
                // TODO error handling
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
                    sheet->writeBlank(row, column, format->toXlsx());
                }
            }
        }
    }
}

/*!
 * \brief Save the worksheet as a single page Excel XML document.
 *
 * \param filename - the file name to save to.
 */
void WorksheetPrivate::saveXlsx(QString filename) {

    QXlsx::Document doc(filename);
    writeXlsx(doc.currentWorksheet());
    doc.save();

}

QString WorksheetPrivate::sheetName() {
    return sSheetName;
}

void WorksheetPrivate::setSheetName(QString name) {
    sSheetName = name;
}

WorksheetType WorksheetPrivate::type() {
    return mType;
}

void WorksheetPrivate::setType(WorksheetType type) {
    mType = type;
}

void WorksheetPrivate::readXlsx(QXlsx::Worksheet */*sheet*/, int /*index*/) {
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

void WorksheetPrivate::readXlsx(QString filename) {

    QFile file(filename);

//    QXlsx::Document *doc = new QXlsx::Document(filename, q_ptr);

}

void WorksheetPrivate::lockCell(int row, int column) {
    Cell *c = cellAsCell(row, column);
    if (c)
        c->setLocked(true);
}

void WorksheetPrivate::lockRow(int &row) {
    mRowLocked.insert(row, true);
}

void WorksheetPrivate::lockColumn(int &column) {
    mColLocked.insert(column, true);
}

void WorksheetPrivate::lockRange(Range &range) {
    int startRow = range.top();
    int endRow = range.bottom();
    int startColumn = range.left();
    int endColumn = range.right();

    for (int row = startRow; row <= endRow; row++) {
        for (int column = startColumn; column <= endColumn; column++) {
            Cell *c = cellCreateAsNeeded(row, column);
            if (c)
                c->setLocked(true);
        }
    }
}

void WorksheetPrivate::unlockCell(int row, int column) {
    Cell *c = cellAsCell(row, column);
    if (c)
        c->setLocked(false);
}

void WorksheetPrivate::unlockRow(int &row) {
    mRowLocked.remove(row);
}

void WorksheetPrivate::unlockColumn(int &column) {
    mColLocked.remove(column);
}

void WorksheetPrivate::unlockRange(Range &range) {
    int startRow = range.top();
    int endRow = range.bottom();
    int startColumn = range.left();
    int endColumn = range.right();

    for (int row = startRow; row <= endRow; row++) {
        for (int column = startColumn; column <= endColumn; column++) {
            Cell *c = cellAsCell(row, column);
            if (c)
                c->setLocked(false);
        }
    }
}

void WorksheetPrivate::lockSheet() {
    bSheetLocked = true;
}

void WorksheetPrivate::unlockSheet() {
    bSheetLocked = false;
}

bool WorksheetPrivate::isLocked(int row, int column) {
    if (bSheetLocked) return true;

    if (mRowLocked.value(row)) return true;

    if (mColLocked.value(column)) return true;

    Cell *cell = cellAsCell(row, column);
    if (cell)
        return cell->locked();

    return false;
}

int WorksheetPrivate::maxColumn() {
    QList<int> keys = mCellData.keys();
    int max = 0, value, row;
    QListIterator<int> it(keys);
    while (it.hasNext()) {
        row = it.next();
        value = maxColumn(row);
        if (value > max) max = value;
    }
    return max;
}

int WorksheetPrivate::maxColumn(int row) {
    QMap<int, Cell*> rowData = mCellData.value(row);
    QList<int> keys = rowData.keys();
    int max = 0, value;
    QListIterator<int> it(keys);
    while (it.hasNext()) {
        value = it.next();
        if (value > max)
            max = value;
    }
    return max;
}

int WorksheetPrivate::maxRow() {
    QList<int> keys = mCellData.keys();
    int max = 0, value;
    QListIterator<int> it(keys);
    while (it.hasNext()) {
        value = it.next();
        if (value > max)
            max = value;
    }
    return max;
}

QVariant WorksheetPrivate::cell(int row, int column) {
    QMap<int, Cell*> rowData = mCellData.value(row);
    if (!rowData.isEmpty()) {
        Cell* cell = rowData.value(column);
        if (cell)
            return cell->value();
    }
    return QVariant();
}

/*
 * This is only called internally, normally when a cell has to be read but something else other
 * than it's value . If the value needs to be changed use setCell() or if something else needs to
 * be changed internally use cellCreateAsNeeded().
 */
Cell* WorksheetPrivate::cellAsCell(int row, int column) {
    QMap<int, Cell*> rowData = mCellData.value(row);
    if (!rowData.isEmpty()) {
        Cell* cell = rowData.value(column);
        if (cell)
            return cell;
    }
    return NULL;
}

/*
 * This is only called internally, normally when a cell has to be modified in another way
 * than modifying it's value. If the value needs to be changed use setCell().
 *
 * generally this means that the cell needs to be locked, or similar, so a cell needs to be
 * created if it doesn't already exist.
 */
Cell* WorksheetPrivate::cellCreateAsNeeded(int row, int column) {
    QMap<int, Cell*> rowData = mCellData.value(row);
    Cell* cell = rowData.value(column);
    if (!cell) {
        cell = new Cell(row, column, q_ptr);
        rowData.insert(column, cell);
        if (rowData.size() == 1)
            mCellData.insert(row, rowData);
    }
    return cell;
}


void WorksheetPrivate::setCell(int row, int column, QVariant data) {
    QMap<int, Cell*> rowData = mCellData.value(row);
    Cell *c = rowData.value(column);
    if (c)
        c->setValue(data);
    else
        c = new Cell(row, column, data);

    rowData.insert(column, c);
    mCellData.insert(row, rowData);
}

Format* WorksheetPrivate::rowFormat(int row) {
    return mRowFormat.value(row);
}

Format* WorksheetPrivate::columnFormat(int column) {
    return mColFormat.value(column);
}

void WorksheetPrivate::setRowFormat(int row, Format *format) {
    mRowFormat.insert(row, format);
}

void WorksheetPrivate::setColumnFormat(int column, Format *format) {
    mColFormat.insert(column, format);
}

QList<QVariant> WorksheetPrivate::rowCells(int row) {
    QList<QVariant> data;
    QMap<int, Cell*> rowData = mCellData.value(row);
    if (rowData.size() > 0) {
        QList<int> keys = rowData.keys();
        QListIterator<int> it(keys);
        while (it.hasNext()) {
            int key = it.next();
            data.append(rowData.value(key)->value());
        }
    }
    return data;
}

QList<QVariant> WorksheetPrivate::columnCells(int column) {
    QList<QVariant> data;
    QList<int> keys = mCellData.keys();
    QListIterator<int> it(keys);
    while (it.hasNext()) {
        int key = it.next();
        QMap<int, Cell*> rowData = mCellData.value(key);
        Cell* c = rowData.value(column);
        if (c->empty()) continue;
        data.append(c->value());
    }
    return data;
}

QList<QVariant> WorksheetPrivate::cells(Range *range) {
    QList<QVariant> data;
    QQuad<int, int, int, int> r = range->range();
    for (int row = r.first; row < r.first + r.fourth; row++) {
        for (int col = r.second; col < r.second + r.third; col++) {
            QVariant c = cell(row, col);
            if (c.isNull()) continue;
            data.append(c);
        }
    }
    return data;
}

Format* WorksheetPrivate::format(int row, int column) {
    QMap<int, Format*> rowData = mCellFormat.value(row);
    Format* format;

    format = rowData.value(column);
    if (format == NULL || rowData.isEmpty()) {
        // rowData doesnt exist, an empty one was supplied
        // so create a new format, but don't save it, this
        // will be done if it is modified at all.
        format = new Format(row, column, q_ptr);
        q_ptr->connect(format, SIGNAL(formatChanged(Format*)), q_ptr, SLOT(formatChanged(Format*)), Qt::UniqueConnection);
        q_ptr->connect(format, SIGNAL(leftBorderChanged(Format*)), q_ptr, SLOT(leftBorderChanged(Format*)), Qt::UniqueConnection);
        q_ptr->connect(format, SIGNAL(topBorderChanged(Format*)), q_ptr, SLOT(topBorderChanged(Format*)), Qt::UniqueConnection);
        q_ptr->connect(format, SIGNAL(rightBorderChanged(Format*)), q_ptr, SLOT(rightBorderChanged(Format*)), Qt::UniqueConnection);
        q_ptr->connect(format, SIGNAL(bottomBorderChanged(Format*)), q_ptr, SLOT(bottomBorderChanged(Format*)), Qt::UniqueConnection);
    }

    return format;
}

void WorksheetPrivate::setFormat(Format *format) {
    QMap<int, Format*> rowData = mCellFormat.value(format->row());
    rowData.insert(format->column(), format);
    mCellFormat.insert(format->row(), rowData);
}

void WorksheetPrivate::rightBorderChanged(Format *borderFormat) {
    setFormat(borderFormat);

//    Format *nextCellInLine = format(borderFormat->row(), borderFormat->column() + 1);

//    nextCellInLine->updateLeftBorder(borderFormat->rightBorder().enabled(),
//                                     borderFormat->rightBorder().color(),
//                                     borderFormat->rightBorder().style());

//    setFormat(nextCellInLine);
}

void WorksheetPrivate::leftBorderChanged(Format *borderFormat) {
    setFormat(borderFormat);

//    if (borderFormat->column() > 0) {
//        Format *nextCellInLine = format(borderFormat->row(), borderFormat->column() - 1);

//        nextCellInLine->updateRightBorder(borderFormat->leftborder().enabled(),
//                                          borderFormat->leftborder().color(),
//                                          borderFormat->leftborder().style());

//        setFormat(nextCellInLine);
//    }
}

void WorksheetPrivate::topBorderChanged(Format *borderFormat) {
    setFormat(borderFormat);

    if (borderFormat->row() > 0) {
        Format *nextCellInLine = format(borderFormat->row() - 1, borderFormat->column());

        nextCellInLine->updateBottomBorder(borderFormat->topBorder().isEnabled(),
                                           borderFormat->topBorder().color(),
                                           borderFormat->topBorder().style());

        setFormat(nextCellInLine);
    }
}

void WorksheetPrivate::bottomBorderChanged(Format *borderFormat) {
    setFormat(borderFormat);

    Format *nextCellInLine = format(borderFormat->row() + 1, borderFormat->column());

    nextCellInLine->updateTopBorder(borderFormat->bottomBorder().isEnabled(),
                                    borderFormat->bottomBorder().color(),
                                    borderFormat->bottomBorder().style());

    setFormat(nextCellInLine);
}

