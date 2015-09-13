#include "mainwindow.h"

#include <QWorksheetView>
#include <QWorkbookView>
#include <QWorkbookToolbar>
#include <QCellEditToolbar>
#include <Workbook>

#include <qstd.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    initBuild();

    initToolbar();

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

    QFrame *frame = new QFrame(this);
    QVBoxLayout *layout = new QVBoxLayout;
    frame->setLayout(layout);
    setCentralWidget(frame);

    layout->addWidget(initWorkbook());
    layout->addWidget(initWorksheet());

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

MainWindow::~MainWindow() {

}
