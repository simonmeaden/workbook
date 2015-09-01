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

#include "qworkbookview.h"
#include "qworkbookview_p.h"
#include "toolbar/qworkbooktoolbar.h"
#include "workbook.h"
#include "worksheet.h"
#include "qworksheetview.h"
#include "workbookparser.h"
#include "cell.h"

//WorkbookInsertSheetDialog::WorkbookInsertSheetDialog(QWidget *parent) :
//    QWidget(parent),
//    d_ptr(new WorkbookInsertSheetDialogPrivate(this)) {

//}

//WorkbookInsertSheetDialog::~WorkbookInsertSheetDialog() {

//}

QWorkbookView::QWorkbookView(QWidget *parent) :
    QTabWidget(parent),
    d_ptr(new QWorkbookViewPrivate(this)) {

    pTabBar = tabBar();
    pTabBar->setContextMenuPolicy(Qt::CustomContextMenu);

    pToolBar = NULL;

    setContentsMargins(0, 0, 0, 0);
    setTabShape(QTabWidget::Triangular);
    setTabPosition(QTabWidget::South);

    createActions();

    connect(pTabBar, SIGNAL(customContextMenuRequested(const QPoint &)),
            SLOT(showContextMenu(const QPoint &)));
}

QWorkbookView::~QWorkbookView() {

}

QWorkbookToolBar* QWorkbookView::toolBar() {
    if (!pToolBar) {
        pToolBar = new QWorkbookToolBar("workbook", this);
        connect(pToolBar, SIGNAL(alignmentChanged(Qt::Alignment)),
                this, SLOT(alignmentHasChanged(Qt::Alignment)));
        connect(pToolBar, SIGNAL(boldChanged(bool)), this, SLOT(setBold(bool)));
        connect(pToolBar, SIGNAL(italicChanged(bool)), this, SLOT(setItalic(bool)));
        connect(pToolBar, SIGNAL(underlineChanged(bool)), this, SLOT(setUnderline(bool)));
        connect(pToolBar, SIGNAL(indentCells()), this, SLOT(indentCells()));
        connect(pToolBar, SIGNAL(undentCells()), this, SLOT(undentCells()));
    }
    return pToolBar;
}

QString QWorkbookView::title() {
    return d_ptr->title();
}

void QWorkbookView::setTitle(QString title) {
    d_ptr->setTitle(title);
}

QString QWorkbookView::subject() {
    return d_ptr->subject();
}

void QWorkbookView::setSubject(QString subject) {
    d_ptr->setSubject(subject);
}

QString QWorkbookView::description() {
    return d_ptr->description();
}

void QWorkbookView::setDescription(QString description) {
    d_ptr->setDescription(description);
}

QString QWorkbookView::keywords() {
    return d_ptr->keywords();
}

void QWorkbookView::setKeywords(QString keywords) {
    d_ptr->setKeywords(keywords);
}

QString QWorkbookView::comments() {
    return d_ptr->comments();
}

void QWorkbookView::setComments(QString comments) {
    d_ptr->setComments(comments);
}

QString QWorkbookView::category() {
    return d_ptr->category();
}

void QWorkbookView::setCategory(QString category) {
    d_ptr->setCategory(category);
}

QString QWorkbookView::creator() {
    return d_ptr->creator();
}

void QWorkbookView::setCreator(QString creator) {
    d_ptr->setCreator(creator);
}

QString QWorkbookView::company() {
    return d_ptr->company();
}

void QWorkbookView::setCompany(QString creator) {
    d_ptr->setCompany(creator);
}

QDateTime QWorkbookView::created() {
    return d_ptr->created();
}

void QWorkbookView::setCreated(QDateTime created) {
    d_ptr->setCreated(created);
}

bool QWorkbookView::showGrid() {
    return d_ptr->showGrid();
}

bool QWorkbookView::showGrid(int index) {
    return d_ptr->showGrid(index);
}

bool QWorkbookView::showGrid(QString name) {
    return d_ptr->showGrid(name);
}

void QWorkbookView::setShowGrid(bool showGrid) {
    d_ptr->setShowGrid(showGrid);
}

void QWorkbookView::setShowGrid(int index, bool showGrid) {
    d_ptr->setShowGrid(index, showGrid);
}

void QWorkbookView::setShowGrid(QString name, bool showGrid) {
    d_ptr->setShowGrid(name, showGrid);
}

void QWorkbookView::alignmentHasChanged(Qt::Alignment alignment) {
    d_ptr->alignmentHasChanged(alignment);
}

void QWorkbookView::setBold(bool value) {
    d_ptr->setBold(value);
}

void QWorkbookView::setItalic(bool value) {
    d_ptr->setItalic(value);
}

void QWorkbookView::setUnderline(bool value) {
    d_ptr->setUnderline(value);
}

void QWorkbookView::indentCells() {
    d_ptr->indentCells();
}

void QWorkbookView::undentCells() {
    d_ptr->undentCells();
}

void QWorkbookView::lockCell(int row, int column) {
    d_ptr->lockCell(row, column);
}

void QWorkbookView::lockCell(CellReference& reference) {
    d_ptr->lockCell(reference.row(), reference.column());
}

void QWorkbookView::lockRow(int &row) {
    d_ptr->lockRow(row);
}

void QWorkbookView::lockColumn(int &column) {
    d_ptr->lockColumn(column);
}

void QWorkbookView::lockRange(Range &range) {
    d_ptr->lockRange(range);
}

void QWorkbookView::lockSheet() {
    d_ptr->lockSheet();
}

void QWorkbookView::unlockCell(int row, int column) {
    d_ptr->unlockCell(row, column);
}

void QWorkbookView::unlockCell(CellReference& reference) {
    d_ptr->unlockCell(reference.row(), reference.column());
}

void QWorkbookView::unlockRow(int &row) {
    d_ptr->unlockRow(row);
}

void QWorkbookView::unlockColumn(int &column) {
    d_ptr->unlockColumn(column);
}

void QWorkbookView::unlockRange(Range &range) {
    d_ptr->unlockRange(range);
}

void QWorkbookView::unlockSheet() {
    d_ptr->unlockSheet();
}

void QWorkbookView::lockCell(int index, int row, int column) {
    d_ptr->lockCell(index, row, column);
}

void QWorkbookView::lockCell(int index, CellReference& reference) {
    d_ptr->lockCell(index, reference.row(), reference.column());
}

void QWorkbookView::lockRow(int index, int &row) {
    d_ptr->lockRow(index, row);
}

void QWorkbookView::lockColumn(int index, int &column) {
    d_ptr->lockColumn(index, column);
}

void QWorkbookView::lockRange(int index, Range &range) {
    d_ptr->lockRange(index, range);
}

void QWorkbookView::lockSheet(int index) {
    d_ptr->lockSheet(index);
}

void QWorkbookView::unlockCell(int index, int row, int column) {
    d_ptr->unlockCell(index, row, column);
}

void QWorkbookView::unlockCell(int index, CellReference& reference) {
    d_ptr->unlockCell(index, reference.row(), reference.column());
}

void QWorkbookView::unlockRow(int index, int &row) {
    d_ptr->unlockRow(index, row);
}

void QWorkbookView::unlockColumn(int index, int &column) {
    d_ptr->unlockColumn(index, column);
}

void QWorkbookView::unlockRange(int index, Range &range) {
    d_ptr->unlockRange(index, range);
}

void QWorkbookView::unlockSheet(int index) {
    d_ptr->unlockSheet(index);
}

void QWorkbookView::lockCell(QString name, int row, int column) {
    d_ptr->lockCell(name, row, column);
}

void QWorkbookView::lockCell(QString name, CellReference& reference) {
    d_ptr->lockCell(name, reference.row(), reference.column());
}

void QWorkbookView::lockRow(QString name, int &row) {
    d_ptr->lockRow(name, row);
}

void QWorkbookView::lockColumn(QString name, int &column) {
    d_ptr->lockColumn(name, column);
}

void QWorkbookView::lockRange(QString name, Range &range) {
    d_ptr->lockRange(name, range);
}

void QWorkbookView::lockSheet(QString name) {
    d_ptr->lockSheet(name);
}

void QWorkbookView::unlockCell(QString name, int row, int column) {
    d_ptr->unlockCell(name, row, column);
}

void QWorkbookView::unlockCell(QString name, CellReference& reference) {
    d_ptr->unlockCell(name, reference.row(), reference.column());
}

void QWorkbookView::unlockRow(QString name, int &row) {
    d_ptr->unlockRow(name, row);
}

void QWorkbookView::unlockColumn(QString name, int &column) {
    d_ptr->unlockColumn(name, column);
}

void QWorkbookView::unlockRange(QString name, Range &range) {
    d_ptr->unlockRange(name, range);
}

void QWorkbookView::unlockSheet(QString name) {
    d_ptr->unlockSheet(name);
}

QVariant QWorkbookView::read(int row, int column) {
    return d_ptr->read(row, column);
}

QVariant QWorkbookView::read(const CellReference &reference) {
    return d_ptr->read(reference.row(), reference.column());
}

QVariant QWorkbookView::read(int index, const CellReference &reference) {
    return d_ptr->read(index, reference.row(), reference.column());
}

QVariant QWorkbookView::read(int index, int row, int column) {
    return d_ptr->read(index, row, column);
}

QVariant QWorkbookView::read(QString name, const CellReference &reference) {
    return d_ptr->read(name, reference.row(), reference.column());
}

QVariant QWorkbookView::read(QString name, int row, int column) {
    return d_ptr->read(name, row, column);
}

void QWorkbookView::write(Range &range, QVariant item) {
    for (int row = range.top(); row <= range.bottom(); row++) {
        for (int col = range.left(); col <= range.right(); col++) {
            d_ptr->write(row, col, item);
        }
    }
}

void QWorkbookView::write(int row, int column, QVariant item) {
    d_ptr->write(row, column, item);
}

void QWorkbookView::write(CellReference& reference, QVariant item) {
    d_ptr->write(reference.row(), reference.column(), item);
}

void QWorkbookView::write(int index, CellReference &reference, QVariant item) {
    d_ptr->write(index, reference.row(), reference.column(), item);
}

void QWorkbookView::write(int index, Range &range, QVariant item) {
    for (int row = range.top(); row <= range.bottom(); row++) {
        for (int col = range.left(); col <= range.right(); col++) {
            d_ptr->write(index, row, col, item);
        }
    }
}

void QWorkbookView::write(int index, int row, int column, QVariant item) {
    d_ptr->write(index, row, column, item);
}

void QWorkbookView::write(QString name, CellReference &reference, QVariant item) {
    d_ptr->write(name, reference.row(), reference.column(), item);
}

void QWorkbookView::write(QString name, Range &range, QVariant item) {
    for (int row = range.top(); row <= range.bottom(); row++) {
        for (int col = range.left(); col <= range.right(); col++) {
            d_ptr->write(name, row, col, item);
        }
    }
}

void QWorkbookView::write(QString name, int row, int column, QVariant item) {
    d_ptr->write(name, row, column, item);
}

void QWorkbookView::writeImage(int row, int column, QString path) {
    d_ptr->writeImage(row, column, path);
}

void QWorkbookView::writeImage(CellReference& reference, QString path) {
    d_ptr->writeImage(reference.row(), reference.column(), path);
}

void QWorkbookView::writeImage(int index, CellReference &reference, QString path) {
    d_ptr->writeImage(index, reference.row(), reference.column(), path);
}

void QWorkbookView::writeImage(int index, int row, int column, QString path) {
    d_ptr->writeImage(index, row, column, path);
}

void QWorkbookView::writeImage(QString name, CellReference &reference, QString path) {
    d_ptr->writeImage(name, reference.row(), reference.column(), path);
}

void QWorkbookView::writeImage(QString name, int row, int column, QString path) {
    d_ptr->writeImage(name, row, column, path);
}

void QWorkbookView::writeImage(int row, int column, QImage image) {
    d_ptr->writeImage(row, column, image);
}

void QWorkbookView::writeImage(CellReference& reference, QImage image) {
    d_ptr->writeImage(reference.row(), reference.column(), image);
}

void QWorkbookView::writeImage(int index, CellReference &reference, QImage image) {
    d_ptr->writeImage(index, reference.row(), reference.column(), image);
}

void QWorkbookView::writeImage(int index, int row, int column, QImage image) {
    d_ptr->writeImage(index, row, column, image);
}

void QWorkbookView::writeImage(QString name, CellReference &reference, QImage image) {
    d_ptr->writeImage(name, reference.row(), reference.column(), image);
}

void QWorkbookView::writeImage(QString name, int row, int column, QImage image) {
    d_ptr->writeImage(name, row, column, image);
}

Format* QWorkbookView::format(int row, int column) {
    return d_ptr->format(row, column);
}

Format* QWorkbookView::format(const CellReference &reference) {
    return d_ptr->format(reference.row(), reference.column());
}

Format* QWorkbookView::format(int index, int row, int column) {
    return d_ptr->format(index, row, column);
}

Format* QWorkbookView::format(int index, const CellReference &reference) {
    return d_ptr->format(index, reference.row(), reference.column());
}

Format* QWorkbookView::format(QString name, const CellReference &reference) {
    return d_ptr->format(name, reference.row(), reference.column());
}

Format* QWorkbookView::format(QString name, int row, int column) {
    return d_ptr->format(name, row, column);
}

void QWorkbookView::setFormat(const CellReference &reference, Format* format) {
    d_ptr->setFormat(reference.row(), reference.column(), format);
}

void QWorkbookView::setFormat(Range &range, Format* format) {
    for (int row = range.top(); row <= range.bottom(); row++) {
        for (int col = range.left(); col <= range.right(); col++) {
            d_ptr->setFormat(row, col, format);
        }
    }
}

void QWorkbookView::setFormat(int row, int column, Format* format) {
    d_ptr->setFormat(row, column, format);
}

void QWorkbookView::setFormat(int index, const CellReference &reference, Format* format) {
    d_ptr->setFormat(index, reference.row(), reference.column(), format);
}

void QWorkbookView::setFormat(int index, Range &range, Format* format) {
    for (int row = range.top(); row <= range.bottom(); row++) {
        for (int col = range.left(); col <= range.right(); col++) {
            d_ptr->setFormat(index, row, col, format);
        }
    }
}

void QWorkbookView::setFormat(int index, int row, int column, Format* format) {
    d_ptr->setFormat(index, row, column, format);
}

void QWorkbookView::setFormat(QString name, const CellReference &reference, Format* format) {
    d_ptr->setFormat(name, reference.row(), reference.column(), format);
}

void QWorkbookView::setFormat(QString name, Range &range, Format* format) {
    for (int row = range.top(); row <= range.bottom(); row++) {
        for (int col = range.left(); col <= range.right(); col++) {
            d_ptr->setFormat(name, row, col, format);
        }
    }
}

void QWorkbookView::setFormat(QString name, int row, int column, Format* format) {
    d_ptr->setFormat(name, row, column, format);
}

void QWorkbookView::setSelectedFormat(Format *format) {
    d_ptr->setSelectedFormat(format);
}

void QWorkbookView::setSelectedFormat(int index, Format *format) {
    d_ptr->setSelectedFormat(index, format);
}

void QWorkbookView::setSelectedFormat(QString name, Format *format) {
    d_ptr->setSelectedFormat(name, format);
}

QMap<QModelIndex, Format*> QWorkbookView::selectedFormats() {
    return d_ptr->selectedFormats();
}

QMap<QModelIndex, Format*> QWorkbookView::selectedFormats(int index) {
    return d_ptr->selectedFormats(index);
}

QMap<QModelIndex, Format*> QWorkbookView::selectedFormats(QString name) {
    return d_ptr->selectedFormats(name);
}

void QWorkbookView::createActions() {
    d_ptr->createActions();
}

void QWorkbookView::insertSheet() {
    d_ptr->insertSheet();
}

void QWorkbookView::renameSheet() {
    d_ptr->renameSheet();
}

void QWorkbookView::moveCopySheet() {
    d_ptr->moveCopySheet();
}

void QWorkbookView::protectSheet() {
    d_ptr->protectSheet();
}

void QWorkbookView::tabColor() {
    d_ptr->tabColor();
}

void QWorkbookView::showContextMenu(const QPoint &point) {
    d_ptr->showContextMenu(point);
}

void QWorkbookView::saveWorkbook(QString filename) {
    d_ptr->saveWorkbook(filename);
}

void QWorkbookView::saveWorkbook(QString filename, WorksheetType type) {
    d_ptr->saveWorkbook(filename, type);
}

void QWorkbookView::setWorkbook(Workbook *book) {
    d_ptr->setWorkbook(book);
}

int QWorkbookView::indexOf(Worksheet *sheet) {
    return d_ptr->indexOf(sheet);
}

QWorksheetView* QWorkbookView::currentWorksheetView() {
    return d_ptr->currentWorksheetView();
}

Worksheet* QWorkbookView::currentWorksheet() {
    return d_ptr->currentWorksheet();
}

void QWorkbookView::setCurrentWorksheet(int index) {
    d_ptr->setCurrentWorksheet(index);
}

void QWorkbookView::setCurrentWorksheet(QString name) {
    d_ptr->setCurrentWorksheet(name);
}

QWorksheetView* QWorkbookView::addWorksheet() {
    return d_ptr->addWorksheet();
}

QWorksheetView *QWorkbookView::addWorksheet(QString name) {
    return d_ptr->addWorksheet(name);
}

int QWorkbookView::addTab(QWidget *widget, const QString &label) {
    // just disables function - moves it to private.
    return QTabWidget::addTab(widget, label);
}

int QWorkbookView::addTab(QWidget *widget, const QIcon &icon, const QString &label) {
    // just disables function - moves it to private.
    return QTabWidget::addTab(widget, icon, label);
}

QWorksheetView *QWorkbookView::insertWorksheet(int index) {
    return d_ptr->insertWorksheet(index);
}

QWorksheetView *QWorkbookView::insertWorksheet(int index, QString name) {
    return d_ptr->insertWorksheet(index, name);
}

int QWorkbookView::insertTab(int index, QWidget *widget, const QString & label) {
    // just disables function - moves it to private.
    return QTabWidget::insertTab(index, widget, label);
}

int QWorkbookView::insertTab(int index, QWidget *widget, const QIcon &icon, const QString &label) {
    // just disables function - moves it to private.
    return QTabWidget::insertTab(index, widget, icon, label);
}

void QWorkbookView::removeWorksheet(int index) {
    d_ptr->removeWorksheet(index);
}

void QWorkbookView::removeWorksheet(Worksheet *sheet) {
    d_ptr->removeWorksheet(sheet);
}

void QWorkbookView::removeWorksheet(QString name) {
    d_ptr->removeWorksheet(name);
}

void QWorkbookView::removeTab(int index) {
    // just disables function - moves it to private.
    QTabWidget::removeTab(index);
}

void QWorkbookView::renameSheet(QString oldname, QString newname) {
    d_ptr->renameSheet(oldname, newname);
}

void QWorkbookView::setTabText(int index, QString text) {
    d_ptr->setTabText(index, text);
}

void QWorkbookView::setCurrentWidget(QWidget */*widget*/) {
    // just disables function - moves it to private.
}

QWidget* QWorkbookView::currentWidget() const {
    return QTabWidget::currentWidget();
}

QWidget* QWorkbookView::widget(int index) const {
    return QTabWidget::widget(index);
}
