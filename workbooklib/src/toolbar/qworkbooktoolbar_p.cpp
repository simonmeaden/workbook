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

    cout << "QWorkbookToolBarPrivate" << endl << flush;

    init();

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
