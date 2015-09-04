
#include <QDateTime>
#include <QImage>
#include <QImageReader>

#include "qworkbookview_p.h"
#include "toolbar/qworkbooktoolbar.h"
#include "qworkbookview.h"
#include "workbook.h"
#include "worksheet.h"
#include "qworksheetview.h"
#include "worksheetmodel.h"
#include "pluginstore.h"
#include "workbookparser.h"

quint8 QWorkbookViewPrivate::sheetNumber = 1;

QWorkbookViewPrivate::QWorkbookViewPrivate(QWorkbookView *parent) : q_ptr(parent) {
    Q_Q(QWorkbookView);

    pTabBar = q_ptr->tabBar();
    pTabBar->setContextMenuPolicy(Qt::CustomContextMenu);
    q_ptr->connect(pTabBar, SIGNAL(customContextMenuRequested(const QPoint &)),
                   SLOT(showContextMenu(const QPoint &)));

    q_ptr->setContentsMargins(0, 0, 0, 0);
    q_ptr->setTabShape(QTabWidget::Triangular);
    q_ptr->setTabPosition(QTabWidget::South);

    createActions();

    pBook = new Workbook(q_ptr);

    pPluginStore = new PluginStore(q_ptr);
    pParser = new WorkbookParser(pPluginStore, q_ptr);

    pCurrentView = addWorksheet();
}

QWorkbookViewPrivate::~QWorkbookViewPrivate() {

}

QWorkbookToolBar* QWorkbookViewPrivate::toolBar() {
    Q_Q(QWorkbookView);

    QWorkbookToolBar* toolBar = NULL;

    toolBar = new QWorkbookToolBar("workbook", q_ptr);

    // bar to view
    q_ptr->connect(toolBar, SIGNAL(boldChanged(bool)), q_ptr, SLOT(setSelectionBold(bool)));
    q_ptr->connect(toolBar, SIGNAL(italicChanged(bool)), q_ptr, SLOT(setSelectionItalic(bool)));
    q_ptr->connect(toolBar, SIGNAL(underlineChanged(bool)), q_ptr, SLOT(setSelectionUnderline(bool)));
    q_ptr->connect(toolBar, SIGNAL(fontChanged(QFont)), q_ptr, SLOT(setSelectionFont(QFont)));
    q_ptr->connect(toolBar, SIGNAL(fontSizeChanged(int)), q_ptr, SLOT(setSelectionFontSize(int)));
    q_ptr->connect(toolBar, SIGNAL(alignmentChanged(Qt::Alignment)), q_ptr, SLOT(setSelectionAlignment(Qt::Alignment)));

    // view to bar
    q_ptr->connect(q_ptr, SIGNAL(boldSelection(bool)), toolBar, SLOT(setSelectionBold(bool)));
    q_ptr->connect(q_ptr, SIGNAL(italicSelection(bool)), toolBar, SLOT(setSelectionUnderline(bool)));
    q_ptr->connect(q_ptr, SIGNAL(underlineSelection(bool)), toolBar, SLOT(setSelectionUnderline(bool)));
    // TODO connect the rest
//    q_ptr->connect(toolBar, SIGNAL(alignmentChanged(Qt::Alignment)),
//            q_ptr, SLOT(alignmentHasChanged(Qt::Alignment)));
//    q_ptr->connect(toolBar, SIGNAL(indentCells()), q_ptr, SLOT(indentCells()));
//    q_ptr->connect(toolBar, SIGNAL(undentCells()), q_ptr, SLOT(undentCells()));
//    q_ptr->connect(toolBar, SIGNAL(fontChanged(QFont)), q_ptr, SLOT(setFont(QFont)));

    q_ptr->connect(q_ptr, SIGNAL(selectionChanged(FormatStatus*)),
            toolBar, SLOT(selectionChanged(FormatStatus*)));

    triggerInitialSelection();

    return toolBar;
}

void QWorkbookViewPrivate::triggerInitialSelection() {
    QModelIndex index = pCurrentView->model()->index(0, 0);
    QItemSelection selection(index, index);
    pCurrentView->selectionHasChanged(selection, selection);
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
void QWorkbookViewPrivate::setSelectionBold(bool value) {
    pCurrentView->setSelectionBold(value);
}

void QWorkbookViewPrivate::setSelectionItalic(bool value) {
    pCurrentView->setSelectionItalic(value);
}

void QWorkbookViewPrivate::setSelectionUnderline(bool value) {
    pCurrentView->setSelectionUnderline(value);
}

void QWorkbookViewPrivate::setSelectionFont(QFont font) {
    pCurrentView->setSelectionFont(font);
}

void QWorkbookViewPrivate::setSelectionFontSize(int size) {
    pCurrentView->setSelectionFontSize(size);
}

void QWorkbookViewPrivate::setSelectionAlignment(Qt::Alignment alignment) {
    pCurrentView->setSelectionAlignment(alignment);
}

void QWorkbookViewPrivate::setSelectionMerge(bool merge) {
    pCurrentView->setSelectionMerge(merge);
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
    // TODO insertSheet()
}

void QWorkbookViewPrivate::renameSheet() {
    // TODO renameSheet()
}

void QWorkbookViewPrivate::moveCopySheet() {
    // TODO moveCopySheet()
}

void QWorkbookViewPrivate::protectSheet() {
    // TODO protectSheet()
}

void QWorkbookViewPrivate::tabColor() {
    // TODO tabColor()
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
//        model = new WorksheetModel(sheet, pPluginStore, q_ptr);
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
    QWorksheetView *view = new QWorksheetView(pParser, pPluginStore, q_ptr);

    // link selectionChanged to internal modifier slot.
    q_ptr->connect(view->selectionModel(),
                   SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                   view,
                   SLOT(selectionHasChanged(QItemSelection, QItemSelection)));
    // link the result to the outside world.
    q_ptr->connect(view, SIGNAL(selectionChanged(FormatStatus*)),
                  q_ptr, SIGNAL(selectionChanged(FormatStatus*)));

    return view;
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

    Worksheet *sheet = pBook->worksheet(oldName);
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

void QWorkbookViewPrivate::removeWorksheet(Worksheet *sheet) {

    int index = pBook->removeWorksheet(sheet);
    if (index >= 0) {
        QWorksheetView *view = qobject_cast<QWorksheetView*>(q_ptr->widget(index));

        view->disconnect(view, SIGNAL(cellsSelected(QModelIndexList)),
                         q_ptr, SIGNAL(cellsSelected(QModelIndexList)));

        q_ptr->removeTab(index);
        view->deleteLater();
    }
}

