/*
    This Workbook library is © Simon Meaden 2015. It is licensed under the LGPL V3 license.

    This Workbook library dynamically links to unmodified Nokia Qt5 Library. The Qt5
    Library is © 2011 Nokia Corporation and/or its subsidiary(-ies), and is licensed
    under the GNU Lesser General Public License version 2.1 with Nokia Qt LGPL exception
    version 1.1.

    Qt5 library is free software; you can redistribute it and/or modify it under the
    terms of the GNU Lesser General Public License, version 2.1, as published by the
    Free Software Foundation.

    Qt5 library is provided “AS IS”, without WARRANTIES OR CONDITIONS OF ANY KIND, EITHER
    EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY WARRANTIES OR CONDITIONS OF
    TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.

    As an additional permission to the GNU Lesser General Public License version 3.0, the
    object code form of a “work that uses the Library” may incorporate material from a
    header file that is part of the Library. You may distribute such object code under
    terms of your choice, provided that: (i) the header files of the Library have not
    been modified; and (ii) the incorporated material is limited to numerical parameters,
    data structure layouts, accessors, macros, inline functions and templates; and (iii)
    you comply with the terms of Section 6 of the GNU Lesser General Public License version 3.0.

    Moreover, you may apply this exception to a modified version of the Library, provided
    that such modification does not involve copying material from the Library into the
    modified Library’s header files unless such material is limited to (i) numerical
    parameters; (ii) data structure layouts; (iii) accessors; and (iv) small macros,
    templates and inline functions of five lines or less in length.

    Furthermore, you are not required to apply this additional permission to a modified
    version of the Library.

    You should have received a copy of the GNU Lesser General Public License along
    with this package; if not, write to the Free Software Foundation, Inc., 51 Franklin
    Street, Fifth Floor, Boston, MA 02110-1301 USA

    The source code for Qt 5.4.X SDK is available from Nokia here:
    http://get.qt.nokia.com/qt/source/qt-everywhere-opensource-src-4.7.X.zip.

    It is also available on request from Simon Meaden info@smelecomp.co.uk.
*/
#include "qworksheetview_p.h"
#include "qworksheetview.h"
#include "formatdelegate.h"
#include "worksheetmodel.h"

#include "pluginstore.h"
#include "workbookparser.h"

QWorksheetViewPrivate::QWorksheetViewPrivate(QWorksheetView *parent) :
    q_ptr(parent) {

    pPluginStore = new PluginStore(q_ptr);
    pParser = new WorkbookParser(pPluginStore, q_ptr);

    q_ptr->setModel(new WorksheetModel(pPluginStore, q_ptr));
    q_ptr->setItemDelegate(new FormatDelegate(q_ptr));

    contiguous = true;
}

QWorksheetViewPrivate::QWorksheetViewPrivate(WorkbookParser *parser, PluginStore *store, QWorksheetView *parent) :
    pParser(parser),
    pPluginStore(store),
    q_ptr(parent) {

    q_ptr->setModel(new WorksheetModel(pPluginStore, q_ptr));
    q_ptr->setItemDelegate(new FormatDelegate(q_ptr));

    contiguous = true;
}

QWorksheetViewPrivate::~QWorksheetViewPrivate() {

}

void QWorksheetViewPrivate::selectionHasChanged(QItemSelection selected, QItemSelection /*deselected*/) {
    QModelIndex index;

    QModelIndexList items = selected.indexes();
    int count = 0, minRow = 0, maxRow = 0, minCol = 0, maxCol = 0, row, col;

    // if the total rows * total columns = total item count then
    // the range is contigouous.
    foreach (index, items) {
        row = index.row();
        col = index.column();
        count++;

        minRow = (row < minRow ? row : minRow);
        maxRow = (row > maxRow ? row : maxRow);
        minCol = (col < minCol ? col : minCol);
        maxCol = (col > maxCol ? col : maxCol);
    }

    Q_Q(QWorksheetView);
    if (count == 1) { // single cell selected
        Cell *cell = q->model()->cellAsCell(index.row(), index.column());
        emit q->cellSelected(cell);
        emit q->cellsChanged(CellReference::cellToString(index.row(), index.column()));
    } else {

        int rows = maxRow - minRow + 1;
        int cols = maxCol - minCol + 1;
        int cells = rows * cols;

        if (cells > count)
            contiguous = false;
        else
            contiguous = true;

        if (contiguous) {
            Range range(minRow, minCol, maxRow, maxCol);
            emit q->rangeSelected(range);
            emit q->cellsChanged(Range::rangeToString(minRow, minCol, maxRow, maxCol));
        } else {
            emit q->nonContiguousRangeSelected();
            emit q->cellsChanged("");
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
