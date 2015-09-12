/*
    Copyright © Simon Meaden 2015.

    This file is part of the QWorkbook spreadsheet library.

    QWorkbook is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    QWorkbook is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QWorkbook.  If not, see <http://www.gnu.org/licenses/>.

    It is also available on request from Simon Meaden info@smelecomp.co.uk.
*/
#ifndef QWORKBOOKFUNCTIONTOOLBARPRIVATE_H
#define QWORKBOOKFUNCTIONTOOLBARPRIVATE_H

#include <QPlainTextEdit>
#include <QPushButton>
#include <QToolButton>
#include <QLineEdit>


class QWorkbookFunctionToolBar;
class QWorkbookView;
class FormatStatus;

class QWorkbookFunctionToolBarPrivate {
    Q_DECLARE_PUBLIC(QWorkbookFunctionToolBar)
public:
    QWorkbookFunctionToolBarPrivate(QWorkbookFunctionToolBar *q);
    virtual ~QWorkbookFunctionToolBarPrivate() {}

    void drop();
    void manageNames();
    void functionWizard();
    void sum();
    void function();
    void setRange(QString value);

protected:
    QLineEdit *rangeEdit, *functionEdit;
    QPlainTextEdit *dropDownEdit;
    QToolButton *manageNamesBtn, *dropBtn;
    QPushButton *funcWizardBtn, *sumBtn, *funcBtn;
    QWidget *editor;
    QWorkbookFunctionToolBar *q_ptr;

    void init();

};

#endif // QWORKBOOKFUNCTIONTOOLBARPRIVATE_H
