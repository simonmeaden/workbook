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
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QTabWidget>
#include <QLabel>
#include <QDebug>

//#include "ExtendedTabWidget"

#include "reference.h"

namespace QWorkbook {
class QWorkbookToolBar;
class QCellEditToolBar;
class QWorkbookFunctionToolBar;
class QWorkbookView;
class QWorksheetView;
}

class MainWindow : public QMainWindow, public QWorkbook::Reference {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow() {}

protected slots:

    void fileNewWorkbook();
    void fileOpenWorkbook();
    void fileSaveWorkbook();
    void fileSaveWorkbookAs();

    void fileNewWorksheet();
    void fileOpenWorksheet();
    void fileSaveWorksheet();
    void fileSaveWorksheetAs();

    void filePrintBook();
    void filePrintSheet();

    void fileClose();

    void testReference();
    void testRange();
    void setRefLabel(QString);
    void setRowLabel(int, bool);
    void setRow1Label(int, bool);
    void setRow2Label(int, bool);
    void setColumnLabel(int, bool);
    void setColumn1Label(int, bool);
    void setColumn2Label(int, bool);
    void setRangeLabel(QString);

    void tabChanged(int);

protected:
    QTabWidget *pTabs;

    QAction *pNewBookAct, *pOpenBookAct, *pSaveBookAct, *pSaveBookAsAct;
    QAction *pNewSheetAct, *pOpenSheetAct, *pSaveSheetAct, *pSaveSheetAsAct;
    QAction *pPrintBookAct, *pPrintSheetAct;
    QAction *pCloseAct;

    QWorkbook::QWorkbookToolBar *pToolbar;
    QWorkbook::QWorkbookFunctionToolBar *pFunctionBar;
    QWorkbook::QCellEditToolBar *pCellEditorBar;

    QLabel *pReferenceLbl, *pRowLbl, *pStaticRowLbl, *pColumnLbl, *pStaticColumnLbl;
    QLabel *pReference1Lbl, *pReference2Lbl;
    QLabel *pRangeLbl, *pRow1Lbl, *pStaticRow1Lbl, *pColumn1Lbl, *pStaticColumn1Lbl;
    QLabel *pRow2Lbl, *pStaticRow2Lbl, *pColumn2Lbl, *pStaticColumn2Lbl;
    QLineEdit *pCellReferenceEdit, *pCellFunctionEditor, *pRangeEdit;
    QPlainTextEdit *pTokenOutput;
    QPushButton *pTokeniseBtn;

    QPushButton *pQuitBtn;


    QString mFilename;

    void initBuild();
    QFrame* initFunctionParserTest();
    QFrame* initTest();
    QFrame* initTestCellReference();
    QFrame* initTestRange();
    void initToolbar();
    void initActions();
    void initMenu();
    QFrame *initWorksheet();
    QFrame *initWorkbook();


private:
    QWorkbook::QWorkbookView *pBookView;
    QWorkbook::QWorksheetView *pSheetView;
    QWorkbook::QWorksheetView *pTestView;


};

#endif // MAINWINDOW_H
