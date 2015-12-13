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
#include "qworkbookfunctiontoolbar_p.h"
#include "qworkbookfunctiontoolbar.h"
#include "qworkbookview.h"
#include "types.h"

#include "workbook_global.h"

namespace QWorkbook {

QWorkbookFunctionToolBarPrivate::QWorkbookFunctionToolBarPrivate(QWorkbookFunctionToolBar *q) :
    q_ptr(q) {

}

void QWorkbookFunctionToolBarPrivate::init() {
    rangeEdit = new QLineEdit(q_ptr);
    rangeEdit->setReadOnly(true);
    q_ptr->addWidget(rangeEdit);

    manageNamesBtn = new QToolButton(q_ptr);
    manageNamesBtn->setCheckable(true);
    manageNamesBtn->setArrowType(Qt::DownArrow);
    q_ptr->addWidget(manageNamesBtn);

    funcWizardBtn = new QPushButton(q_ptr);
    funcWizardBtn->setToolTip(q_ptr->tr("Function Wizard"));
    funcWizardBtn->setIcon(QIcon("://fxwizard"));
    q_ptr->addWidget(funcWizardBtn);

    sumBtn = new QPushButton(q_ptr);
    sumBtn->setToolTip(q_ptr->tr("Sum"));
    sumBtn->setIcon(QIcon("://sum"));
    q_ptr->addWidget(sumBtn);

    funcBtn = new QPushButton(q_ptr);
    funcBtn->setToolTip(q_ptr->tr("Function"));
    funcBtn->setIcon(QIcon("://function"));
    q_ptr->addWidget(funcBtn);

    functionEdit = new QLineEdit(q_ptr);
    dropDownEdit = new QPlainTextEdit(q_ptr);
    dropDownEdit->setVisible(false);
    editor = functionEdit;
    q_ptr->addWidget(editor);

    dropBtn = new QToolButton(q_ptr);
    dropBtn->setCheckable(true);
    dropBtn->setArrowType(Qt::DownArrow);
    q_ptr->addWidget(dropBtn);
    q_ptr->connect(dropBtn, SIGNAL(clicked()), q_ptr, SLOT(drop()));

 }

void QWorkbookFunctionToolBarPrivate::drop() {
    if (editor == functionEdit) {
        dropDownEdit->setVisible(true);
        functionEdit->setVisible(false);
        editor = dropDownEdit;
    } else {
        dropDownEdit->setVisible(false);
        functionEdit->setVisible(true);
        editor = functionEdit;
    }
}

void QWorkbookFunctionToolBarPrivate::manageNames() {
    // TODO
}

void QWorkbookFunctionToolBarPrivate::functionWizard() {
    // TODO
}

void QWorkbookFunctionToolBarPrivate::sum() {
    // TODO
}

void QWorkbookFunctionToolBarPrivate::function() {
    // TODO
}

void QWorkbookFunctionToolBarPrivate::setRange(QString value){
    rangeEdit->setText(value);
}


}

