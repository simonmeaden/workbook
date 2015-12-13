#include "mainwindow.h"

#include <QWorksheetView>
#include <QWorkbookView>
#include <QWorkbookToolbar>
#include <QCellEditToolbar>
#include <Workbook>

#include "qstd.h"
#include "ExtendedTabWidget"

#include "workbook_global.h"

QWORKBOOK_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    initBuild();

    initActions();
    initMenu();
    initToolbar();

}

MainWindow::~MainWindow() {

}

void MainWindow::fileClose() {
    close();
}

void MainWindow::fileOpen() {

}

void MainWindow::fileSaveXlsx() {
    pView->saveWorkbook("testFile", WorksheetType::XLSX);
}

void MainWindow::fileSaveOds() {
    pView->saveWorkbook("testFile", WorksheetType::ODS);
}

void MainWindow::fileSaveCsv() {
    pView->saveWorkbook("testFile", WorksheetType::CSV);
}

void MainWindow::fileSaveAs() {

}

void MainWindow::fileNew() {

}

void MainWindow::filePrint() {

}

void MainWindow::initActions() {

    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(fileNew()));

    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open a file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(fileOpen()));

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save file"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(fileSaveXlsx()));

    saveAsAct = new QAction(tr("Save &As"), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save file as..."));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(fileSaveAs()));

    printAct = new QAction(tr("&Print"), this);
    printAct->setShortcuts(QKeySequence::Print);
    printAct->setStatusTip(tr("Print a file"));
    connect(printAct, SIGNAL(triggered()), this, SLOT(filePrint()));

    closeAct = new QAction(tr("E&xit"), this);
    closeAct->setShortcuts(QKeySequence::Close);
    closeAct->setStatusTip(tr("Exit Application"));
    connect(closeAct, SIGNAL(triggered()), this, SLOT(fileClose()));

}

void MainWindow::initMenu() {

    QMenuBar *menu = menuBar();

    QMenu *fileMenu = new QMenu(tr("File"), this);
    menu->addMenu(fileMenu);

    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
}

void MainWindow::initToolbar() {

    pToolbar = new QWorkbookToolBar(this);
    addToolBar(pToolbar);
    pToolbar->setWorkbookView(pView);

    pCellEditor = new QCellEditToolBar("celleditor", this);
    addToolBar(pCellEditor);
    pCellEditor->setWorkbookView(pView);

    pFunctionBar = new QWorkbookFunctionToolBar("function", this);
//    pFunctionVisibleAction = functionBar->toggleViewAction();
    addToolBar(pFunctionBar);


//    toolbar->showAlignBar(false);
}

void MainWindow::initBuild() {

    ExtendedTabWidget *tabs = new ExtendedTabWidget(this);
    setCentralWidget(tabs);

    tabs->addTab(initWorkbook(), tr("Workbook"));
    tabs->addTab(initWorksheet(), tr("Worksheet"));
    tabs->addTab(initFunctionParserTest(), tr("Function Parser"));

}

QFrame* MainWindow::initFunctionParserTest() {
    QFrame *frame = new QFrame(this);
    QVBoxLayout *layout = new QVBoxLayout;
    frame->setLayout(layout);

//    layout->addWidget(initWorkbook());
//    layout->addWidget(initWorksheet());
    return frame;
}

QFrame* MainWindow::initWorksheet() {
    QFrame *frame = new QFrame(this);
    QGridLayout *layout = new QGridLayout;
    frame->setLayout(layout);

    QWorksheetView *view = new QWorksheetView(this);
    layout->addWidget(view, 0, 0);

    view->show();

    return frame;
}

QFrame *MainWindow::initWorkbook() {
    QFrame *frame = new QFrame(this);
    QGridLayout *layout = new QGridLayout;
    frame->setLayout(layout);

    pView = new QWorkbookView(this);
    layout->addWidget(pView, 0, 0);

    return frame;
}


