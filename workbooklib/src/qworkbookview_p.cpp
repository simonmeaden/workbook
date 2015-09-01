
#include <QDateTime>
#include <QImage>
#include <QImageReader>

#include "qworkbookview_p.h"
#include "qworkbookview.h"
#include "workbook.h"
#include "worksheet.h"
#include "qworksheetview.h"
#include "worksheetmodel.h"
#include "pluginstore.h"
#include "workbookparser.h"

//WorkbookInsertSheetDialogPrivate::WorkbookInsertSheetDialogPrivate(WorkbookInsertSheetDialog *parent) :
//    q_ptr(parent) {

//    Q_Q(WorkbookInsertSheetDialog);
//    QGridLayout *layout = new QGridLayout;
//    q->setLayout(layout);

//    QFrame *f1 = new QFrame(this);
//    QVBoxLayout *l1 = new QVBoxLayout;
//    f1->setLayout(l1);

//    l1->addWidget(new QLabel(q->tr("Position :"), this));
//    beforeBox = new QCheckBox(this);
//    l1->addWidget(beforeBox);
//    afterBox = new QCheckBox(this);
//    li->addWidget(afterBox, 2, 0);
//    tabPositionGroup = new QButtonGroup(this);
//    tabPositionGroup->addButton(beforeBox);
//    tabPositionGroup->addButton(afterBox);
//    beforeBox->setChecked(true);
//    layout->addWidget(f1, 0, 0);

//    QFrame *f2 = new QFrame(this);
//    QGridLayout *l2 = new QGridLayout;
//    f2->setLayout(l2);

//    l2->addWidget(new QLabel(q->tr("Sheet :"), this), 0, 0);
//    newSheetBox = new QCheckBox(this);
//    l2->addWidget(newSheetBox, 1, 0, 1, 2);
//    l2->addWidget(new QLabel(q->tr("No. of sheets :")), 2, 0);
//    tabCountBox = QSpinBox(this);
//    tabCountBox->setMinimum(1);
//    tabCountBox->setMaximum(100);
//    tabCountBox->setValue(1);
//    l2->addWidget(tabCountBox, 2, 1);
//    l2->addWidget(new QLabel(q->tr("Name :")), 2, 0);
//    tabFilenameEdit = new QLineEdit(this);
//    l2->addWidget(tabFilenameEdit, 2, 1);

//    QFrame *f3 = new QFrame(this);
//    QGridLayout *l3 = new QGridLayout;
//    f3->setLayout(l3);

//    okBtn = new QPushButton

//    fromFileBox = new QCheckBox(this);
//    l2->addWidget(fromFileBox, 3, 0);
//}


QWorkbookViewPrivate::QWorkbookViewPrivate(QWorkbookView *parent) : q_ptr(parent) {
    pBook = new Workbook(q_ptr);

    pCurrentView = addWorksheet();
    pPluginStore = new PluginStore(q_ptr);
    pParser = new WorkbookParser(pPluginStore, q_ptr);

}

QWorkbookViewPrivate::~QWorkbookViewPrivate() {

}

bool QWorkbookViewPrivate::showGrid(int index) {
    Worksheet* sheet = pBook->worksheet(index);
    if (sheet)
        sheet->showGrid();
    QWorksheetView* view = worksheetview(index);
    if (view)
        return view->showGrid();
    return false;
}

bool QWorkbookViewPrivate::showGrid(QString name) {
    Worksheet* sheet = pBook->worksheet(name);
    if (sheet)
        sheet->showGrid();
    QWorksheetView* view = worksheetview(name);
    if (view)
        return view->showGrid();
    return false;
}

bool QWorkbookViewPrivate::showGrid() {
    Worksheet* sheet = currentWorksheet();
    if (sheet)
        sheet->showGrid();
    QWorksheetView* view = currentWorksheetView();
    if (view)
        return view->showGrid();
    return false;
}

void QWorkbookViewPrivate::setShowGrid(int index, bool showGrid) {
    Worksheet* sheet = pBook->worksheet(index);
    if (sheet)
        sheet->setShowGrid(showGrid);
    QWorksheetView* view = worksheetview(index);
    if (view)
        view->setShowGrid(showGrid);
}

void QWorkbookViewPrivate::setShowGrid(QString name, bool showGrid) {
    Worksheet* sheet = pBook->worksheet(name);
    if (sheet)
        sheet->setShowGrid(showGrid);
    QWorksheetView* view = worksheetview(name);
    if (view)
        view->setShowGrid(showGrid);
}

void QWorkbookViewPrivate::setShowGrid(bool showGrid) {
    Worksheet* sheet = currentWorksheet();
    if (sheet)
        sheet->setShowGrid(showGrid);
    QWorksheetView* view = currentWorksheetView();
    if (view)
        return view->setShowGrid(showGrid);
}

void QWorkbookViewPrivate::lockCell(int row, int column) {
    currentWorksheet()->lockCell(row, column);
}

void QWorkbookViewPrivate::lockRow(int &row) {
    currentWorksheet()->lockRow(row);
}

void QWorkbookViewPrivate::lockColumn(int &column) {
    currentWorksheet()->lockColumn(column);
}

void QWorkbookViewPrivate::lockRange(Range &range) {
    currentWorksheet()->lockRange(range);
}

void QWorkbookViewPrivate::lockSheet() {
    currentWorksheet()->lockSheet();
}

void QWorkbookViewPrivate::unlockCell(int row, int column) {
    currentWorksheet()->unlockCell(row, column);
}

void QWorkbookViewPrivate::unlockRow(int &row) {
    currentWorksheet()->unlockRow(row);
}

void QWorkbookViewPrivate::unlockColumn(int &column) {
    currentWorksheet()->unlockColumn(column);
}

void QWorkbookViewPrivate::unlockRange(Range &range) {
    currentWorksheet()->unlockRange(range);
}

void QWorkbookViewPrivate::unlockSheet() {
    currentWorksheet()->unlockSheet();
}

void QWorkbookViewPrivate::lockCell(int index, int row, int column) {
    Worksheet* sheet = pBook->worksheet(index);
    if (sheet)
        return sheet->lockCell(row, column);
}

void QWorkbookViewPrivate::lockRow(int index, int &row) {
    Worksheet* sheet = pBook->worksheet(index);
    if (sheet)
        return sheet->lockRow(row);
}

void QWorkbookViewPrivate::lockColumn(int index, int &column) {
    Worksheet* sheet = pBook->worksheet(index);
    if (sheet)
        return sheet->lockColumn(column);
}

void QWorkbookViewPrivate::lockRange(int index, Range &range) {
    Worksheet* sheet = pBook->worksheet(index);
    if (sheet)
        return sheet->lockRange(range);
}

void QWorkbookViewPrivate::lockSheet(int index) {
    Worksheet* sheet = pBook->worksheet(index);
    if (sheet)
        return sheet->lockSheet();
}

void QWorkbookViewPrivate::unlockCell(int index, int row, int column) {
    Worksheet* sheet = pBook->worksheet(index);
    if (sheet)
        return sheet->unlockCell(row, column);
}

void QWorkbookViewPrivate::unlockRow(int index, int &row) {
    Worksheet* sheet = pBook->worksheet(index);
    if (sheet)
        return sheet->unlockRow(row);
}

void QWorkbookViewPrivate::unlockColumn(int index, int &column) {
    Worksheet* sheet = pBook->worksheet(index);
    if (sheet)
        return sheet->unlockColumn(column);
}

void QWorkbookViewPrivate::unlockRange(int index, Range &range) {
    Worksheet* sheet = pBook->worksheet(index);
    if (sheet)
        return sheet->unlockRange(range);
}


void QWorkbookViewPrivate::unlockSheet(int index) {
    Worksheet* sheet = pBook->worksheet(index);
    if (sheet)
        return sheet->unlockSheet();
}

void QWorkbookViewPrivate::lockCell(QString name, int row, int column) {
    Worksheet* sheet = pBook->worksheet(name);
    if (sheet)
        return sheet->lockCell(row, column);
}

void QWorkbookViewPrivate::lockRow(QString name, int &row) {
    Worksheet* sheet = pBook->worksheet(name);
    if (sheet)
        return sheet->lockRow(row);
}

void QWorkbookViewPrivate::lockColumn(QString name, int &column) {
    Worksheet* sheet = pBook->worksheet(name);
    if (sheet)
        return sheet->lockColumn(column);
}

void QWorkbookViewPrivate::lockRange(QString name, Range &range) {
    Worksheet* sheet = pBook->worksheet(name);
    if (sheet)
        return sheet->lockRange(range);
}

void QWorkbookViewPrivate::lockSheet(QString name) {
    Worksheet* sheet = pBook->worksheet(name);
    if (sheet)
        return sheet->lockSheet();
}

void QWorkbookViewPrivate::unlockCell(QString name, int row, int column) {
    Worksheet* sheet = pBook->worksheet(name);
    if (sheet)
        return sheet->unlockCell(row, column);
}

void QWorkbookViewPrivate::unlockRow(QString name, int &row) {
    Worksheet* sheet = pBook->worksheet(name);
    if (sheet)
        return sheet->unlockRow(row);
}

void QWorkbookViewPrivate::unlockColumn(QString name, int &column) {
    Worksheet* sheet = pBook->worksheet(name);
    if (sheet)
        return sheet->unlockColumn(column);
}

void QWorkbookViewPrivate::unlockRange(QString name, Range &range) {
    Worksheet* sheet = pBook->worksheet(name);
    if (sheet)
        return sheet->unlockRange(range);
}


void QWorkbookViewPrivate::unlockSheet(QString name) {
    Worksheet* sheet = pBook->worksheet(name);
    if (sheet)
        return sheet->unlockSheet();
}



QVariant QWorkbookViewPrivate::read(int row, int column) {
    return currentWorksheetView()->read(row, column);
}

QVariant QWorkbookViewPrivate::read(int index, int row, int column) {
    QWorksheetView* sheet = worksheetview(index);
    if (sheet)
        return sheet->read(row, column);
    return QVariant();
}

QVariant QWorkbookViewPrivate::read(QString name, int row, int column) {
    QWorksheetView* sheet = worksheetview(name);
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
        QWorksheetView* sheet = worksheetview(index);
        if (sheet)
            sheet->write(row, column, item);
    }
}

void QWorkbookViewPrivate::write(QString name, int row, int column, QVariant item) {
    if (item.type() == QVariant::Image)
        writeImage(name, row, column, item.value<QImage>());
    else {
        QWorksheetView* sheet = worksheetview(name);
        if (sheet)
            sheet->write(row, column, item);
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
        QWorksheetView* sheet = worksheetview(index);
        if (sheet)
            sheet->write(row, column, QVariant(pixmap));
    }
}

void QWorkbookViewPrivate::writeImage(QString name, int row, int column, QImage image) {
    if (!image.isNull()) {
        QPixmap pixmap = QPixmap::fromImage(image);
        QWorksheetView* sheet = worksheetview(name);
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
    QWorksheetView* sheet = worksheetview(index);
    if (sheet)
        return sheet->format(row, column);
    return NULL;
}

Format*  QWorkbookViewPrivate::format(QString name, int row, int column) {
    QWorksheetView* sheet = worksheetview(name);
    if (sheet)
        return sheet->format(row, column);
    return NULL;
}

void QWorkbookViewPrivate::setFormat(int row, int column, Format* format) {
    currentWorksheetView()->setFormat(row, column, format);
}

void QWorkbookViewPrivate::setFormat(int index, int row, int column, Format* format) {
    QWorksheetView* sheet = worksheetview(index);
    if (sheet)
        sheet->setFormat(row, column, format);
}

void QWorkbookViewPrivate::setFormat(QString name, int row, int column, Format* format) {
    QWorksheetView* sheet = worksheetview(name);
    if (sheet)
        sheet->setFormat(row, column, format);
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
    QWorksheetView *sheet = worksheetview(index);

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
    QWorksheetView *sheet = worksheetview(name);

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

    QWorksheetView* sheet = worksheetview(index);
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

    QWorksheetView* sheet = worksheetview(name);
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

void QWorkbookViewPrivate::setBold(bool value) {
    QMap<QModelIndex, Format*> formats = selectedFormats();

    Format *format;
    QListIterator<QModelIndex> it(formats.keys());
    while (it.hasNext()) {
        QModelIndex index = it.next();
        if (index.isValid()) {
            format = formats.value(index);
            format->setBold(value);
        }
    }
}

void QWorkbookViewPrivate::setItalic(bool value) {
    QMap<QModelIndex, Format*> formats = selectedFormats();

    Format *format;
    QListIterator<QModelIndex> it(formats.keys());
    while (it.hasNext()) {
        QModelIndex index = it.next();
        if (index.isValid()) {
            format = formats.value(index);
            format->setItalic(value);
        }
    }
}

void QWorkbookViewPrivate::setUnderline(bool value) {
    QMap<QModelIndex, Format*> formats = selectedFormats();

    Format *format;
    QListIterator<QModelIndex> it(formats.keys());
    while (it.hasNext()) {
        QModelIndex index = it.next();
        if (index.isValid()) {
            format = formats.value(index);
            format->setUnderline(value);
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

void QWorkbookViewPrivate::enableContextMenu(bool value) {
    bEnableContextMenu = value;
}

void QWorkbookViewPrivate::enableTabMenu(bool value) {
    pEnableTabMenu = value;
}

void QWorkbookViewPrivate::createActions() {
    Q_Q(QWorkbookView);
    pInsertSheetAction = new QAction(q_ptr->tr("Insert Sheet"), q_ptr);
    q->connect(pInsertSheetAction, SIGNAL(triggered()),
               q_ptr, SLOT(insertSheet()));

    pRenameSheetAction = new QAction(q_ptr->tr("Rename Sheet"), q_ptr);
    q->connect(pRenameSheetAction, SIGNAL(triggered()),
               q_ptr, SLOT(renameSheet()));

    pMoveCopySheetAction = new QAction(q_ptr->tr("Move/Copy Sheet"), q_ptr);
    q->connect(pMoveCopySheetAction, SIGNAL(triggered()),
               q_ptr, SLOT(moveCopySheet()));

    pProtectSheetAction = new QAction(q_ptr->tr("Protect Sheet"), q_ptr);
    q->connect(pProtectSheetAction, SIGNAL(triggered()),
               q_ptr, SLOT(protectSheet()));

    pTabColorAction = new QAction(q_ptr->tr("Tab Color"), q_ptr);
    q->connect(pTabColorAction, SIGNAL(triggered()),
               q_ptr, SLOT(tabColor()));
}

void QWorkbookViewPrivate::insertSheet() {
//    Q_Q(QWorkbookView);

}

void QWorkbookViewPrivate::renameSheet() {

}

void QWorkbookViewPrivate::moveCopySheet() {

}

void QWorkbookViewPrivate::protectSheet() {

}

void QWorkbookViewPrivate::tabColor() {

}

void QWorkbookViewPrivate::showContextMenu(const QPoint &/*point*/) {
//    Q_Q(QWorkbookView);

//    int tabIndex = q->p_tabBar->tabAt(point);

//    if (m_enableTabMenu && tabIndex >= 0) {
//        if (point.isNull())
//            return;


//        QMenu *menu = new QMenu(this);
//        menu->addAction(insertSheetAction);
//        menu->addAction(renameSheetAction);
//        menu->addAction(moveCopySheetAction);
//        menu->addAction(protectSheetAction);
//        menu->addAction(tabColorAction);


//        menu->popup(q->p_tabBar->mapToGlobal(point));
//    }

//    if (m_enableContextMenu && tabIndex < 0) {
//        // TODO context menu for main workbook sheet
//    }
}

void QWorkbookViewPrivate::saveWorkbook(QString filename) {
    pBook->saveWorkbook(filename);
}

void QWorkbookViewPrivate::saveWorkbook(QString filename, WorksheetType type) {
    pBook->saveWorkbook(filename, type);
}

int QWorkbookViewPrivate::indexOf(Worksheet* sheet) {
    return pBook->indexOf(sheet);
}

QWorksheetView* QWorkbookViewPrivate::currentWorksheetView() {
    return pCurrentView;
}

Worksheet* QWorkbookViewPrivate::currentWorksheet() {
    return pBook->currentWorksheet();
}

void QWorkbookViewPrivate::setCurrentWorksheet(int index) {
    pBook->setCurrentWorksheet(index);
    q_ptr->setCurrentIndex(index);
    pCurrentView = qobject_cast<QWorksheetView*>(q_ptr->currentWidget());
}

void QWorkbookViewPrivate::setCurrentWorksheet(QString name) {
    pBook->setCurrentWorksheet(name);
    q_ptr->setCurrentIndex(pBook->indexOf(currentWorksheet()));
    pCurrentView = qobject_cast<QWorksheetView*>(q_ptr->currentWidget());
}


void QWorkbookViewPrivate::setWorkbook(Workbook *book) {
    QList<QWorksheetView*> views;
    QList<QString> names;
    pBook = book;
    int count = pBook->count();
    Worksheet *sheet;
    WorksheetModel *model;
    QWorksheetView *view;

    // remove the old stuff.
    for (int i = count - 1; i >= 0; i--) {
        removeWorksheet(i);
        q_ptr->removeTab(i);
    }

    // set up the new stuff.
    for (int i = 0; i < count; i++) {
        sheet = pBook->worksheet(i);
        model = new WorksheetModel(sheet, pPluginStore, q_ptr);
        view = new QWorksheetView(pParser, pPluginStore, q_ptr);
        view->setModel(model);
        views.append(view);
        names.append(sheet->sheetName());
        q_ptr->addTab(view, sheet->sheetName());
    }
}

QWorksheetView* QWorkbookViewPrivate::worksheetview(int index) {
    return qobject_cast<QWorksheetView*>(q_ptr->widget(index));
}

QWorksheetView* QWorkbookViewPrivate::worksheetview(QString name) {
    for (int i = 0; i < q_ptr->tabBar()->count(); i++) {
        QString tabText = q_ptr->tabBar()->tabText(i);
        if (tabText == name) {
            return qobject_cast<QWorksheetView*>(q_ptr->widget(i));
        }
    }
    return NULL;
}

QWorksheetView* QWorkbookViewPrivate::addWorksheet() {
    Worksheet *sheet = pBook->addWorksheet();
    WorksheetModel *model = new WorksheetModel(sheet, pPluginStore, q_ptr);

    QWorksheetView *view =  initWorksheet(model);
    q_ptr->addTab(view, sheet->sheetName());
    return view;
}

QWorksheetView* QWorkbookViewPrivate::addWorksheet(QString name) {
    Worksheet *sheet = pBook->addWorksheet();
    WorksheetModel *model = new WorksheetModel(sheet, pPluginStore, q_ptr);
    sheet->setSheetName(name);

    QWorksheetView *view =  initWorksheet(model);
    q_ptr->addTab(view, name);
    return view;
}

QWorksheetView* QWorkbookViewPrivate::initWorksheet(WorksheetModel *model) {
    QWorksheetView *view = new QWorksheetView(pParser, pPluginStore, q_ptr);
    q_ptr->connect(view, SIGNAL(cellSelected(Cell*)), q_ptr, SIGNAL(cellSelected(Cell*)));
    q_ptr->connect(view, SIGNAL(rangeSelected(Range&)), q_ptr, SIGNAL(rangeSelected(Range&)));
    q_ptr->connect(view, SIGNAL(nonContiguousRangeSelected()), q_ptr, SIGNAL(nonContiguousRangeSelected()));
    q_ptr->connect(view, SIGNAL(cellsChanged(QString)), q_ptr, SIGNAL(cellsChanged(QString)));

    q_ptr->connect(view->selectionModel(),
                   SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                   view,
                   SLOT(selectionHasChanged(QItemSelection, QItemSelection)));

    q_ptr->connect(view->selectionModel(),
                   SIGNAL(currentChanged(QModelIndex,QModelIndex)),
                   view,
                   SLOT(currentCellChanged(QModelIndex,QModelIndex)));

    view->setModel(model);
    return view;

}

QWorksheetView* QWorkbookViewPrivate::insertWorksheet(int index) {
    Worksheet *sheet = pBook->insertWorksheet(index);
    WorksheetModel *model = new WorksheetModel(sheet, pPluginStore, q_ptr);

    QWorksheetView *view = initWorksheet(model);

    q_ptr->insertTab(index, view, sheet->sheetName());
    return view;
}

QWorksheetView* QWorkbookViewPrivate::insertWorksheet(int index, QString name) {
    Worksheet *sheet = pBook->insertWorksheet(index);
    sheet->setSheetName(name);
    WorksheetModel *model = new WorksheetModel(sheet, pPluginStore, q_ptr);

    QWorksheetView *view = initWorksheet(model);

    q_ptr->insertTab(index, view, name);
    return view;
}

void QWorkbookViewPrivate::renameSheet(QString oldname, QString newname) {
    int index = pBook->renameSheet(oldname, newname);
    q_ptr->tabBar()->setTabText(index, newname);
}

void QWorkbookViewPrivate::setTabText(int index, QString text) {
    Worksheet *sheet = pBook->insertWorksheet(index);
    sheet->setSheetName(text);
    q_ptr->tabBar()->setTabText(index, text);
}

void QWorkbookViewPrivate::removeWorksheet(int index) {
    int i = pBook->removeWorksheet(index);
    if (i >= 0) {
        QWorksheetView *view = qobject_cast<QWorksheetView*>(q_ptr->widget(index));
        q_ptr->removeTab(index);
        view->deleteLater();
    }
}

void QWorkbookViewPrivate::removeWorksheet(QString name) {
    int index = pBook->removeWorksheet(name);
    if (index >= 0) {
        QWorksheetView *view = qobject_cast<QWorksheetView*>(q_ptr->widget(index));
        q_ptr->removeTab(index);
        view->deleteLater();
    }
}

void QWorkbookViewPrivate::removeWorksheet(Worksheet *sheet) {
    int index = pBook->removeWorksheet(sheet);
    if (index >= 0) {
        QWorksheetView *view = qobject_cast<QWorksheetView*>(q_ptr->widget(index));
        q_ptr->removeTab(index);
        view->deleteLater();
    }
}

