#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QFrame>
#include <QTableView>
#include <QItemSelection>
#include <QStandardItemModel>
#include <QMenu>
#include <QMenuBar>

#include "ExtendedTabWidget"

namespace QWorkbook {
class QWorkbookToolBar;
class QCellEditToolBar;
class QWorkbookFunctionToolBar;
class QWorkbookView;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:

    void fileOpen();
    void fileSaveXlsx();
    void fileSaveOds();
    void fileSaveCsv();
    void fileSaveAs();
    void fileNew();
    void filePrint();
    void fileClose();

protected:
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *printAct;
    QAction *closeAct;

    QWorkbook::QWorkbookToolBar *pToolbar;
    QWorkbook::QWorkbookFunctionToolBar *pFunctionBar;
    QWorkbook::QCellEditToolBar *pCellEditor;

    void initBuild();
    QFrame* initFunctionParserTest();
    void initToolbar();
    void initActions();
    void initMenu();
    QFrame *initWorksheet();
    QFrame *initWorkbook();


private:
    QWorkbook::QWorkbookView *pView;

};

#endif // MAINWINDOW_H
