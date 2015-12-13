#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qstd.h"

#include "workbook_global.h"

QT_BEGIN_NAMESPACE_QWORKBOOK

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->readExprBtn, SIGNAL(clicked()), this, SLOT(readExpression()));

}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::readExpression() {
    QString text = ui->expressionEdit->text();

    cout << text << endl << flush;

    tokeniser->parse(text);

}

void MainWindow::fileOpen() {

}


QT_END_NAMESPACE_QWORKBOOK
