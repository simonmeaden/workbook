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

#include <QtPlugin>

#include <qstd.h>

#include "qworksheetview.h"
#include "qworksheetview_p.h"
#include "worksheetmodel.h"
#include "formatdelegate.h"
#include "pluginstore.h"
#include "cell.h"


QWorksheetView::QWorksheetView(QWidget *parent) :
    QTableView(parent),
    d_ptr(new QWorksheetViewPrivate(this)) {

    init();

}

QWorksheetView::QWorksheetView(WorkbookParser *parser, PluginStore *store, QWidget *parent) :
    QTableView(parent),
    d_ptr(new QWorksheetViewPrivate(parser, store, this)) {

    init();

}

QWorksheetView::~QWorksheetView() {

}

void QWorksheetView::init() {
    setSelectionMode(QTableView::ExtendedSelection);

    QItemSelectionModel *sm = selectionModel();
    connect(sm,
            SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
            this,
            SLOT(selectionHasChanged(QItemSelection, QItemSelection)));
    connect(sm,
            SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this,
            SLOT(currentCellChanged(QModelIndex,QModelIndex)));
}

void QWorksheetView::selectionHasChanged(const QItemSelection selected, const QItemSelection deselected) {
    d_ptr->selectionHasChanged(selected, deselected);
}

void QWorksheetView::currentCellChanged(const QModelIndex current, const QModelIndex /*previous*/) {
//    d_ptr->selectionHasChanged(selected, deselected);
    cout << current.row() << " : " << current.column() << endl << flush;
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
    return d_ptr->read(row, column);
}


QVariant QWorksheetView::read(const CellReference& reference) {
    return read(reference);
}

void QWorksheetView::write(int row, int column, QVariant item) {
    d_ptr->write(row, column, item);
}

void QWorksheetView::write(const CellReference& reference, QVariant item) {
    d_ptr->write(reference, item);
}

void QWorksheetView::write(Range& range, QVariant item) {
    d_ptr->write(range, item);
}

Format* QWorksheetView::format(int row, int column) {
    return d_ptr->format(row, column);
}

Format* QWorksheetView::format(const CellReference& reference) {
    return d_ptr->format(reference);
}

void QWorksheetView::setFormat(int row, int column, Format *format) {
    d_ptr->setFormat(row, column, format);
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
