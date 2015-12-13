/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Open;
    QAction *action_New;
    QAction *action_Save;
    QAction *actionRead;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLineEdit *expressionEdit;
    QPlainTextEdit *plainTyFileEditextEdit_2;
    QPlainTextEdit *extExpressionEdit;
    QPushButton *readExprBtn;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menuTokeniser;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(827, 580);
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName(QStringLiteral("action_Open"));
        action_New = new QAction(MainWindow);
        action_New->setObjectName(QStringLiteral("action_New"));
        action_Save = new QAction(MainWindow);
        action_Save->setObjectName(QStringLiteral("action_Save"));
        actionRead = new QAction(MainWindow);
        actionRead->setObjectName(QStringLiteral("actionRead"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        expressionEdit = new QLineEdit(centralWidget);
        expressionEdit->setObjectName(QStringLiteral("expressionEdit"));

        gridLayout->addWidget(expressionEdit, 0, 1, 1, 1);

        plainTyFileEditextEdit_2 = new QPlainTextEdit(centralWidget);
        plainTyFileEditextEdit_2->setObjectName(QStringLiteral("plainTyFileEditextEdit_2"));

        gridLayout->addWidget(plainTyFileEditextEdit_2, 1, 0, 1, 1);

        extExpressionEdit = new QPlainTextEdit(centralWidget);
        extExpressionEdit->setObjectName(QStringLiteral("extExpressionEdit"));

        gridLayout->addWidget(extExpressionEdit, 1, 1, 1, 1);

        readExprBtn = new QPushButton(centralWidget);
        readExprBtn->setObjectName(QStringLiteral("readExprBtn"));

        gridLayout->addWidget(readExprBtn, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 827, 27));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        menuTokeniser = new QMenu(menuBar);
        menuTokeniser->setObjectName(QStringLiteral("menuTokeniser"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menuTokeniser->menuAction());
        menu_File->addAction(action_Open);
        menu_File->addAction(action_New);
        menu_File->addAction(action_Save);
        menuTokeniser->addAction(actionRead);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        action_Open->setText(QApplication::translate("MainWindow", "&Open", 0));
        action_New->setText(QApplication::translate("MainWindow", "&New", 0));
        action_Save->setText(QApplication::translate("MainWindow", "&Save", 0));
        actionRead->setText(QApplication::translate("MainWindow", "Read", 0));
        readExprBtn->setText(QApplication::translate("MainWindow", "Read", 0));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0));
        menuTokeniser->setTitle(QApplication::translate("MainWindow", "Tokeniser", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
