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

#include <qstd.h>

#include "qworksheetview.h"
#include "qworksheetview_p.h"
#include "worksheetmodel.h"
#include "formatdelegate.h"
#include "pluginstore.h"
#include "workbookparser.h"
#include "cell.h"


QWorksheetView::QWorksheetView(QWidget *parent) :
    QTableView(parent),
    d_ptr(new QWorksheetViewPrivate(this)) {

}

QWorksheetView::QWorksheetView(WorkbookParser *parser, PluginStore *store, QWidget *parent) :
    QTableView(parent),
    pPluginStore(store),
    d_ptr(new QWorksheetViewPrivate(parser, store, this)) {

}

QWorksheetView::~QWorksheetView() {

}

void QWorksheetView::setSheetName(QString name) {
    d_ptr->setSheetName(name);
}

QString QWorksheetView::sheetName() {
    return d_ptr->sheetName();
}

Worksheet* QWorksheetView::worksheet() {
    return d_ptr->worksheet();
}

bool QWorksheetView::eventFilter(QObject *obj, QEvent *event) {
    return d_ptr->eventFilter(obj, event);
}

void QWorksheetView::selectionHasChanged(const QItemSelection selected, const QItemSelection deselected) {
    d_ptr->selectionHasChanged(selected, deselected);
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

void QWorksheetView::setSelectionMerge(bool merge) {
    d_ptr->setSelectionMerge(merge);
}

void QWorksheetView::setSpan(int row, int column, int rowSpan, int colSpan) {
    d_ptr->setSpan(row, column, rowSpan, colSpan);
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
