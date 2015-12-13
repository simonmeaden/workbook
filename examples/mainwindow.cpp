#include "mainwindow.h"

#include <QWorksheetView>
#include <QWorkbookView>
#include <QWorkbookToolbar>
#include <QCellEditToolbar>
#include <QWorkbookFunctionToolbar>
#include <Workbook>
#include <CellReference>

#include "workbook_global.h"
#include "workbookparser.h"
#include "cellreference.h"
#include "parser.h"

QWORKBOOK_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    initBuild();

    initActions();
    initMenu();
    initToolbar();

    pBookView->enableMovableTabs(true);
    pBookView->enableTabMenu(true);

    tabChanged(0);

    // zero based values
    int col = Reference::columnFromString("A"); // 0
    qDebug() << qSetFieldWidth(6) << "A"  << col;
    col = Reference::columnFromString("Z");     // 25
    qDebug() << qSetFieldWidth(6) << "Z"  << col;
    col = Reference::columnFromString("AA");    // 27 - (1 * 26) +  1
    qDebug() << qSetFieldWidth(6) << "AA"  << col;
    col = Reference::columnFromString("AB");    // 28 - (1 * 26) + 2
    qDebug() << qSetFieldWidth(6) << "AB"  << col;
    col = Reference::columnFromString("ZZ");
    qDebug() << qSetFieldWidth(6) << "ZZ"  << col;
    col = Reference::columnFromString("AAA");
    qDebug() << qSetFieldWidth(6) << "AAA"  << col;
    col = Reference::columnFromString("ZZZ");
    qDebug() << qSetFieldWidth(6) << "ZZZ"  << col;

    pSheetView->write(210, 110, QVariant(100.0));

}


void MainWindow::fileClose() {
    close();
}

void MainWindow::fileNewWorkbook() {
    // TODO
}

void MainWindow::fileOpenWorkbook() {
    // TODO
}

void MainWindow::fileSaveWorkbook() {
    // TODO
}

void MainWindow::fileSaveWorkbookAs() {
    // TODO
}

void MainWindow::fileNewWorksheet() {
    // TODO
}

void MainWindow::fileOpenWorksheet() {
    // TODO
}

void MainWindow::fileSaveWorksheet() {
    QString selectedFilter;
    QString filename = QFileDialog::getSaveFileName(
                           this,
                           tr("Save Worksheet"),
                           "/workspace/qt/common/workbook/examples",
                           tr("OpenOffice Calc (*.ods);;Excel XLSX (*.xlsx);;Text Files (*.csv)"),
                           &selectedFilter/*, options*/);
    WorksheetType type = ODS;

    if (!filename.isEmpty()) {
        if (selectedFilter == "*.ods)") type = ODS;
        pSheetView->saveWorksheet(filename, type);
    }
}

void MainWindow::fileSaveWorksheetAs() {
    // TODO
}

void MainWindow::filePrintBook() {
    // TODO
}

void MainWindow::filePrintSheet() {
    // TODO
}

void MainWindow::initActions() {

    pNewBookAct = new QAction(tr("&New Book"), this);
    pNewBookAct->setShortcuts(QKeySequence::New);
    pNewBookAct->setStatusTip(tr("Create a new file"));
    connect(pNewBookAct, SIGNAL(triggered()), this, SLOT(fileNewWorkbook()));

    pOpenBookAct = new QAction(tr("&Open Book"), this);
    pOpenBookAct->setShortcuts(QKeySequence::Open);
    pOpenBookAct->setStatusTip(tr("Open a file"));
    connect(pOpenBookAct, SIGNAL(triggered()), this, SLOT(fileOpenWorkbook()));

    pSaveBookAct = new QAction(tr("&Save Book"), this);
    pSaveBookAct->setShortcuts(QKeySequence::Save);
    pSaveBookAct->setStatusTip(tr("Save file"));
    connect(pSaveBookAct, SIGNAL(triggered()), this, SLOT(fileSaveWorkbook()));

    pSaveBookAsAct = new QAction(tr("Save Book &As"), this);
    pSaveBookAsAct->setShortcuts(QKeySequence::SaveAs);
    pSaveBookAsAct->setStatusTip(tr("Save file as..."));
    connect(pSaveBookAsAct, SIGNAL(triggered()), this, SLOT(fileSaveWorkbookAs()));

    pPrintBookAct = new QAction(tr("&Print"), this);
    pPrintBookAct->setShortcuts(QKeySequence::Print);
    pPrintBookAct->setStatusTip(tr("Print a file"));
    connect(pPrintBookAct, SIGNAL(triggered()), this, SLOT(filePrintBook()));


    pNewSheetAct = new QAction(tr("&New Sheet"), this);
    pNewSheetAct->setShortcuts(QKeySequence::New);
    pNewSheetAct->setStatusTip(tr("Create a new sheet"));
    connect(pNewSheetAct, SIGNAL(triggered()), this, SLOT(fileNewWorksheet()));

    pOpenSheetAct = new QAction(tr("&Open Sheet"), this);
    pOpenSheetAct->setShortcuts(QKeySequence::Open);
    pOpenSheetAct->setStatusTip(tr("Open a sheet"));
    connect(pOpenSheetAct, SIGNAL(triggered()), this, SLOT(fileOpenWorksheet()));

    pSaveSheetAct = new QAction(tr("&Save Sheet"), this);
    pSaveSheetAct->setShortcuts(QKeySequence::Save);
    pSaveSheetAct->setStatusTip(tr("Save sheet"));
    connect(pSaveSheetAct, SIGNAL(triggered()), this, SLOT(fileSaveWorksheet()));

    pSaveSheetAsAct = new QAction(tr("Save Sheet &As"), this);
    pSaveSheetAsAct->setShortcuts(QKeySequence::SaveAs);
    pSaveSheetAsAct->setStatusTip(tr("Save sheet as..."));
    connect(pSaveSheetAsAct, SIGNAL(triggered()), this, SLOT(fileSaveWorksheetAs()));


    pPrintSheetAct = new QAction(tr("&Print Worksheet"), this);
    pPrintSheetAct->setShortcuts(QKeySequence::Print);
    pPrintSheetAct->setStatusTip(tr("Print a worksheet"));
    connect(pPrintSheetAct, SIGNAL(triggered()), this, SLOT(filePrintBook()));

    pCloseAct = new QAction(tr("E&xit"), this);
    pCloseAct->setShortcuts(QKeySequence::Close);
    pCloseAct->setStatusTip(tr("Exit Application"));
    connect(pCloseAct, SIGNAL(triggered()), this, SLOT(fileClose()));

}

void MainWindow::initMenu() {

    QMenuBar *menu = menuBar();

    QMenu *fileMenu = new QMenu(tr("File"), this);
    fileMenu->addAction(pCloseAct);
    menu->addMenu(fileMenu);

    QMenu *worksheetMenu = new QMenu(tr("Worksheet"), this);
    worksheetMenu->addAction(pNewSheetAct);
    worksheetMenu->addAction(pOpenSheetAct);
    worksheetMenu->addAction(pSaveSheetAct);
    worksheetMenu->addAction(pSaveSheetAsAct);
    worksheetMenu->addSeparator();
    worksheetMenu->addAction(pPrintSheetAct);
    menu->addMenu(worksheetMenu);

    QMenu *workbookMenu = new QMenu(tr("Workbook"), this);
    workbookMenu->addAction(pNewBookAct);
    workbookMenu->addAction(pOpenBookAct);
    workbookMenu->addAction(pSaveBookAct);
    workbookMenu->addAction(pSaveBookAsAct);
    workbookMenu->addSeparator();
    workbookMenu->addAction(pPrintBookAct);
    menu->addMenu(workbookMenu);

}

void MainWindow::initToolbar() {

    pToolbar = new QWorkbookToolBar(this);
    addToolBar(pToolbar);
    pToolbar->setWorkbookView(pBookView);

    pCellEditorBar = new QCellEditToolBar("celleditor", this);
    addToolBar(pCellEditorBar);
    pCellEditorBar->setWorkbookView(pBookView);

    pFunctionBar = new QWorkbookFunctionToolBar("function", this);
//    pFunctionVisibleAction = functionBar->toggleViewAction();
    addToolBar(pFunctionBar);


//    toolbar->showAlignBar(false);
}

void MainWindow::tabChanged(int tab) {
    QString text = pTabs->tabText(tab);
    if (text == "Workbook") {
        pToolbar->setWorkbookView(pBookView);
        pCellEditorBar->setWorkbookView(pBookView);
    } else if (text == "Worksheet") {
        pToolbar->setWorksheetView(pSheetView);
        pCellEditorBar->setWorksheetView(pSheetView);
    }
}

void MainWindow::initBuild() {

    QFrame *frame = new QFrame(this);
    QGridLayout *layout = new QGridLayout;
    frame->setLayout(layout);
    setCentralWidget(frame);

    pTabs = new QTabWidget(this);
    layout->addWidget(pTabs, 0, 0);

    pTabs->addTab(initWorkbook(), tr("Workbook"));
    pTabs->addTab(initWorksheet(), tr("Worksheet"));
    pTabs->addTab(initFunctionParserTest(), tr("Function Parser"));
    pTabs->addTab(initTest(), tr("Test"));

    connect(pTabs, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));

    pQuitBtn = new QPushButton(tr("Quit"), this);
    layout->addWidget(pQuitBtn, 1, 0);
    connect(pQuitBtn, SIGNAL(clicked()), this, SLOT(close()));

}

QFrame* MainWindow::initFunctionParserTest() {
    QFrame *frame = new QFrame(this);
    QGridLayout *layout = new QGridLayout;
    layout->setColumnStretch(0, 2);
    frame->setLayout(layout);

    pTestView = new QWorksheetView(this);
    layout->addWidget(pTestView, 1, 0);

    pCellFunctionEditor = new QLineEdit(this);
    layout->addWidget(pCellFunctionEditor, 0, 0);

    pTokeniseBtn = new QPushButton(tr("Tokenise"), this);
    layout->addWidget(pTokeniseBtn, 0, 1);

    pTokenOutput = new QPlainTextEdit(this);
    layout->addWidget(pTokenOutput, 1, 1);

    return frame;
}

QFrame* MainWindow::initTest() {
    QFrame *frame = new QFrame(this);
    QGridLayout *layout = new QGridLayout;
    frame->setLayout(layout);

    layout->addWidget(initTestCellReference(), 0, 0);
    layout->addWidget(initTestRange(), 0, 1);

    QFrame *dummy = new QFrame(this);
    dummy->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(dummy, 1, 0, 1, 2);

    return frame;
}

QFrame* MainWindow::initTestCellReference() {
    QFrame *frame = new QFrame(this);
    frame->setFrameStyle(QFrame::StyledPanel);
    QVBoxLayout *layout = new QVBoxLayout;
    frame->setLayout(layout);

    QFrame *f1 = new QFrame(this);
    QGridLayout *l1 = new QGridLayout;
    f1->setLayout(l1);
    layout->addWidget(f1);

    QLabel *lbl1 = new QLabel(tr("Cell Reference"), this);
    l1->addWidget(lbl1, 0, 0);
    pCellReferenceEdit = new QLineEdit(this);
    l1->addWidget(pCellReferenceEdit, 0, 1);
    QPushButton *btn1 = new QPushButton(tr("Test"), this);
    l1->addWidget(btn1, 0, 2);
    connect(btn1, SIGNAL(clicked()), this, SLOT(testReference()));

    QFrame *f2 = new QFrame(this);
    QGridLayout *l2 = new QGridLayout;
    f2->setLayout(l2);
    layout->addWidget(f2);

    QLabel *lbl2_1 =  new QLabel(tr("CellReference:"), this);
    l2->addWidget(lbl2_1, 0, 0);
    pReferenceLbl = new QLabel(this);
    l2->addWidget(pReferenceLbl, 0, 1, 1, 3);
    QLabel *lbl2_3 =  new QLabel(tr("Row:"), this);
    l2->addWidget(lbl2_3, 1, 0);
    pRowLbl = new QLabel(this);
    l2->addWidget(pRowLbl, 1, 1);
    QLabel *lbl2_5 =  new QLabel(tr("Static:"), this);
    l2->addWidget(lbl2_5, 1, 2);
    pStaticRowLbl = new QLabel(this);
    l2->addWidget(pStaticRowLbl, 1, 3);
    QLabel *lbl2_7 =  new QLabel(tr("Column:"), this);
    l2->addWidget(lbl2_7, 2, 0);
    pColumnLbl = new QLabel(this);
    l2->addWidget(pColumnLbl, 2, 1);
    QLabel *lbl2_9 =  new QLabel(tr("Static:"), this);
    l2->addWidget(lbl2_9, 2, 2);
    pStaticColumnLbl = new QLabel(this);
    l2->addWidget(pStaticColumnLbl, 2, 3);


    return frame;
}

QFrame* MainWindow::initTestRange() {

    QFrame *frame = new QFrame(this);
    frame->setFrameStyle(QFrame::StyledPanel);
    QVBoxLayout *layout = new QVBoxLayout;
    frame->setLayout(layout);

    QFrame *f1 = new QFrame(this);
    QGridLayout *l1 = new QGridLayout;
    f1->setLayout(l1);
    layout->addWidget(f1);

    QLabel *lbl1 = new QLabel(tr("Range"), this);
    l1->addWidget(lbl1, 0, 0);
    pRangeEdit = new QLineEdit(this);
    l1->addWidget(pRangeEdit, 0, 1);
    QPushButton *btn1 = new QPushButton(tr("Test"), this);
    l1->addWidget(btn1, 0, 2);
    connect(btn1, SIGNAL(clicked()), this, SLOT(testRange()));

    QFrame *f2 = new QFrame(this);
    QGridLayout *l2 = new QGridLayout;
    f2->setLayout(l2);
    layout->addWidget(f2);

    QLabel *lbl2_1 =  new QLabel(tr("Range:"), this);
    l2->addWidget(lbl2_1, 0, 0);
    pRangeLbl = new QLabel(this);
    l2->addWidget(pRangeLbl, 0, 1, 1, 3);

    QLabel *lbl2_2 =  new QLabel(tr("CellReference 1:"), this);
    l2->addWidget(lbl2_2, 1, 0);
    pReference1Lbl = new QLabel(this);
    l2->addWidget(pReference1Lbl, 1, 1, 1, 3);
    QLabel *lbl2_3 =  new QLabel(tr("Row 1:"), this);
    l2->addWidget(lbl2_3, 2, 0);
    pRow1Lbl = new QLabel(this);
    l2->addWidget(pRow1Lbl, 2, 1);
    QLabel *lbl2_5 =  new QLabel(tr("Static 1:"), this);
    l2->addWidget(lbl2_5, 2, 2);
    pStaticRow1Lbl = new QLabel(this);
    l2->addWidget(pStaticRow1Lbl, 2, 3);
    QLabel *lbl2_7 =  new QLabel(tr("Column 1:"), this);
    l2->addWidget(lbl2_7, 3, 0);
    pColumn1Lbl = new QLabel(this);
    l2->addWidget(pColumn1Lbl, 3, 1);
    QLabel *lbl2_9 =  new QLabel(tr("Static 1:"), this);
    l2->addWidget(lbl2_9, 3, 2);
    pStaticColumn1Lbl = new QLabel(this);
    l2->addWidget(pStaticColumn1Lbl, 3, 3);

    QLabel *lbl2_4 =  new QLabel(tr("CellReference 1:"), this);
    l2->addWidget(lbl2_4, 4, 0);
    pReference2Lbl = new QLabel(this);
    l2->addWidget(pReference2Lbl, 1, 4, 1, 3);
    QLabel *lbl2_6 =  new QLabel(tr("Row 1:"), this);
    l2->addWidget(lbl2_6, 5, 0);
    pRow2Lbl = new QLabel(this);
    l2->addWidget(pRow2Lbl, 5, 1);
    QLabel *lbl2_8 =  new QLabel(tr("Static 1:"), this);
    l2->addWidget(lbl2_8, 5, 2);
    pStaticRow2Lbl = new QLabel(this);
    l2->addWidget(pStaticRow2Lbl, 5, 3);
    QLabel *lbl2_A =  new QLabel(tr("Column 1:"), this);
    l2->addWidget(lbl2_A, 6, 0);
    pColumn2Lbl = new QLabel(this);
    l2->addWidget(pColumn2Lbl, 6, 1);
    QLabel *lbl2_B =  new QLabel(tr("Static 1:"), this);
    l2->addWidget(lbl2_B, 6, 2);
    pStaticColumn2Lbl = new QLabel(this);
    l2->addWidget(pStaticColumn2Lbl, 6, 3);


    return frame;
}

void MainWindow::testReference() {
    SplitCellName split = QWorkbook::Reference::cellFromString(pCellReferenceEdit->text());

    if (!split.isGood) {
        setRefLabel(tr("Bad Reference"));
        setRowLabel(-1, false);
        setColumnLabel(-1, false);
        return;
    }

    setRefLabel(pCellReferenceEdit->text());
    setRowLabel(split.row, split.rowStatic);
    setColumnLabel(split.column, split.colStatic);

}

void MainWindow::testRange() {
    const QString s(pRangeEdit->text());
    QWorkbook::SplitRangeName split = QWorkbook::Reference::rangeFromString(s);

    if (!split.isValid()) {
        setRangeLabel(tr("Bad Range"));
        setRow1Label(-1, false);
        setColumn1Label(-1, false);
        setRow2Label(-1, false);
        setColumn2Label(-1, false);
        return;
    }

    setRangeLabel(pRangeEdit->text());
    setRow1Label(split.from.row, split.from.rowStatic);
    setRow2Label(split.to.row, split.to.rowStatic);
    setColumn1Label(split.from.column, split.from.colStatic);
    setColumn2Label(split.to.column, split.to.colStatic);

}

void MainWindow::setRefLabel(QString value) {
    pReferenceLbl->setText(value);
}

void MainWindow::setRangeLabel(QString value) {
    pRangeLbl->setText(value);
}

void MainWindow::setRowLabel(int value, bool stat) {
    pRowLbl->setText(QString::number(value));
    pStaticRowLbl->setText(stat ? "true" : "false");
}

void MainWindow::setRow1Label(int value, bool stat) {
    pRow1Lbl->setText(QString::number(value));
    pStaticRow1Lbl->setText(stat ? "true" : "false");
}

void MainWindow::setRow2Label(int value, bool stat) {
    pRow2Lbl->setText(QString::number(value));
    pStaticRow2Lbl->setText(stat ? "true" : "false");
}

void MainWindow::setColumnLabel(int value, bool stat) {
    pColumnLbl->setText(QString::number(value));
    pStaticColumnLbl->setText(stat ? "true" : "false");
}

void MainWindow::setColumn1Label(int value, bool stat) {
    pColumn1Lbl->setText(QString::number(value));
    pStaticColumn1Lbl->setText(stat ? "true" : "false");
}

void MainWindow::setColumn2Label(int value, bool stat) {
    pColumn2Lbl->setText(QString::number(value));
    pStaticColumn2Lbl->setText(stat ? "true" : "false");
}

QFrame* MainWindow::initWorksheet() {
    QFrame *frame = new QFrame(this);
    QGridLayout *layout = new QGridLayout;
    frame->setLayout(layout);

    pSheetView = new QWorksheetView(this);
    layout->addWidget(pSheetView, 0, 0);

    return frame;
}

QFrame *MainWindow::initWorkbook() {
    QFrame *frame = new QFrame(this);
    QGridLayout *layout = new QGridLayout;
    frame->setLayout(layout);

    pBookView = new QWorkbookView(this);
    layout->addWidget(pBookView, 0, 0);

    return frame;
}
