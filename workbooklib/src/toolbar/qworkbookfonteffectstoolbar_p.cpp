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
#include "qworkbookfonteffectstoolbar_p.h"
#include "qworkbookfonteffectstoolbar.h"
#include "qworkbookview.h"
#include "types.h"

QWorkbookFontEffectsToolBarPrivate::QWorkbookFontEffectsToolBarPrivate(QWorkbookFontEffectsToolBar *q) :
    q_ptr(q) {

    init();

}

void QWorkbookFontEffectsToolBarPrivate::init()  {
    pBoldBtn = new QPushButton(QIcon("://bold"), "", q_ptr);
    pBoldBtn->setShortcut(QKeySequence(QKeySequence::Bold));
    pBoldBtn->setToolTip(q_ptr->tr("Bold (Ctrl+B)"));
    pBoldBtn->setStyleSheet(buttonStyle);
    pBoldBtn->setContentsMargins(0, 0, 0, 0);
    pBoldBtn->setCheckable(true);
    q_ptr->addWidget(pBoldBtn);
    q_ptr->connect(pBoldBtn, SIGNAL(clicked()), q_ptr, SLOT(boldHasClicked()));

    pItalicBtn = new QPushButton(QIcon("://italic"), "", q_ptr);
    pItalicBtn->setShortcut(QKeySequence(QKeySequence::Italic));
    pItalicBtn->setToolTip(q_ptr->tr("Italic (Ctrl+I)"));
    pItalicBtn->setStyleSheet(buttonStyle);
    pItalicBtn->setContentsMargins(0, 0, 0, 0);
    pItalicBtn->setCheckable(true);
    q_ptr->addWidget(pItalicBtn);
    q_ptr->connect(pItalicBtn, SIGNAL(clicked()), q_ptr, SLOT(italicHasClicked()));

    pUnderlineBtn = new QPushButton(QIcon("://underline"), "", q_ptr);
    pUnderlineBtn->setShortcut(QKeySequence(QKeySequence::Underline));
    pUnderlineBtn->setToolTip(q_ptr->tr("Underline (Ctrl+U)"));
    pUnderlineBtn->setStyleSheet(buttonStyle);
    pUnderlineBtn->setContentsMargins(0, 0, 0, 0);
    pUnderlineBtn->setCheckable(true);
    q_ptr->addWidget(pUnderlineBtn);
    q_ptr->connect(pUnderlineBtn, SIGNAL(clicked()), q_ptr, SLOT(underlineHasClicked()));

}

void QWorkbookFontEffectsToolBarPrivate::setWorkbookView(QWorkbookView *view) {
    Q_Q(QWorkbookFontEffectsToolBar);

    q->connect(view, SIGNAL(selectionChanged(FormatStatus*)),
               q, SLOT(selectionChanged(FormatStatus*)));

    q->connect(q, SIGNAL(boldChanged(bool)), view, SLOT(setSelectionBold(bool)));
    q->connect(q, SIGNAL(italicChanged(bool)), view, SLOT(setSelectionItalic(bool)));
    q->connect(q, SIGNAL(underlineChanged(bool)), view, SLOT(setSelectionUnderline(bool)));
}

void QWorkbookFontEffectsToolBarPrivate::selectionChanged(FormatStatus* status) {
    if (!status) return;

    setBold(!(status->bAllBold));
    setItalic(!(status->bAllItalic));
    setUnderline(!(status->bAllUnderline));

}


void QWorkbookFontEffectsToolBarPrivate::boldHasClicked() {

    Q_Q(QWorkbookFontEffectsToolBar);
    emit q->boldChanged(pBoldBtn->isChecked());

}

void QWorkbookFontEffectsToolBarPrivate::italicHasClicked() {

    Q_Q(QWorkbookFontEffectsToolBar);
    emit q->italicChanged(pItalicBtn->isChecked());

}

void QWorkbookFontEffectsToolBarPrivate::underlineHasClicked() {

    Q_Q(QWorkbookFontEffectsToolBar);
    emit q->underlineChanged(pUnderlineBtn->isChecked());

}

void QWorkbookFontEffectsToolBarPrivate::setBold(bool value) {
    pBoldBtn->setChecked(value);
}

void QWorkbookFontEffectsToolBarPrivate::setItalic(bool value) {
    pItalicBtn->setChecked(value);
}

void QWorkbookFontEffectsToolBarPrivate::setUnderline(bool value) {
    pUnderlineBtn->setChecked(value);
}

