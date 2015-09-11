/*
    This Workbook library is © Simon Meaden 2015. It is licensed under the LGPL V3 license.

    This Workbook library dynamically links to unmodified Nokia Qt5 Library. The Qt5
    Library is © 2011 Nokia Corporation and/or its subsidiary(-ies), and is licensed
    under the GNU Lesser General Public License version 2.1 with Nokia Qt LGPL exception
    version 1.1.

    Qt5 library is free software; you can redistribute it and/or modify it under the
    terms of the GNU Lesser General Public License, version 2.1, as published by the
    Free Software Foundation.

    Qt5 library is provided “AS IS”, without WARRANTIES OR CONDITIONS OF ANY KIND, EITHER
    EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY WARRANTIES OR CONDITIONS OF
    TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.

    As an additional permission to the GNU Lesser General Public License version 3.0, the
    object code form of a “work that uses the Library” may incorporate material from a
    header file that is part of the Library. You may distribute such object code under
    terms of your choice, provided that: (i) the header files of the Library have not
    been modified; and (ii) the incorporated material is limited to numerical parameters,
    data structure layouts, accessors, macros, inline functions and templates; and (iii)
    you comply with the terms of Section 6 of the GNU Lesser General Public License version 3.0.

    Moreover, you may apply this exception to a modified version of the Library, provided
    that such modification does not involve copying material from the Library into the
    modified Library’s header files unless such material is limited to (i) numerical
    parameters; (ii) data structure layouts; (iii) accessors; and (iv) small macros,
    templates and inline functions of five lines or less in length.

    Furthermore, you are not required to apply this additional permission to a modified
    version of the Library.

    You should have received a copy of the GNU Lesser General Public License along
    with this package; if not, write to the Free Software Foundation, Inc., 51 Franklin
    Street, Fifth Floor, Boston, MA 02110-1301 USA

    The source code for Qt 5.4.X SDK is available from Nokia here:
    http://get.qt.nokia.com/qt/source/qt-everywhere-opensource-src-4.7.X.zip.

    It is also available on request from Simon Meaden info@smelecomp.co.uk.
*/
#include "qworkbookfunctiontoolbar_p.h"

QWorkbookFunctionToolBarPrivate::QWorkbookFunctionToolBarPrivate(QWorkbookFunctionToolBar *q) :
    BaseToolBarPrivate(q)/*,
    q_ptr(q)*/ {

    init();

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

