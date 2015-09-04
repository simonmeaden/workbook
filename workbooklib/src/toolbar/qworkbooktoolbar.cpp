/*
 * This Workbook library is © Simon Meaden 2015. It is licensed under the LGPL V3 license.
 *
 * This Workbook library dynamically links to unmodified Nokia Qt5 Library. The Qt5
 * Library is © 2011 Nokia Corporation and/or its subsidiary(-ies), and is licensed
 * under the GNU Lesser General Public License version 2.1 with Nokia Qt LGPL exception
 * version 1.1.
 *
 * Qt5 library is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License, version 2.1, as published by the
 * Free Software Foundation.
 *
 * Qt5 library is provided “AS IS”, without WARRANTIES OR CONDITIONS OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY WARRANTIES OR CONDITIONS OF
 * TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 * As an additional permission to the GNU Lesser General Public License version 3.0, the
 * object code form of a “work that uses the Library” may incorporate material from a
 * header file that is part of the Library. You may distribute such object code under
 * terms of your choice, provided that: (i) the header files of the Library have not
 * been modified; and (ii) the incorporated material is limited to numerical parameters,
 * data structure layouts, accessors, macros, inline functions and templates; and (iii)
 * you comply with the terms of Section 6 of the GNU Lesser General Public License version 3.0.
 *
 * Moreover, you may apply this exception to a modified version of the Library, provided
 * that such modification does not involve copying material from the Library into the
 * modified Library’s header files unless such material is limited to (i) numerical
 * parameters; (ii) data structure layouts; (iii) accessors; and (iv) small macros,
 * templates and inline functions of five lines or less in length.
 *
 * Furthermore, you are not required to apply this additional permission to a modified
 * version of the Library.
 *
 * You should have received a copy of the GNU Lesser General Public License along
 * with this package; if not, write to the Free Software Foundation, Inc., 51 Franklin
 * Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * The source code for Qt 5.4.X SDK is available from Nokia here:
 * http://get.qt.nokia.com/qt/source/qt-everywhere-opensource-src-4.7.X.zip.
 *
 * It is also available on request from Simon Meaden info@smelecomp.co.uk.
 */
#include "qworkbooktoolbar.h"
#include "qworkbookaligntoolbar.h"
#include "qworkbookfonteffectstoolbar.h"
#include "qworkbookfonttoolbar.h"
#include "qworkbookindenttoolbar.h"
#include "qworkbookmergetoolbar.h"
#include <qstd.h>

/*!
 * \class QWorkbookToolBar
 * \brief A OpenOffice style toolbar for the QWorkbook class.
 * \ingroup QWorkbookView
 *
 * The QWorkbookToolBar class provides a movable panel that contains a set of controls,
 * similar in form to OpenOffice Calc.
 *\

/*!
 * \brief Constructor for the QWorkbookToolBar class.
 *
 * Constructs a QWorkbookToolBar with the given parent.
 */
QWorkbookToolBar::QWorkbookToolBar(QWidget *parent) : QToolBar(parent) {
    initBuild();
}

/*!
 * \brief Constructor for the QWorkbookToolBar class.
 *
 * Constructs a QWorkbookToolBar with the given parent.
 *
 * The given window title identifies the toolbar and is shown in the context menu provided by QMainWindow.
 */
QWorkbookToolBar::QWorkbookToolBar(QString title, QWidget *parent) :
    QToolBar(title, parent) {
    initBuild();
}

/*!
 * \brief QWorkbookToolBar::~QWorkbookToolBar
 *
 * Destroys the toolbar.
 */
QWorkbookToolBar::~QWorkbookToolBar() {

}

void QWorkbookToolBar::initBuild() {
    pFontBar = new QWorkbookFontToolbar("font", this);
    pFontVisibleAction = pFontBar->toggleViewAction();
    addWidget(pFontBar);
    connect(pFontBar, SIGNAL(fontChanged(QFont)), this, SIGNAL(fontChanged(QFont)));
    connect(pFontBar, SIGNAL(fontSizeChanged(int)), this, SIGNAL(fontSizeChanged(int)));

    pFontEffectsBar = new QWorkbookFontEffectsToolbar("fonteffects", this);
    pFontEffectsVisibleAction = pFontEffectsBar->toggleViewAction();
    addWidget(pFontEffectsBar);
    connect(pFontEffectsBar, SIGNAL(boldChanged(bool)), this, SIGNAL(boldChanged(bool)));
    connect(pFontEffectsBar, SIGNAL(italicChanged(bool)), this, SIGNAL(italicChanged(bool)));
    connect(pFontEffectsBar, SIGNAL(underlineChanged(bool)), this, SIGNAL(underlineChanged(bool)));

    // TODO font colour & background colour

    pAlignBar = new QWorkbookAlignToolbar("align", this);
    pAlignVisibleAction = pAlignBar->toggleViewAction();
    addWidget(pAlignBar);
    connect(pAlignBar, SIGNAL(alignmentChanged(Qt::Alignment)), this, SIGNAL(alignmentChanged(Qt::Alignment)));

    pMergeBar = new QWorkbookMergeToolbar("merge", this);
    pMergeVisibleAction = pMergeBar->toggleViewAction();
    addWidget(pMergeBar);
    connect(pMergeBar, SIGNAL(mergeSelection(bool)), this, SIGNAL(mergeSelection(bool)));

    // TODO vertical align

    // TODO Number format

    pIndentBar = new QWorkbookIndentToolbar("indent", this);
    pIndentVisibleAction = pAlignBar->toggleViewAction();
    addWidget(pIndentBar);

    // TODO Borders
    // TODO Linestyle
    // TODO Conditional Formatting
    // TODO insert/remove columns/rows

    pPopupMenu = new QMenu(this);

    QMenu *toolbarMenu = new QMenu(tr("Toolbars"), this);
    pPopupMenu->addMenu(toolbarMenu);

    toolbarMenu->addAction(pFontVisibleAction);
    toolbarMenu->addAction(pFontEffectsVisibleAction);
    toolbarMenu->addAction(pAlignVisibleAction);
    toolbarMenu->addAction(pIndentVisibleAction);


    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));

}

/*!
 * \brief QWorkbookToolBar::setWorkbookView(QWorkbookView *view)
 *
 * \param view
 */
void QWorkbookToolBar::setWorkbookView(QWorkbookView *view) {

    pView = view;

    connect(pView, SIGNAL(selectionChanged(FormatStatus*)), this, SLOT(selectionChanged(FormatStatus*)));

    // bar to view
    connect(this, SIGNAL(boldChanged(bool)), pView, SLOT(setSelectionBold(bool)));
    connect(this, SIGNAL(italicChanged(bool)), pView, SLOT(setSelectionItalic(bool)));
    connect(this, SIGNAL(underlineChanged(bool)), pView, SLOT(setSelectionUnderline(bool)));
    connect(this, SIGNAL(fontChanged(QFont)), pView, SLOT(setSelectionFont(QFont)));
    connect(this, SIGNAL(fontSizeChanged(int)), pView, SLOT(setSelectionFontSize(int)));
    connect(this, SIGNAL(alignmentChanged(Qt::Alignment)), pView, SLOT(setSelectionAlignment(Qt::Alignment)));


    // view to bar
    connect(this, SIGNAL(boldSelection(bool)), pFontEffectsBar, SLOT(setBold(bool)));
    connect(this, SIGNAL(italicSelection(bool)), pFontEffectsBar, SLOT(setItalic(bool)));
    connect(this, SIGNAL(underlineSelection(bool)), pFontEffectsBar, SLOT(setUnderline(bool)));
    connect(this, SIGNAL(fontSelection(bool,QFont,int)), pFontBar, SLOT(setFont(bool,QFont,int)));
    connect(this, SIGNAL(alignSelection(bool,Qt::Alignment)), pAlignBar, SLOT(setAlign(bool, Qt::Alignment)));
    connect(this, SIGNAL(mergeSelection(bool)), pMergeBar, SLOT(setMerge(bool)));

    pView->triggerInitialSelection();
}

void QWorkbookToolBar::selectionChanged(FormatStatus* status) {
    if (!status) return;

    emit boldSelection(!(status->bAllBold));
    emit italicSelection(!(status->bAllItalic));
    emit underlineSelection(!(status->bAllUnderline));

    emit fontSelection(status->bAllSameFont, status->mFont, status->mFontSize);

    emit alignSelection(status->bAllSameAlignment, status->mAlignment);

    emit mergeSelection(status->bContiguous);

}

void QWorkbookToolBar::showContextMenu(const QPoint &pos) {
    QPoint globalPos = mapToGlobal(pos);

    QAction* selectedItem = pPopupMenu->exec(globalPos);


}

void QWorkbookToolBar::showFontBar(bool show) {
    pFontBar->setVisible(show);
}

void QWorkbookToolBar::showFontEffectsBar(bool show) {
    pFontEffectsBar->setVisible(show);
}

void QWorkbookToolBar::showIndentBar(bool show) {
    pIndentBar->setVisible(show);
}

void QWorkbookToolBar::showAlignBar(bool show) {
    pAlignBar->setVisible(show);
}

void QWorkbookToolBar::setBold(bool value) {
    emit boldChanged(value);
}

void QWorkbookToolBar::setItalic(bool value) {
    emit italicChanged(value);
}

void QWorkbookToolBar::setUnderline(bool value) {
    emit underlineChanged(value);
}

void QWorkbookToolBar::setFont(QFont font) {
    emit fontChanged(font);
}

void QWorkbookToolBar::setAlign(Qt::Alignment alignment) {
    emit alignmentChanged(alignment);
}
