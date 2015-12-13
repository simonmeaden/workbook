#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

#include "workbook_global.h"

QT_BEGIN_NAMESPACE_QWORKBOOK

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void readExpression();
    void fileOpen();

protected:

private:
    Ui::MainWindow *ui;
};

QT_END_NAMESPACE_QWORKBOOK

#endif // MAINWINDOW_H
