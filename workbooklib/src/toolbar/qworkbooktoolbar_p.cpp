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
#include "qworkbooktoolbar_p.h"
#include "qworkbooktoolbar.h"
//#include "qworkbookfonttoolbar.h"
//#include "qworkbookfonteffectstoolbar.h"
//#include "qworkbookaligntoolbar.h"
//#include "qworkbookmergetoolbar.h"
//#include "qworkbookindenttoolbar.h"
#include "qstd.h"

QWorkbookToolBarPrivate::QWorkbookToolBarPrivate(QWorkbookToolBar *parent) :
    q_ptr(parent) {

}

void QWorkbookToolBarPrivate::init() {

    Q_Q(QWorkbookToolBar);
    pFontBar = new QWorkbookFontToolBar("font", q);
    pFontVisibleAction = pFontBar->toggleViewAction();
    q->addWidget(pFontBar);
    q->connect(pFontBar, SIGNAL(fontChanged(QFont)), q, SIGNAL(fontChanged(QFont)));
    q->connect(pFontBar, SIGNAL(fontSizeChanged(int)), q, SIGNAL(fontSizeChanged(int)));

    pFontEffectsBar = new QWorkbookFontEffectsToolBar("fonteffects", q);
    pFontEffectsVisibleAction = pFontEffectsBar->toggleViewAction();
    q->addWidget(pFontEffectsBar);
    q->connect(pFontEffectsBar, SIGNAL(boldChanged(bool)), q, SIGNAL(boldChanged(bool)));
    q->connect(pFontEffectsBar, SIGNAL(italicChanged(bool)), q, SIGNAL(italicChanged(bool)));
    q->connect(pFontEffectsBar, SIGNAL(underlineChanged(bool)), q, SIGNAL(underlineChanged(bool)));

    // TODO font colour & background colour

    pAlignBar = new QWorkbookAlignToolBar("align", q);
    pAlignVisibleAction = pAlignBar->toggleViewAction();
    q->addWidget(pAlignBar);
//    q->connect(pAlignBar, SIGNAL(alignmentChanged(Qt::Alignment)), q, SIGNAL(alignmentChanged(Qt::Alignment)));

    pMergeBar = new QWorkbookMergeToolbar("merge", q);
    pMergeVisibleAction = pMergeBar->toggleViewAction();
    q->addWidget(pMergeBar);
    q->connect(pMergeBar, SIGNAL(mergeChanged(bool)), q, SIGNAL(mergeChanged(bool)));

    // TODO vertical align

    // TODO Number format

    pIndentBar = new QWorkbookIndentToolBar("indent", q);
    pIndentVisibleAction = pAlignBar->toggleViewAction();
    q->addWidget(pIndentBar);

    // TODO Borders
    // TODO Linestyle
    // TODO Conditional Formatting
    // TODO insert/remove columns/rows

    pPopupMenu = new QMenu(q);

    pToolbarMenu = new QMenu(q->tr("Toolbars"), q);
    pPopupMenu->addMenu(pToolbarMenu);

    pToolbarMenu->addAction(pFontVisibleAction);
    pToolbarMenu->addAction(pFontEffectsVisibleAction);
    pToolbarMenu->addAction(pAlignVisibleAction);
    pToolbarMenu->addAction(pIndentVisibleAction);


    q->setContextMenuPolicy(Qt::CustomContextMenu);
    q->connect(q, SIGNAL(customContextMenuRequested(const QPoint&)), q, SLOT(showContextMenu(const QPoint&)));

}

void QWorkbookToolBarPrivate::setWorkbookView(QWorkbookView *view) {

    pView = view;

    pAlignBar->setWorkbookView(view);
    pFontEffectsBar->setWorkbookView(view);
    pFontBar->setWorkbookView(view);
    pMergeBar->setWorkbookView(view);

    pView->triggerInitialSelection();
}

void QWorkbookToolBarPrivate::selectionChanged(FormatStatus* status) {
    if (!status) return;

    q_ptr->selectionChanged(status);

    emit q_ptr->boldSelection(!(status->bAllBold));
    emit q_ptr->italicSelection(!(status->bAllItalic));
    emit q_ptr->underlineSelection(!(status->bAllUnderline));

    emit q_ptr->fontSelection(status->bAllSameFont, status->mFont, status->mFontSize);

    emit q_ptr->mergeSelection(status->bContiguous);

}

void QWorkbookToolBarPrivate::showContextMenu(const QPoint &pos) {
    Q_UNUSED(pos)
//    QPoint globalPos = mapToGlobal(pos);

//    QAction* selectedItem = pPopupMenu->exec(globalPos);

    // TODO complete this

}

void QWorkbookToolBarPrivate::showFontBar(bool show) {
    pFontBar->setVisible(show);
}

void QWorkbookToolBarPrivate::showFontEffectsBar(bool show) {
    pFontEffectsBar->setVisible(show);
}

void QWorkbookToolBarPrivate::showIndentBar(bool show) {
    pIndentBar->setVisible(show);
}

void QWorkbookToolBarPrivate::showAlignBar(bool show) {
    pAlignBar->setVisible(show);
}

void QWorkbookToolBarPrivate::setBold(bool value) {
    emit q_ptr->boldChanged(value);
}

void QWorkbookToolBarPrivate::setItalic(bool value) {
    emit q_ptr->italicChanged(value);
}

void QWorkbookToolBarPrivate::setUnderline(bool value) {
    emit q_ptr->underlineChanged(value);
}

void QWorkbookToolBarPrivate::setFont(QFont font) {
    emit q_ptr->fontChanged(font);
}

void QWorkbookToolBarPrivate::setAlign(Qt::Alignment alignment) {
    emit q_ptr->alignmentChanged(alignment);
}
