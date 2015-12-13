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
#include <QDateTime>
#include <QImage>
#include <QImageReader>

#include "qworkbookview_p.h"
#include "toolbar/qworkbooktoolbar.h"
#include "toolbar/qcelledittoolbar.h"
#include "qworkbookview.h"
#include "workbook.h"
#include "qworksheetview.h"
#include "worksheetmodel.h"
#include "pluginstore.h"
#include "workbookparser.h"
#include "movecopydialog.h"

#include "workbook_global.h"

namespace QWorkbook {

quint8 QWorkbookViewPrivate::sheetNumber = 1;

QWorkbookViewPrivate::QWorkbookViewPrivate(QWorkbookView *parent) : q_ptr(parent) {

    pTabBar = q_ptr->tabBar();
    pTabBar->setMovable(false); // disallows tab dragging
    pTabBar->setUsesScrollButtons(true); // show scroll buttons if too many tabs
//    pTabBar->setDocumentMode(true);
    pTabBar->setContextMenuPolicy(Qt::CustomContextMenu);
    q_ptr->connect(pTabBar, SIGNAL(customContextMenuRequested(const QPoint &)),
                   SLOT(showContextMenu(const QPoint &)));

    q_ptr->connect(pTabBar, SIGNAL(currentChanged(int)), q_ptr, SLOT(setCurrentWorksheetView(int)));

    q_ptr->setContentsMargins(0, 0, 0, 0);
    q_ptr->setTabShape(QTabWidget::Triangular);
    q_ptr->setTabPosition(QTabWidget::South);

    createActions();

    WorkbookParser *parser = new WorkbookParser(q_ptr);
    parser->start();
    pParser = PWorkbookParser(parser);

    pBook = new Workbook(pParser, q_ptr);

    bEnableContextMenu = false;
    bEnableTabMenu = false;

}

QWorkbookViewPrivate::~QWorkbookViewPrivate() {

}

QCellEditToolBar* QWorkbookViewPrivate::editBar() {

    QCellEditToolBar* cellEditorBar = new QCellEditToolBar("celleditor", q_ptr);
    cellEditorBar->setWorkbookView(q_ptr);

    return cellEditorBar;

}

QWorkbookToolBar* QWorkbookViewPrivate::toolBar() {

    QWorkbookToolBar* toolBar = new QWorkbookToolBar("workbook", q_ptr);
    toolBar->setWorkbookView(q_ptr);

    triggerInitialSelection();

    return toolBar;
}

QStringList QWorkbookViewPrivate::names() {
    return pBook->names();
}

void QWorkbookViewPrivate::triggerInitialSelection() {
    currentWorksheetView()->triggerInitialSelection();
}

bool QWorkbookViewPrivate::showGrid(int index) {
    QWorksheetView* view = worksheetView(index);
    if (view)
        return view->showGrid();
    return false;
}

bool QWorkbookViewPrivate::showGrid(QString name) {
    QWorksheetView* view = worksheetView(name);
    if (view)
        return view->showGrid();
    return false;
}

bool QWorkbookViewPrivate::showGrid() {
    QWorksheetView* view = currentWorksheetView();
    if (view)
        return view->showGrid();
    return false;
}

void QWorkbookViewPrivate::setShowGrid(int index, bool showGrid) {
    QWorksheetView* view = worksheetView(index);
    if (view)
        view->setShowGrid(showGrid);
}

void QWorkbookViewPrivate::setShowGrid(QString name, bool showGrid) {
    QWorksheetView* view = worksheetView(name);
    if (view)
        view->setShowGrid(showGrid);
}

void QWorkbookViewPrivate::setShowGrid(bool showGrid) {
    QWorksheetView* view = currentWorksheetView();
    if (view)
        return view->setShowGrid(showGrid);
}

void QWorkbookViewPrivate::lockCell(int row, int column) {
    currentWorksheetView()->lockCell(row, column);
}

void QWorkbookViewPrivate::lockRow(int &row) {
    currentWorksheetView()->lockRow(row);
}

void QWorkbookViewPrivate::lockColumn(int &column) {
    currentWorksheetView()->lockColumn(column);
}

void QWorkbookViewPrivate::lockRange(Range &range) {
    currentWorksheetView()->lockRange(range);
}

void QWorkbookViewPrivate::lockSheet() {
    currentWorksheetView()->lockSheet();
}

void QWorkbookViewPrivate::unlockCell(int row, int column) {
    currentWorksheetView()->unlockCell(row, column);
}

void QWorkbookViewPrivate::unlockRow(int &row) {
    currentWorksheetView()->unlockRow(row);
}

void QWorkbookViewPrivate::unlockColumn(int &column) {
    currentWorksheetView()->unlockColumn(column);
}

void QWorkbookViewPrivate::unlockRange(Range &range) {
    currentWorksheetView()->unlockRange(range);
}

void QWorkbookViewPrivate::unlockSheet() {
    currentWorksheetView()->unlockSheet();
}

void QWorkbookViewPrivate::lockCell(int index, int row, int column) {
    QWorksheetView *view =  worksheetView(index);
    view->lockCell(row, column);
}

void QWorkbookViewPrivate::lockRow(int index, int &row) {
    QWorksheetView *view =  worksheetView(index);
    view->lockRow(row);
}

void QWorkbookViewPrivate::lockColumn(int index, int &column) {
    QWorksheetView *view =  worksheetView(index);
    view->lockColumn(column);
}

void QWorkbookViewPrivate::lockRange(int index, Range &range) {
    QWorksheetView *view =  worksheetView(index);
    view->lockRange(range);
}

void QWorkbookViewPrivate::lockSheet(int index) {
    QWorksheetView *view =  worksheetView(index);
    view->lockSheet();
}

void QWorkbookViewPrivate::unlockCell(int index, int row, int column) {
    QWorksheetView *view =  worksheetView(index);
    view->unlockCell(row, column);
}

void QWorkbookViewPrivate::unlockRow(int index, int &row) {
    QWorksheetView *view =  worksheetView(index);
    view->unlockRow(row);
}

void QWorkbookViewPrivate::unlockColumn(int index, int &column) {
    QWorksheetView *view =  worksheetView(index);
    view->unlockColumn(column);
}

void QWorkbookViewPrivate::unlockRange(int index, Range &range) {
    QWorksheetView *view =  worksheetView(index);
    view->unlockRange(range);
}


void QWorkbookViewPrivate::unlockSheet(int index) {
    QWorksheetView *view =  worksheetView(index);
    view->unlockSheet();
}

void QWorkbookViewPrivate::lockCell(QString name, int row, int column) {
    QWorksheetView *view =  worksheetView(name);
    view->lockCell(row, column);
}

void QWorkbookViewPrivate::lockRow(QString name, int &row) {
    QWorksheetView *view =  worksheetView(name);
    view->lockRow(row);
}

void QWorkbookViewPrivate::lockColumn(QString name, int &column) {
    QWorksheetView *view =  worksheetView(name);
    view->lockColumn(column);
}

void QWorkbookViewPrivate::lockRange(QString name, Range &range) {
    QWorksheetView *view =  worksheetView(name);
    view->lockRange(range);
}

void QWorkbookViewPrivate::lockSheet(QString name) {
    QWorksheetView *view =  worksheetView(name);
    view->lockSheet();
}

void QWorkbookViewPrivate::unlockCell(QString name, int row, int column) {
    QWorksheetView *view =  worksheetView(name);
    view->unlockCell(row, column);
}

void QWorkbookViewPrivate::unlockRow(QString name, int &row) {
    QWorksheetView *view =  worksheetView(name);
    view->unlockRow(row);
}

void QWorkbookViewPrivate::unlockColumn(QString name, int &column) {
    QWorksheetView *view =  worksheetView(name);
    view->unlockColumn(column);
}

void QWorkbookViewPrivate::unlockRange(QString name, Range &range) {
    QWorksheetView *view =  worksheetView(name);
    view->unlockRange(range);
}


void QWorkbookViewPrivate::unlockSheet(QString name) {
    QWorksheetView *view =  worksheetView(name);
    view->unlockSheet();
}

QVariant QWorkbookViewPrivate::read(int row, int column) {
    return currentWorksheetView()->read(row, column);
}

QVariant QWorkbookViewPrivate::read(int index, int row, int column) {
    QWorksheetView* sheet = worksheetView(index);
    if (sheet)
        return sheet->read(row, column);
    return QVariant();
}

QVariant QWorkbookViewPrivate::read(QString name, int row, int column) {
    QWorksheetView* sheet = worksheetView(name);
    if (sheet)
        return sheet->read(row, column);
    return QVariant();
}

void QWorkbookViewPrivate::write(int row, int column, QVariant item) {
    if (item.type() == QVariant::Image)
        writeImage(row, column, item.value<QImage>());
    else
        currentWorksheetView()->write(row, column, item);
}

void QWorkbookViewPrivate::write(int index, int row, int column, QVariant item) {
    if (item.type() == QVariant::Image)
        writeImage(index, row, column, item.value<QImage>());
    else {
        QWorksheetView* sheet = worksheetView(index);
        if (sheet)
            sheet->write(row, column, item);
    }
}

void QWorkbookViewPrivate::write(QString name, int row, int column, QVariant item) {
    if (item.type() == QVariant::Image)
        writeImage(name, row, column, item.value<QImage>());
    else {
        QWorksheetView* sheet = worksheetView(name);
        if (sheet)
            sheet->write(row, column, item);
    }
}

void QWorkbookViewPrivate::write(Range &range, QVariant item) {
    for (int row = range.top(); row <= range.bottom(); row++) {
        for (int col = range.left(); col <= range.right(); col++) {
            write(row, col, item);
        }
    }
}

void QWorkbookViewPrivate::write(int index, Range &range, QVariant item) {
    for (int row = range.top(); row <= range.bottom(); row++) {
        for (int col = range.left(); col <= range.right(); col++) {
            write(index, row, col, item);
        }
    }
}

void QWorkbookViewPrivate::write(QString name, Range &range, QVariant item) {
    for (int row = range.top(); row <= range.bottom(); row++) {
        for (int col = range.left(); col <= range.right(); col++) {
            write(name, row, col, item);
        }
    }
}

void QWorkbookViewPrivate::writeImage(int row, int column, QString path) {
    QImage image = imageFromFilename(path);
    if (image.isNull()) return;
    write(row, column, QVariant(QPixmap::fromImage(image)));
}

void QWorkbookViewPrivate::writeImage(int index, int row, int column, QString path) {
    QImage image = imageFromFilename(path);
    if (image.isNull()) return;
    write(index, row, column, QVariant(QPixmap::fromImage(image)));
}

void QWorkbookViewPrivate::writeImage(QString name, int row, int column, QString path) {
    QImage image = imageFromFilename(path);
    if (image.isNull()) return;
    write(name, row, column, QVariant(QPixmap::fromImage(image)));
}

void QWorkbookViewPrivate::writeImage(int row, int column, QImage image) {
    if (!image.isNull()) {
        QPixmap pixmap = QPixmap::fromImage(image);
        write(row, column, QVariant(pixmap));
    }
}

void QWorkbookViewPrivate::writeImage(int index, int row, int column, QImage image) {
    if (!image.isNull()) {
        QPixmap pixmap = QPixmap::fromImage(image);
        QWorksheetView* sheet = worksheetView(index);
        if (sheet)
            sheet->write(row, column, QVariant(pixmap));
    }
}

void QWorkbookViewPrivate::writeImage(QString name, int row, int column, QImage image) {
    if (!image.isNull()) {
        QPixmap pixmap = QPixmap::fromImage(image);
        QWorksheetView* sheet = worksheetView(name);
        if (sheet)
            sheet->write(row, column, QVariant(pixmap));
    }
}

QImage QWorkbookViewPrivate::imageFromFilename(QString path) {
    QFile file(path);
    if (file.exists()) {
        QImageReader reader;
        reader.setDecideFormatFromContent(true);
        reader.setDevice(&file);

        QImage image = reader.read();
        return image;
    }
    return QImage();
}

Format* QWorkbookViewPrivate::format(int row, int column) {
    return currentWorksheetView()->format(row, column);
}

Format*  QWorkbookViewPrivate::format(int index, int row, int column) {
    QWorksheetView* sheet = worksheetView(index);
    if (sheet)
        return sheet->format(row, column);
    return NULL;
}

Format*  QWorkbookViewPrivate::format(QString name, int row, int column) {
    QWorksheetView* sheet = worksheetView(name);
    if (sheet)
        return sheet->format(row, column);
    return NULL;
}

void QWorkbookViewPrivate::setFormat(int row, int column, Format* format) {
    currentWorksheetView()->setFormat(row, column, format);
}

void QWorkbookViewPrivate::setFormat(int index, int row, int column, Format* format) {
    QWorksheetView* sheet = worksheetView(index);
    if (sheet)
        sheet->setFormat(row, column, format);
}

void QWorkbookViewPrivate::setFormat(QString name, int row, int column, Format* format) {
    QWorksheetView* sheet = worksheetView(name);
    if (sheet)
        sheet->setFormat(row, column, format);
}

void QWorkbookViewPrivate::setFormat(Range &range, Format* format) {
    for (int row = range.top(); row <= range.bottom(); row++) {
        for (int col = range.left(); col <= range.right(); col++) {
            setFormat(row, col, format);
        }
    }
}

void QWorkbookViewPrivate::setFormat(int index, Range &range, Format* format) {
    for (int row = range.top(); row <= range.bottom(); row++) {
        for (int col = range.left(); col <= range.right(); col++) {
            setFormat(index, row, col, format);
        }
    }
}

void QWorkbookViewPrivate::setFormat(QString name, Range &range, Format* format) {
    for (int row = range.top(); row <= range.bottom(); row++) {
        for (int col = range.left(); col <= range.right(); col++) {
            setFormat(name, row, col, format);
        }
    }
}

void QWorkbookViewPrivate::setSelectedFormat(Format *format) {
    QWorksheetView *sheet = currentWorksheetView();

    if (sheet) {
        QModelIndexList list = sheet->selectedIndexes();
        QListIterator<QModelIndex> it(list);
        while(it.hasNext()) {
            QModelIndex index = it.next();
            if (index.isValid())
                sheet->setFormat(index.row(), index.column(), format);
        }
    }
}

void QWorkbookViewPrivate::setSelectedFormat(int index, Format *format) {
    QWorksheetView *sheet = worksheetView(index);

    if (sheet) {
        QModelIndexList list = sheet->selectedIndexes();
        QListIterator<QModelIndex> it(list);
        while(it.hasNext()) {
            QModelIndex index = it.next();
            if (index.isValid())
                sheet->setFormat(index.row(), index.column(), format);
        }
    }
}

void QWorkbookViewPrivate::setSelectedFormat(QString name, Format *format) {
    QWorksheetView *sheet = worksheetView(name);

    if (sheet) {
        QModelIndexList list = sheet->selectedIndexes();
        QListIterator<QModelIndex> it(list);
        while(it.hasNext()) {
            QModelIndex index = it.next();
            if (index.isValid())
                sheet->setFormat(index.row(), index.column(), format);
        }
    }
}

QMap<QModelIndex, Format*> QWorkbookViewPrivate::selectedFormats() {
    QMap<QModelIndex, Format*> formats;

    QWorksheetView *sheet = currentWorksheetView();
    if (sheet) {
        QModelIndexList list = sheet->selectedIndexes();
        QListIterator<QModelIndex> it(list);
        while(it.hasNext()) {
            QModelIndex index = it.next();
            if (index.isValid())
                formats.insert(index, sheet->format(index.row(), index.column()));
        }
    }
    return formats;
}

QMap<QModelIndex, Format*> QWorkbookViewPrivate::selectedFormats(int index) {
    QMap<QModelIndex, Format*> formats;

    QWorksheetView* sheet = worksheetView(index);
    if (sheet) {
        QModelIndexList list = sheet->selectedIndexes();
        QListIterator<QModelIndex> it(list);
        while(it.hasNext()) {
            QModelIndex index = it.next();
            if (index.isValid())
                formats.insert(index, sheet->format(index.row(), index.column()));
        }
    }
    return formats;
}

QMap<QModelIndex, Format*> QWorkbookViewPrivate::selectedFormats(QString name) {
    QMap<QModelIndex, Format*> formats;

    QWorksheetView* sheet = worksheetView(name);
    if (sheet) {
        QModelIndexList list = sheet->selectedIndexes();
        QListIterator<QModelIndex> it(list);
        while(it.hasNext()) {
            QModelIndex index = it.next();
            if (index.isValid())
                formats.insert(index, sheet->format(index.row(), index.column()));
        }
    }
    return formats;
}

void QWorkbookViewPrivate::alignmentHasChanged(Qt::Alignment alignment) {
    QMap<QModelIndex, Format*> formats = selectedFormats();

    Format *format;
    QListIterator<QModelIndex> it(formats.keys());
    while (it.hasNext()) {
        QModelIndex index = it.next();
        if (index.isValid()) {
            format = formats.value(index);
            format->setAlignment(alignment);
        }
    }
}

void QWorkbookViewPrivate::changeCellContents(QString text) {
    currentWorksheetView()->changeCellContents(text);
}

void QWorkbookViewPrivate::setSelectionBold(bool value) {
    currentWorksheetView()->setSelectionBold(value);
}

void QWorkbookViewPrivate::setSelectionItalic(bool value) {
    currentWorksheetView()->setSelectionItalic(value);
}

void QWorkbookViewPrivate::setSelectionUnderline(bool value) {
    currentWorksheetView()->setSelectionUnderline(value);
}

void QWorkbookViewPrivate::setSelectionFont(QFont font) {
    currentWorksheetView()->setSelectionFont(font);
}

void QWorkbookViewPrivate::setSelectionFontSize(int size) {
    currentWorksheetView()->setSelectionFontSize(size);
}

void QWorkbookViewPrivate::setSelectionAlignment(Qt::Alignment alignment) {
    currentWorksheetView()->setSelectionAlignment(alignment);
}

void QWorkbookViewPrivate::setSelectionMerge(/*bool merge*/) {
    currentWorksheetView()->setSelectionMerge(/*merge*/);
}

void QWorkbookViewPrivate::setFont(QFont font) {
    QMap<QModelIndex, Format*> formats = selectedFormats();

    Format *format;
    QListIterator<QModelIndex> it(formats.keys());
    while (it.hasNext()) {
        QModelIndex index = it.next();
        if (index.isValid()) {
            format = formats.value(index);
            format->setFont(font);
        }
    }
}

void QWorkbookViewPrivate::indentCells() {
    QMap<QModelIndex, Format*> formats = selectedFormats();

    Format *format;
    QListIterator<QModelIndex> it(formats.keys());
    while (it.hasNext()) {
        QModelIndex index = it.next();
        if (index.isValid()) {
            format = formats.value(index);
            format->indent();
        }
    }
}

void QWorkbookViewPrivate::undentCells() {
    QMap<QModelIndex, Format*> formats = selectedFormats();

    Format *format;
    QListIterator<QModelIndex> it(formats.keys());
    while (it.hasNext()) {
        QModelIndex index = it.next();
        if (index.isValid()) {
            format = formats.value(index);
            format->undent();
        }
    }
}

/*!
    \brief Sets whether the tabs are draggable within the QWorkbookView.

    By default the tabs are not draggable. Set this value to true if you want draggable
    tabs, otherwise set it to false.

*/
void QWorkbookViewPrivate::enableMovableTabs(bool movable) {
    pTabBar->setMovable(movable);
}

void QWorkbookViewPrivate::enableContextMenu(bool value) {
    bEnableContextMenu = value;
}

void QWorkbookViewPrivate::enableTabMenu(bool value) {
    bEnableTabMenu = value;
}

void QWorkbookViewPrivate::createActions() {
    Q_Q(QWorkbookView);

    // tab menu actions
    pInsertSheetBeforeAction = new QAction(q_ptr->tr("Insert New Sheet &Before"), q_ptr);
    q->connect(pInsertSheetBeforeAction, SIGNAL(triggered()),
               q_ptr, SLOT(insertSheetBefore()));

    pInsertSheetAfterAction = new QAction(q_ptr->tr("Insert New Sheet &After"), q_ptr);
    q->connect(pInsertSheetAfterAction, SIGNAL(triggered()),
               q_ptr, SLOT(insertSheetAfter()));

    pDeleteSheetAction = new QAction(q_ptr->tr("&Delete Sheet"), q_ptr);
    q->connect(pDeleteSheetAction, SIGNAL(triggered()),
               q_ptr, SLOT(deleteSheet()));

    pRenameSheetAction = new QAction(q_ptr->tr("&Rename Sheet"), q_ptr);
    q->connect(pRenameSheetAction, SIGNAL(triggered()),
               q_ptr, SLOT(renameSheet()));

    pMoveCopySheetAction = new QAction(q_ptr->tr("&Move/Copy Sheet"), q_ptr);
    q->connect(pMoveCopySheetAction, SIGNAL(triggered()),
               q_ptr, SLOT(moveCopySheet()));

    pProtectSheetAction = new QAction(q_ptr->tr("&Protect Sheet"), q_ptr);
    q->connect(pProtectSheetAction, SIGNAL(triggered()),
               q_ptr, SLOT(protectSheet()));

    pTabColorAction = new QAction(q_ptr->tr("&Tab Color"), q_ptr);
    q->connect(pTabColorAction, SIGNAL(triggered()),
               q_ptr, SLOT(tabColor()));
}

void QWorkbookViewPrivate::showContextMenu(const QPoint &point) {

    mTabIndex = pTabBar->tabAt(point);

    if (bEnableTabMenu && mTabIndex >= 0) {
        if (point.isNull())
            return;

        QMenu *insertMenu = new QMenu(q_ptr->tr("&Insert Sheet"), q_ptr);
        insertMenu->addAction(pInsertSheetBeforeAction);
        insertMenu->addAction(pInsertSheetAfterAction);


        QMenu *menu = new QMenu(q_ptr);
        menu->addMenu(insertMenu);
        menu->addAction(pDeleteSheetAction);
        menu->addAction(pRenameSheetAction);
        menu->addAction(pMoveCopySheetAction);
        menu->addAction(pProtectSheetAction);
        menu->addAction(pTabColorAction);


        menu->popup(pTabBar->mapToGlobal(point));
    }

    if (bEnableContextMenu && mTabIndex < 0) {
        // TODO context menu for main workbook sheet
    }
}


void QWorkbookViewPrivate::insertSheetBefore() {
    q_ptr->insertWorksheet(mTabIndex);
}

void QWorkbookViewPrivate::insertSheetAfter() {
    q_ptr->insertWorksheet(mTabIndex + 1);
}

void QWorkbookViewPrivate::deleteSheet() {
    q_ptr->removeWorksheet(mTabIndex);
}

void QWorkbookViewPrivate::renameSheet() {
    QString oldName = q_ptr->currentWorksheetView()->sheetName();
    bool ok;

    QString newName = QInputDialog::getText(q_ptr,
                                            q_ptr->tr("Set Tab Name"),
                                            q_ptr->tr("Enter Tab Name"),
                                            QLineEdit::Normal,
                                            oldName,
                                            &ok);
    if (ok) {
        q_ptr->renameSheet(oldName, newName);
    }

}

void QWorkbookViewPrivate::moveCopySheet() {
    QWorksheetView *view = worksheetView(mTabIndex);
    QString sheetName = view->sheetName();

    MoveCopyDialog *dlg = new MoveCopyDialog(sheetName, q_ptr);

    if (dlg->exec() == QDialog::Accepted) {
        QString newSheetName = dlg->name();
        int newTabIndex = dlg->tabIndex(); // Move before tab
        MoveCopyDialog::Type type = dlg->type();

        switch (type) {
        case MoveCopyDialog::Move: {
            if (newTabIndex >= pBook->size()) // moves to end.
                newTabIndex = pBook->size() - 1;
            pBook->moveSheet(mTabIndex, newTabIndex);
            pTabBar->moveTab(mTabIndex, newTabIndex);
            if (sheetName != newSheetName)
                renameSheet(sheetName, newSheetName);
            break;
        }
        case MoveCopyDialog::Copy: {
            QWorksheetView *view = pBook->worksheetView(mTabIndex)->clone();
            view->setSheetName(newSheetName);
            pBook->insertWorksheet(newTabIndex, view);
            q_ptr->insertTab(newTabIndex, view, view->sheetName());
            break;
        }
        }
    }

}

void QWorkbookViewPrivate::protectSheet() {
    // TODO no protectSheet in qworksheetview.
//    q_ptr->currentWorksheetView()->protectSheet();
}

void QWorkbookViewPrivate::tabColor() {
    // TODO tabColor()
}

void QWorkbookViewPrivate::saveWorkbook(QString filename, WorksheetType type) {
    pBook->saveWorkbook(filename, type);
}

int QWorkbookViewPrivate::indexOf(QWorksheetView* sheet) {
    return pBook->indexOf(sheet);
}

QWorksheetView* QWorkbookViewPrivate::currentWorksheetView() {
    return pBook->currentWorksheetView();
}

void QWorkbookViewPrivate::setCurrentWorksheetView(int index) {
    pBook->setCurrentWorksheetView(index);
    q_ptr->setCurrentIndex(index);
}

void QWorkbookViewPrivate::setCurrentWorksheetView(QString name) {
    pBook->setCurrentWorksheetView(name);
    q_ptr->setCurrentIndex(pBook->indexOf(currentWorksheetView()));
}

void QWorkbookViewPrivate::triggerCurrentSelection() {
    currentWorksheetView()->triggerCurrentSelection();
}

void QWorkbookViewPrivate::setWorkbook(Workbook *book) {
    QList<QWorksheetView*> views;
    QList<QString> names;
    pBook = book;
    int count = pBook->size();
    QWorksheetView *view;

    // remove the old stuff.
    for (int i = count - 1; i >= 0; i--) {
        removeWorksheet(i);
        q_ptr->removeTab(i);
    }

    // set up the new stuff.
    for (int i = 0; i < count; i++) {
        view = new QWorksheetView(pParser, q_ptr);
        views.append(view);
        names.append(view->sheetName());
        q_ptr->addTab(view, view->sheetName());
    }
}

QWorksheetView* QWorkbookViewPrivate::worksheetView(int index) {
    return qobject_cast<QWorksheetView*>(q_ptr->widget(index));
}

QWorksheetView* QWorkbookViewPrivate::worksheetView(QString name) {
    for (int i = 0; i < q_ptr->tabBar()->count(); i++) {
        QString tabText = q_ptr->tabBar()->tabText(i);
        if (tabText == name) {
            return qobject_cast<QWorksheetView*>(q_ptr->widget(i));
        }
    }
    return NULL;
}

QWorksheetView* QWorkbookViewPrivate::addWorksheet() {

    // creat3 new view
    QWorksheetView *view =  initWorksheet();
    // add it to the tabsheet
    // default next sheet name equals "Sheet" plus a number()
    QString sheetName = "Sheet" + QString::number(QWorkbookViewPrivate::sheetNumber++);

    view->setSheetName(sheetName);
    q_ptr->addTab(view, sheetName);

    return view;
}

QWorksheetView* QWorkbookViewPrivate::addWorksheet(QString name) {

    QWorksheetView *view = initWorksheet();

    view->setSheetName(name);
    q_ptr->addTab(view, name);

    return view;
}

QWorksheetView* QWorkbookViewPrivate::initWorksheet() {
    // create new view
    QWorksheetView *sheetView = pBook->addWorksheet();

    // link selectionChanged to internal modifier slot.
    q_ptr->connect(sheetView->selectionModel(),
                   SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                   sheetView,
                   SLOT(selectionHasChanged(QItemSelection, QItemSelection)));
    // link the result to the outside world.
    q_ptr->connect(sheetView, SIGNAL(selectionChanged(FormatStatus*)),
                   q_ptr, SIGNAL(selectionChanged(FormatStatus*)));
    q_ptr->connect(sheetView, SIGNAL(cellChanged(QVariant)),
                   q_ptr, SIGNAL(cellChanged(QVariant)));
//    q_ptr->connect(sheetView, SIGNAL(cellContentsChanged(QString)),
//                   q_ptr, SIGNAL(cellContentsChanged(QString)));

    return sheetView;
}

QWorksheetView* QWorkbookViewPrivate::insertWorksheet(int index) {

    QWorksheetView *view = initWorksheet();
    // add it to the tabsheet
    // default next sheet name equals "Sheet" plus a number()
    QString sheetName = "Sheet" + QString::number(QWorkbookViewPrivate::sheetNumber++);

    view->setSheetName(sheetName);
    q_ptr->insertTab(index, view, sheetName);

    return view;
}

QWorksheetView* QWorkbookViewPrivate::insertWorksheet(int index, QString name) {

    QWorksheetView *view = initWorksheet();

    view->setSheetName(name);
    q_ptr->insertTab(index, view, name);

    return view;
}

void QWorkbookViewPrivate::renameSheet(QString oldname, QString newname) {
    QString text;
    int index;
    bool found = false;
    for (index = 0; index < pTabBar->count(); index++) {
        text = pTabBar->tabText(index);
        if (text == oldname) {
            found = true;
            break;
        }
    }

    if (!found) return;

    pTabBar->setTabText(index, newname);
    pBook->renameSheet(oldname, newname);

}

void QWorkbookViewPrivate::setTabText(int index, QString text) {

    QString oldName = pTabBar->tabText(index);
    pTabBar->setTabText(index, text);

    QWorksheetView *sheet = pBook->worksheetView(oldName);
    sheet->setSheetName(text);

}

void QWorkbookViewPrivate::removeWorksheet(int index) {
    int i = pBook->removeWorksheet(index);
    if (i >= 0) {
        QWorksheetView *view = qobject_cast<QWorksheetView*>(q_ptr->widget(index));

        view->disconnect(view, SIGNAL(cellsSelected(QModelIndexList)),
                         q_ptr, SIGNAL(cellsSelected(QModelIndexList)));

        q_ptr->removeTab(index);
        view->deleteLater();
    }
}

void QWorkbookViewPrivate::removeWorksheet(QString name) {
    QString text;
    int index;
    bool found = false;
    for (index = 0; index < pTabBar->count(); index++) {
        text = pTabBar->tabText(index);
        if (text == name) {
            found = true;
            break;
        }
    }

    if (!found) return;

    pBook->removeWorksheet(name);

    QWorksheetView *view = qobject_cast<QWorksheetView*>(q_ptr->widget(index));

    view->disconnect(view, SIGNAL(cellsSelected(QModelIndexList)),
                     q_ptr, SIGNAL(cellsSelected(QModelIndexList)));

    view->deleteLater();

    q_ptr->removeTab(index);

}

void QWorkbookViewPrivate::removeWorksheet(QWorksheetView *sheet) {

    int index = pBook->removeWorksheet(sheet);
    if (index >= 0) {
        QWorksheetView *view = qobject_cast<QWorksheetView*>(q_ptr->widget(index));

        view->disconnect(view, SIGNAL(cellsSelected(QModelIndexList)),
                         q_ptr, SIGNAL(cellsSelected(QModelIndexList)));

        q_ptr->removeTab(index);
        view->deleteLater();
    }
}


}

