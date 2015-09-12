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
#include "qworkbookfonteffectstoolbar_p.h"
#include "qworkbookfonteffectstoolbar.h"
#include "qworkbookview.h"
#include "types.h"

QWorkbookFontEffectsToolBarPrivate::QWorkbookFontEffectsToolBarPrivate(QWorkbookFontEffectsToolBar *q) :
    q_ptr(q) {

}

void QWorkbookFontEffectsToolBarPrivate::init()  {
    pBoldBtn = new QPushButton(QIcon("://bold"), "", q_ptr);
    pBoldBtn->setShortcut(QKeySequence(QKeySequence::Bold));
    pBoldBtn->setToolTip(q_ptr->tr("Bold (Ctrl+B)"));
    pBoldBtn->setStyleSheet(ButtonStyle);
    pBoldBtn->setContentsMargins(0, 0, 0, 0);
    pBoldBtn->setCheckable(true);
    q_ptr->addWidget(pBoldBtn);
    q_ptr->connect(pBoldBtn, SIGNAL(clicked()), q_ptr, SLOT(boldHasClicked()));

    pItalicBtn = new QPushButton(QIcon("://italic"), "", q_ptr);
    pItalicBtn->setShortcut(QKeySequence(QKeySequence::Italic));
    pItalicBtn->setToolTip(q_ptr->tr("Italic (Ctrl+I)"));
    pItalicBtn->setStyleSheet(ButtonStyle);
    pItalicBtn->setContentsMargins(0, 0, 0, 0);
    pItalicBtn->setCheckable(true);
    q_ptr->addWidget(pItalicBtn);
    q_ptr->connect(pItalicBtn, SIGNAL(clicked()), q_ptr, SLOT(italicHasClicked()));

    pUnderlineBtn = new QPushButton(QIcon("://underline"), "", q_ptr);
    pUnderlineBtn->setShortcut(QKeySequence(QKeySequence::Underline));
    pUnderlineBtn->setToolTip(q_ptr->tr("Underline (Ctrl+U)"));
    pUnderlineBtn->setStyleSheet(ButtonStyle);
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

