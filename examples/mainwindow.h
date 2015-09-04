#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QFrame>
#include <QTableView>
#include <QItemSelection>
#include <QStandardItemModel>

class QWorkbookToolBar;
class QWorkbookFunctionToolbar;
class QWorkbookView;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:

protected:

    QWorkbookToolBar *pToolbar;
    QWorkbookFunctionToolbar *pFunctionBar;

    void initBuild();
    void initToolbar();
    QFrame *initWorksheet();
    QFrame *initWorkbook();


private:
    QWorkbookView *pView;

};

#endif // MAINWINDOW_H