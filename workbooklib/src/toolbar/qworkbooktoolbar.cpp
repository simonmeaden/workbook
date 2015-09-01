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
#include "qstd.h"

QWorkbookToolBar::QWorkbookToolBar(QWidget *parent) : QToolBar(parent) {
    initBuild();
}

QWorkbookToolBar::QWorkbookToolBar(QString title, QWidget *parent) :
    QToolBar(title, parent) {
    initBuild();
}

QWorkbookToolBar::~QWorkbookToolBar() {

}

void QWorkbookToolBar::initBuild() {
    pFontBar = new WorkbookFontToolbar("font", this);
    pFontVisibleAction = pFontBar->toggleViewAction();
    addWidget(pFontBar);

    pFontEffectsBar = new WorkbookFontEffectsToolbar("font2", this);
    pFontEffectsVisibleAction = pFontEffectsBar->toggleViewAction();
    addWidget(pFontEffectsBar);

    pAlignBar = new WorkbookAlignToolbar("align", this);
    pAlignVisibleAction = pAlignBar->toggleViewAction();
    addWidget(pAlignBar);

    pIndentBar = new WorkbookIndentToolbar("indent", this);
    pIndentVisibleAction = pAlignBar->toggleViewAction();
    addWidget(pIndentBar);

    pFunctionBar = new WorkbookFunctionToolbar("function", this);
    ppFunctionVisibleAction = pFunctionBar->toggleViewAction();
    addWidget(pFunctionBar);

    pPopupMenu = new QMenu(this);

    QMenu *toolbarMenu = new QMenu(tr("Toolbars"), this);
    pPopupMenu->addMenu(toolbarMenu);

    toolbarMenu->addAction(pFontVisibleAction);
    toolbarMenu->addAction(pFontEffectsVisibleAction);
    toolbarMenu->addAction(pAlignVisibleAction);
    toolbarMenu->addAction(pIndentVisibleAction);
    toolbarMenu->addAction(ppFunctionVisibleAction);


    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));

    connect(pFontBar, SIGNAL(italic(bool)), pFontEffectsBar, SLOT(setItalic(bool)));
    connect(pFontBar, SIGNAL(bold(bool)), pFontEffectsBar, SLOT(setBold(bool)));

    connect(this, SIGNAL(boldChanged(bool)), pFontEffectsBar, SLOT(setBold(bool)));
    connect(this, SIGNAL(italicChanged(bool)), pFontEffectsBar, SLOT(setItalic(bool)));
    connect(this, SIGNAL(underlineChanged(bool)), pFontEffectsBar, SLOT(setUnderline(bool)));
    connect(this, SIGNAL(fontChanged(QFont)), pFontBar, SLOT(setFont(QFont)));
    connect(this, SIGNAL(alignmentChanged(Qt::Alignment)), pAlignBar, SLOT(setAlign(Qt::Alignment)));
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

void QWorkbookToolBar::showFunctionBar(bool show) {
    pFunctionBar->setVisible(show);
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
